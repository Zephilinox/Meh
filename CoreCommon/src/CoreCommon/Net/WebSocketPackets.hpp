#pragma once

#include <cstdint>
#include <vector>

namespace core::common::net
{
enum class MsgCoreClientServer
{
    ClientServerBinaryBegin = 64,
    Ping = ClientServerBinaryBegin,
    Connect,
    Disconnect,
    Input
};

enum class MsgCoreServerClient
{
    ServerClientBinaryBegin = 0,
    Pong = ServerClientBinaryBegin,
};

//Header of all packets
template <typename T>
struct PacketHeader
{
    T id{};
    long long timestamp = -1;
    uint32_t size = sizeof(PacketHeader);
};

template <typename T>
class Packet
{
public:
    Packet() noexcept = delete;
    Packet(Packet&&) noexcept = delete;
    Packet(const Packet&) noexcept = delete;
    Packet& operator=(Packet&&) noexcept = delete;
    Packet& operator=(const Packet&) noexcept = delete;
    
    explicit Packet(const PacketHeader<T>& header) : header(header) {}
    
    virtual ~Packet() noexcept = default;
    
    void write(const void* src, size_t size)
    {
        if(src)
        {
            const auto* data = static_cast<const uint8_t*>(src);
            body.insert(body.end(), data, data + size); // NOLINT
        }
        else
        {
            body.insert(body.end(), size, 0);
        }
        
        header.size += static_cast<uint32_t>(size);
    }
    
    template<typename T2>
    void write(const T2& src) { write(static_cast<void*>(src)); }
    template <typename T3>
    void write(std::vector<T3>& vec) { write(vec.data(), vec.size() * sizeof(T)); }
    
    [[nodiscard]]size_t getSize() const { return sizeof(header) + body.size(); }
    
    [[nodiscard]] const PacketHeader<T>& getHeader() const { return header; }
    
    [[nodiscard]] const auto& getBody() const { return body; }
    
    [[nodiscard]] bool empty() const { return body.empty(); }
    
private:
    PacketHeader<T> header{};
    std::vector<uint8_t> body;
};
} // namespace meh::common::network