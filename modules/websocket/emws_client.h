#ifndef EMWSCLIENT_H
#define EMWSCLIENT_H

#ifdef JAVASCRIPT_ENABLED

#include "core/error_list.h"
#include "emws_peer.h"
#include "websocket_client.h"

class EMWSClient : public WebSocketClient {

	GDCIIMPL(EMWSClient, WebSocketClient);

private:
	int _js_id;

public:
	bool _is_connecting;

	Error connect_to_host(String p_host, String p_path, uint16_t p_port, bool p_ssl, PoolVector<String> p_protocol = PoolVector<String>());
	Ref<WebSocketPeer> get_peer(int p_peer_id) const;
	void disconnect_from_host();
	IP_Address get_connected_host() const;
	uint16_t get_connected_port() const;
	virtual ConnectionStatus get_connection_status() const;
	virtual void poll();
	EMWSClient();
	~EMWSClient();
};

#endif // JAVASCRIPT_ENABLED

#endif // EMWSCLIENT_H
