#include <CoreCommon/Net/WebSocketPackets.hpp>

//LIBS
#include <doctest/doctest.h>

using namespace core::common; // NOLINT

TEST_CASE("Net/WebSocketPacket can write to packet")
{
    
    net::PacketHeader<net::MsgCoreClientServer> header = { net::MsgCoreClientServer::Ping, 1000LL };
    net::Packet packet(header);
    CHECK(packet.getHeader().id == net::MsgCoreClientServer::Ping);
    
    //Add some data
    const std::string data = "This is some data\n";
    packet.write(data.data(), data.size());
    CHECK(packet.getHeader().size == sizeof(net::PacketHeader<net::MsgCoreClientServer>) + data.size());
    const auto packetData = std::string(reinterpret_cast<const char*>(packet.getBody().data()), packet.getBody().size());   // NOLINT
    CHECK(data == packetData);
}