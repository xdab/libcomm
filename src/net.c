#include "net.h"
#include "common.h"
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

int net_resolve(const char *host, int port, struct sockaddr_in *out_addr)
{
    nonnull(host, "host");
    nonnull(out_addr, "out_addr");
    EXITIF(port < 0, -1, "port must be positive");
    EXITIF(port > 65535, -1, "port must be less than 65536");

    memset(out_addr, 0, sizeof(struct sockaddr_in));
    out_addr->sin_family = AF_INET;
    out_addr->sin_port = htons(port);

    if (inet_pton(AF_INET, host, &out_addr->sin_addr) == 1)
        return 0;

    struct addrinfo hints, *result, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    int ret = getaddrinfo(host, port_str, &hints, &result);
    if (ret != 0)
    {
        LOG("failed to resolve host '%s': %s", host, gai_strerror(ret));
        return -1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        if (rp->ai_family == AF_INET)
        {
            memcpy(out_addr, rp->ai_addr, sizeof(struct sockaddr_in));
            freeaddrinfo(result);
            return 0;
        }
    }

    LOG("no IPv4 address found for host '%s'", host);
    freeaddrinfo(result);
    return -1;
}
