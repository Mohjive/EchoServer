#include <boost/bind.hpp>
#include "session.h"

session::session(boost::asio::io_service& io_service): _socket(io_service) {
}

tcp::socket& session::socket() {
    return _socket;
}

void session::start() {
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void session::handle_read(const boost::system::error_code& error,
                        size_t bytes_transferred) {
    if (error) {
        delete this;
    } else {
        boost::asio::async_write(_socket,
                            boost::asio::buffer(_data, bytes_transferred),
                            boost::bind(&session::handle_write, this,
                            boost::asio::placeholders::error));
    }
}

void session::handle_write(const boost::system::error_code& error) {
    if (error) {
        delete this;
    } else {
        _socket.async_read_some(boost::asio::buffer(_data, max_length),
                            boost::bind(&session::handle_read, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }
}
