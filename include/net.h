#pragma once

#include <netinet/in.h>

int net_resolve(const char *host, int port, struct sockaddr_in *out_addr);
