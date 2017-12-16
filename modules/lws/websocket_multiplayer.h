#ifndef WEBSOCKET_MULTIPLAYER_PEER_H
#define WEBSOCKET_MULTIPLAYER_PEER_H

#include "core/error_list.h"
#include "core/io/networked_multiplayer_peer.h"
#include "core/list.h"
#include "websocket_peer.h"

class WebSocketMultiplayerPeer : public NetworkedMultiplayerPeer {

	GDCLASS(WebSocketMultiplayerPeer, NetworkedMultiplayerPeer);

protected:
	enum {
		SYS_NONE = 0,
		SYS_ADD = 1,
		SYS_DEL = 2,
		SYS_ID = 3,

		PROTO_SIZE = 9,
		SYS_PACKET_SIZE = 13,
		MAX_PACKET_SIZE = 65536 - 14 // 5 websocket, 9 multiplayer
	};

	struct Packet {
		int source;
		int destination;
		uint8_t *data;
		uint32_t size;
	};

	List<Packet> _incoming_packets;
	Map<int, Ref<WebSocketPeer> > _peer_map;
	Packet _current_packet;

	bool _is_multiplayer;
	int _target_peer;
	int _peer_id;
	int _refusing;

	static void _bind_methods();

public:
	/* NetworkedMultiplayerPeer */
	void set_transfer_mode(TransferMode p_mode);
	void set_target_peer(int p_peer_id);
	int get_packet_peer() const;
	int get_unique_id() const;
	bool is_server() const;
	void set_refuse_new_connections(bool p_enable);
	bool is_refusing_new_connections() const;
	virtual ConnectionStatus get_connection_status() const = 0;

	/* PacketPeer */
	virtual int get_available_packet_count() const;
	virtual int get_max_packet_size() const;
	virtual Error get_packet(const uint8_t **r_buffer, int &r_buffer_size);
	virtual Error put_packet(const uint8_t *p_buffer, int p_buffer_size);

	/* WebSocketPeer */
	virtual Ref<WebSocketPeer> get_peer(int p_peer_id) const = 0;

	void _send_sys(Ref<WebSocketPeer> p_peer, uint8_t p_type, uint32_t p_peer_id);
	void _send_add(uint32_t p_peer_id);
	void _send_del(uint32_t p_peer_id);
	void _process_multiplayer(Ref<WebSocketPeer> p_peer);
	void _clear();

	WebSocketMultiplayerPeer();
	~WebSocketMultiplayerPeer();
};

#endif // WEBSOCKET_MULTIPLAYER_PEER_H