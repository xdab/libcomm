# libcomm

Networking and IPC utilities library aimed at reducing boilerplate code across simple projects.

## Features

- **TCP**: Client and server support with event callbacks
- **UDP**: Sender and server (connectionless packet I/O)
- **Unix Domain Sockets**: Local inter-process communication (stream and datagram)
- **Socket Poller**: epoll-based multi-FD polling for efficient I/O multiplexing

## Build

```sh
make build    # Debug build
make release  # Release build
make test     # Run unit tests
make install  # Install to system
make clean    # Clean build artifacts
make echo     # Runs demo echo server
```

## Usage

### Networking and IPC

```c
tcp_server_t server;
tcp_server_init(&server, 8000, 50);
tcp_server_listen(&server, &buf);

tcp_client_t client;
tcp_client_init(&client, "192.168.1.1", 8000, 50);
tcp_client_send(&client, &buf);
tcp_client_listen(&client, &buf);

udp_sender_t sender;
udp_sender_init(&sender, "192.168.1.1", 9000);
udp_sender_send(&sender, &buf);

udp_server_t udp_srv;
udp_server_init(&udp_srv, 9000, 50);
udp_server_listen(&udp_srv, &buf);
```

### Unix IPC

```c
uds_server_t uds_srv;
uds_server_init(&uds_srv, "/tmp/my.sock", 50);
uds_server_listen(&uds_srv, &buf);

uds_dgram_sender_t uds_snd;
uds_dgram_sender_init(&uds_snd, "/tmp/server.sock");
uds_dgram_sender_send(&uds_snd, &buf);

uds_dgram_server_t uds_dgram_srv;
uds_dgram_server_init(&uds_dgram_srv, "/tmp/dgram.sock", 50);
uds_dgram_server_listen(&uds_dgram_srv, &buf);
```

### Multi-Socket Polling

```c
socket_poller_t pol;
socket_poller_init(&pol);
socket_poller_add(&pol, tcp_server.listen_fd, POLLER_EV_IN);
socket_poller_add(&pol, udp_server.fd, POLLER_EV_IN);
socket_poller_add(&pol, client_fd, POLLER_EV_IN | POLLER_EV_OUT);

while (1) {
    int ready = socket_poller_wait(&pol, 100);
    if (ready > 0) {
        if (socket_poller_is_ready(&pol, tcp_server.listen_fd))
            tcp_server_listen(&server, &buf);
        if (socket_poller_is_ready(&pol, udp_server.fd))
            udp_server_listen(&udp_server, &buf);
        if (socket_poller_is_ready(&pol, client_fd))
            handle_client(&client);
    }
}
socket_poller_free(&pol);
```

## Demo program

See `src/libtnc_echo.c` for a complete multi-protocol echo server demonstrating TCP/UDP clients and servers as well as all variants of Unix socket IPC (connected and connectionless).

## Dependencies

- Standard C library
