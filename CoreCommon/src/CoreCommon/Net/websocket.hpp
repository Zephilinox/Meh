#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include <asio.hpp>

namespace core::common::net
{
class Packet;

template<typename T>
class IWebSocket
{
public:
    IWebSocket() noexcept = delete;
    IWebSocket(IWebSocket&&) noexcept = delete;
    IWebSocket(const IWebSocket&) noexcept = delete;
    IWebSocket& operator=(IWebSocket&&) noexcept = delete;
    IWebSocket& operator=(const IWebSocket&) noexcept = delete;

    IWebSocket(T* delegate, asio::io_context ctx, asio::ip::tcp::socket sock);

    ~IWebSocket() noexcept = default;
    
    void connect(const asio::ip::tcp::resolver& endPoints);
    void disconnect();
    [[nodiscard]] bool isConnected() const { return socket.is_open(); }

    virtual void startListening() = 0;

    void send(Packet packet);
    void writeHeader();
    void writeBody();

    void readHeader();
    void readBody();

    [[nodiscard]] unsigned int getId() const { return id; }
private:
    asio::ip::tcp::socket socket;
    
    asio::io_context& context;

    unsigned int id;

    //TODO: Implement thread safe queue for incoming and outgoing messages.

    //the server or client so that we can process the packet and pass the information to them
    T* delegate;
};
}