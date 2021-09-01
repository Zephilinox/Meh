#pragma once

//SELF

//LIBS

//STD
#include <functional>
#include <memory>

namespace core::common
{

template <typename... Args>
class Signal;

class Disconnector;

/*
 * Connection is returned by signal.connect()
 * Use it to control disconnecting your function from the signal
 * Similar to a raw pointer. if you do not manually disconnect, the connection will `leak`
 * A leaked connection is acceptable as long as the connected function (Slot) outlives the Signal
 *    e.g. a member function slot connected to a member variable signal
 */
class Connection
{
public:
    Connection() noexcept = default;
    Connection(const Connection& c) = default;
    Connection(Connection&& c) noexcept;
    Connection& operator=(const Connection& c) = default;
    Connection& operator=(Connection&& c) noexcept;
    virtual ~Connection() noexcept = default;

    //Check to see if the Connection is still valid
    operator bool() const noexcept;

    //Ensures both Connections are connected to the same Signal and referring to the same function
    //Might return false if both connections are invalid, depending on what made them invalid.
    friend bool operator==(const Connection& lhs, const Connection& rhs) noexcept
    {
        return lhs.slot_id == rhs.slot_id
               && lhs.weak_disconnector.lock().get() == rhs.weak_disconnector.lock().get();
    }

    friend bool operator!=(const Connection& lhs, const Connection& rhs) noexcept
    {
        return !operator==(lhs, rhs);
    }

    //Returns true if disconnection was successful
    //False if it was not, or if it's already disconnected
    bool disconnect();

private:
    //Signal needs to be able to create Connection with specific params
    //Clients should not be able to, as it means they can do random shit to a signal
    //Note: this means that a Signal<int> is a friend of Connection<bool>
    //But this shouldn't be a problem, since it's created based on the Signal <Args...>
    template <typename...>
    friend class Signal;

    //Only meant to be accessed by Signal
    Connection(std::weak_ptr<Disconnector> dc, unsigned id) noexcept;

    std::weak_ptr<Disconnector> weak_disconnector;
    unsigned slot_id = 0;
};

/*
 * Just a wrapper around Connection with RAII semantics. Automatically disconnects on destruction
 * Similar behaviour to std::shared_ptr
 */
class ManagedConnection final : public Connection
{
public:
    ManagedConnection() noexcept = default;
    explicit(false) ManagedConnection(const Connection& c);

    ManagedConnection(const ManagedConnection&) = default;
    ManagedConnection(ManagedConnection&& c) noexcept = default;
    ManagedConnection& operator=(const ManagedConnection& c) = default;
    ManagedConnection& operator=(ManagedConnection&& c) noexcept;

    ~ManagedConnection() noexcept;
};

} // namespace core::common