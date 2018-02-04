#ifndef __tcp_server_h__
#define __tcp_server_h__
#include <boost/asio.hpp>

#include "session.h"

using boost::asio::ip::tcp;

class tcp_server {
public:
    tcp_server(boost::asio::io_service& io_service, short port);

private:
    boost::asio::io_service& _io_service;
    tcp::acceptor _acceptor;

    void new_accept(void);

    void do_accept(session* new_session,
                        const boost::system::error_code& error);
};
#endif //__tcp_server_h__
