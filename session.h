#ifndef __session_h__
#define __session_h__
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session {
public:
    session(boost::asio::io_service& io_service);
    tcp::socket& socket();
    void start();

private:
    tcp::socket _socket;
    enum { max_length = 1024 };
    char _data[max_length];

    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);
};

#endif //__session_h__
