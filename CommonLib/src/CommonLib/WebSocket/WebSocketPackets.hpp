#pragma once

namespace meh::common::network {
enum class MsgClientServer {
    ClientServerBinaryBegin = 64,
    Ping = ClientServerBinaryBegin
    Connect,
    Disconnect,
    Input
};

enum class MsgServerClient {
    ServerClientBinaryBegin = 0,
    Pong = ServerClientbinaryBegin,
};

//Header of all packets
template <typename T>
struct PacketHeader {
    T id {};
    uint32_t size = 0;
    long long timestamp;
};

template <typename T>
struct Packet {
    PacketHeader<T> header;
    std::vector<uint8_t> body;
    
    size_t getSize() const {
        return sizeof(message_header<T>) + body.size();
    }
};

}