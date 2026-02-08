#ifndef TEST_NET_H
#define TEST_NET_H

#include "test.h"
#include "net.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void test_net_resolve_localhost(void)
{
    struct sockaddr_in addr;
    int result = net_resolve("localhost", 12345, &addr);
    assert_equal_int(result, 0, "localhost resolves successfully");
    assert_equal_int(addr.sin_family, AF_INET, "family is AF_INET");
    assert_equal_int(ntohs(addr.sin_port), 12345, "port is correct");

    char ipbuf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ipbuf, sizeof(ipbuf));
    assert_string(ipbuf, "127.0.0.1", "localhost resolves to 127.0.0.1");
}

void test_net_resolve_numeric_ip(void)
{
    struct sockaddr_in addr;
    int result = net_resolve("192.168.1.1", 8080, &addr);
    assert_equal_int(result, 0, "numeric IP resolves successfully");
    assert_equal_int(addr.sin_family, AF_INET, "family is AF_INET");
    assert_equal_int(ntohs(addr.sin_port), 8080, "port is correct");

    char ipbuf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ipbuf, sizeof(ipbuf));
    assert_string(ipbuf, "192.168.1.1", "numeric IP is correct");
}

void test_net_resolve_empty_address(void)
{
    struct sockaddr_in addr;
    int result = net_resolve("", 12345, &addr);
    assert_equal_int(result, -1, "empty address rejected");
}

void test_net_resolve_unresolvable(void)
{
    struct sockaddr_in addr;
    int result = net_resolve("invalid.host.does.not.exist.example", 12345, &addr);
    assert_equal_int(result, -1, "unresolvable hostname rejected");
}

void test_net_resolve_invalid_format(void)
{
    struct sockaddr_in addr;

    int result = net_resolve("192.168.abc.1", 12345, &addr);
    assert_equal_int(result, -1, "non-numeric address rejected");

    result = net_resolve("999.999.999.999", 12345, &addr);
    assert_equal_int(result, -1, "invalid octet values rejected");
}

void test_net_resolve_too_long(void)
{
    struct sockaddr_in addr;
    char long_addr[256];
    memset(long_addr, '1', sizeof(long_addr) - 1);
    long_addr[sizeof(long_addr) - 1] = '\0';

    int result = net_resolve(long_addr, 12345, &addr);
    assert_equal_int(result, -1, "too long address rejected");
}

#endif
