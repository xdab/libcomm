#include "test.h"
#include "test_tcp.h"
#include "test_udp.h"
#include "test_uds.h"
#include "test_uds_dgram.h"
#include "test_poller.h"
#include "test_net.h"

int main(void)
{
    begin_suite();

    begin_module("Net");
    test_net_resolve_localhost();
    test_net_resolve_numeric_ip();
    test_net_resolve_empty_address();
    test_net_resolve_unresolvable();
    test_net_resolve_invalid_format();
    test_net_resolve_too_long();
    end_module();

    begin_module("TCP");
    test_tcp_server_init_valid();
    test_tcp_server_listen_timeout();
    test_tcp_server_accept_client();
    test_tcp_server_read_data();
    test_tcp_server_client_disconnect();
    test_tcp_server_broadcast();
    test_tcp_server_free();
    test_tcp_client_init_valid();
    test_tcp_client_init_invalid_address();
    test_tcp_client_listen_timeout();
    test_tcp_client_connect_and_read();
    test_tcp_client_server_disconnect();
    test_tcp_client_read_error();
    test_tcp_client_partial_read();
    test_tcp_client_connection_in_progress();
    test_tcp_client_write_error();
    test_tcp_client_free();
    test_tcp_client_send();
    end_module();

    begin_module("UDP");
    test_udp_sender_init_valid();
    test_udp_sender_init_broadcast();
    test_udp_sender_send_unicast();
    test_udp_sender_free();
    test_udp_sender_init_invalid_address();
    test_udp_sender_send_error();
    test_udp_sender_init_broadcast_config();
    test_udp_server_init_valid();
    test_udp_server_listen_timeout();
    test_udp_server_receive_data();
    test_udp_server_init_invalid_address();
    test_udp_server_free();
    end_module();

    begin_module("UDS");
    test_uds_server_init_valid();
    test_uds_server_listen_timeout();
    test_uds_server_accept_client();
    test_uds_server_read_data();
    test_uds_server_client_disconnect();
    test_uds_server_broadcast();
    test_uds_server_free();
    test_uds_server_init_invalid_path();
    test_uds_client_init_valid();
    test_uds_client_init_invalid_path();
    test_uds_client_listen_timeout();
    test_uds_client_connect_and_read();
    test_uds_client_server_disconnect();
    test_uds_client_read_error();
    test_uds_client_free();
    test_uds_client_partial_read();
    test_uds_client_connection_in_progress();
    test_uds_server_broadcast_two_clients();
    test_uds_client_send();
    end_module();

    begin_module("UDS Datagram");
    test_uds_dgram_sender_init_valid();
    test_uds_dgram_sender_init_invalid_path();
    test_uds_dgram_sender_send();
    test_uds_dgram_sender_send_empty();
    test_uds_dgram_sender_free();
    test_uds_dgram_server_init_valid();
    test_uds_dgram_server_init_timeout_ms_zero();
    test_uds_dgram_server_init_invalid_path();
    test_uds_dgram_server_listen_timeout();
    test_uds_dgram_server_listen_no_block();
    test_uds_dgram_server_free();
    test_uds_dgram_server_multiple_messages();
    end_module();

    begin_module("Poller");
    test_poller_create();
    test_poller_add_single();
    test_poller_add_multiple();
    test_poller_remove();
    test_poller_remove_nonexistent();
    test_poller_wait_timeout();
    test_poller_wait_ready();
    test_poller_is_ready();
    test_poller_is_ready_not_ready();
    test_poller_free();
    test_poller_mixed_events();
    end_module();

    int failed = end_suite();

    return failed ? 1 : 0;
}