#pragma once

#include <cstdint>
#include <vector>

namespace meh::common::network
{
enum class MsgClientServer
{
    ClientServerBinaryBegin = 64,
    Ping = ClientServerBinaryBegin,
    Connect,
    Disconnect,
    Input
};

enum class MsgServerClient
{
    ServerClientBinaryBegin = 0,
    Pong = ServerClientbinaryBegin,
};

//Header of all packets
template <typename T>
struct PacketHeader
{
    T id{};
    uint32_t size = 0;
    long long timestamp;
};

template <typename T>
class Packet
{
    Packet() = delete;
    explicit Packet(const PacketHeader& header) : header(header) {}
    ~Packet() = default;
    
    void write(const void* src, size_t size)
    {
        if(src)
        {
            auto data = static_cast<uint8_t*>(src);
            body.insert(body.end(), data, data + size);
        }
        else
        {
            body.insert(body.end(), size, 0);
        }
        
        header.size += size;
    }
    
    template<typename T>
    void write(const T& src) { write(static_cast<void*>(src)); }
    template <typename T>
    void write(std::vector<T>& vec) { write(vec.data(), vec.size() * sizeof(T)) }

    size_t getSize() const { return sizeof(message_header<T>) + body.size(); }
    
    const PacketHeader& getHeader() const { return header; }
    
    bool empty() const { return body.empty() }
protected:
    PacketHeader<T> header;
    std::vector<uint8_t> body;
};
} // namespace meh::common::network