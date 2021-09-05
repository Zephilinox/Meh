#include "websocket.hpp"

#include "websocket

#include <spdlog/spdlog.h>
#define ASIO_STANDALONE
#include <asio.hpp>

namespace core::common::net
{
template<typename T>
IWebSocket<T>::IWebSocket(T* delegate, asio::io_context ctx, asio::ip::tcp::socket sock)
: context(ctx), socket(std::move(sock))
{

}

template<typename T>
void IWebSocket<T>::connect(const asio::ip::tcp::resolver& endPoints)
{
    asio::async_connect(socket, endPoints, [this](std::error_code ec, asio::ip::tcp::endpoint endPoint)
        {
            if(!ec)
                spdlog::info("Connecting");
        });
}

template<typename T>
void IWebSocket<T>::disconnect()
{
    if(isConnected())
        asio::post(context, [this] () { socket.close(); });
}
template <typename T>
void IWebSocket<T>::send(Packet& packet)
{
    asio::post(context [this, packet]
    {
        //do something herer
    });
}
}