#pragma once
struct gamepacket_t
{
private:
	int index = 0;
	int len = 0;
	byte* packet_data = new byte[61];

public:
	gamepacket_t(int delay = 0, int NetID = -1) {

		len = 61;
		int MessageType = 0x4;
		int PacketType = 0x1;
		int CharState = 0x8;

		memset(packet_data, 0, 61);
		memcpy(packet_data, &MessageType, 4);
		memcpy(packet_data + 4, &PacketType, 4);
		memcpy(packet_data + 8, &NetID, 4);
		memcpy(packet_data + 16, &CharState, 4);
		memcpy(packet_data + 24, &delay, 4);
	};
	~gamepacket_t() {
		delete[] packet_data;
	}

	void Insert(string a) {
		byte* data = new byte[len + 2 + a.length() + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x2;
		int str_len = a.length();
		memcpy(data + len + 2, &str_len, 4);
		memcpy(data + len + 6, a.data(), str_len);
		len = len + 2 + a.length() + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(int a) {
		byte* data = new byte[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x9;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(unsigned int a) {
		byte* data = new byte[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x5;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(float a) {
		byte* data = new byte[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x1;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(float a, float b) {
		byte* data = new byte[len + 2 + 8];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x3;
		memcpy(data + len + 2, &a, 4);
		memcpy(data + len + 6, &b, 4);
		len = len + 2 + 8;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(float a, float b, float c) {
		byte* data = new byte[len + 2 + 12];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x4;
		memcpy(data + len + 2, &a, 4);
		memcpy(data + len + 6, &b, 4);
		memcpy(data + len + 10, &c, 4);
		len = len + 2 + 12;
		index++;
		packet_data[60] = (byte)index;
	}
	void CreatePacket(ENetPeer* peer) {
		ENetPacket* packet = enet_packet_create(packet_data, len, 1);
		enet_peer_send(peer, 0, packet);
	}
};

namespace Server {
	namespace Variant {
		void OnNameChanged(ENetPeer* peer_, string name) {
			gamepacket_t p;
			p.Insert("OnNameChanged");
			p.Insert(name);
			p.CreatePacket(peer_);
		}
		void OnAddNotification(ENetPeer* peer_, string banner, string message, string audio, int display) {
			gamepacket_t p;
			p.Insert("OnAddNotification");
			p.Insert(banner);
			p.Insert(message);
			p.Insert(audio);
			p.Insert(display);
			p.CreatePacket(peer_);
		}
		void OnConsoleMessage(ENetPeer* peer, string message) {
			gamepacket_t p;
			p.Insert("OnConsoleMessage");
			p.Insert(message);
			p.CreatePacket(peer);
		}
		void OnDialogRequest(ENetPeer* peer, string message) {
			gamepacket_t p;
			p.Insert("OnDialogRequest");
			p.Insert(message);
			p.CreatePacket(peer);
		}
		void OnSpawn(ENetPeer* peer, string message) {
			gamepacket_t p;
			p.Insert("OnSpawn");
			p.Insert(message);
			p.CreatePacket(peer);
		}
		void OnRequestWorldSelectMenu(ENetPeer* peer, string message) {
			gamepacket_t p;
			p.Insert("OnRequestWorldSelectMenu");
			p.Insert(message);
			p.CreatePacket(peer);
		}
		void OnStoreRequest(ENetPeer* peer, string message) {
			gamepacket_t p;
			p.Insert("OnStoreRequest");
			p.Insert(message);
			p.CreatePacket(peer);
		}
		void OnStorePurchaseResult(ENetPeer* peer, string message) {
			gamepacket_t p;
			p.Insert("OnStorePurchaseResult");
			p.Insert(message);
			p.CreatePacket(peer);
		}
	}
}