#include "Connection.hpp"

//SELF
#include "Disconnector.hpp"

//LIBS

//STD

using namespace meh::common;

Connection::operator bool() const noexcept
{
    return slot_id != 0 && !weak_disconnector.expired();
}

Connection::Connection(Connection&& c) noexcept
    : weak_disconnector(std::move(c.weak_disconnector))
    , slot_id(c.slot_id)
{
    c.slot_id = 0;
}

Connection& Connection::operator=(Connection&& c) noexcept
{
    if (this == &c)
        return *this;

    weak_disconnector = std::move(c.weak_disconnector);
    slot_id = c.slot_id;
    c.slot_id = 0;

    return *this;
}

bool Connection::disconnect()
{
    auto disconnector = weak_disconnector.lock();
    if (!disconnector)
    {
        weak_disconnector.reset();
        slot_id = 0;
        return false;
    }

    const bool was_connected = disconnector->disconnect(*this);
    weak_disconnector.reset();
    slot_id = 0;
    return was_connected;
}

//private
Connection::Connection(std::weak_ptr<Disconnector> dc, unsigned id) noexcept
    : weak_disconnector(std::move(dc))
    , slot_id(id)
{
}

ManagedConnection::ManagedConnection(const Connection& c)
    : Connection(c)
{
}

ManagedConnection& ManagedConnection::operator=(ManagedConnection&& c) noexcept
{
    //Don't disconnect if we're moving ourselves in to ourselves.
    if (this == &c)
        return *this;

    //Disconnect whatever connection we may currently be managing
    disconnect();

    //Call base move assignment operator
    Connection::operator=(std::move(c));

    return *this;
}

ManagedConnection::~ManagedConnection() noexcept
{
    disconnect();
}