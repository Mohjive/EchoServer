#include <boost/bind.hpp>
#include "tcp_server.h"

tcp_server::tcp_server(boost::asio::io_service& io_service, short port):
                _io_service( io_service ),
                _acceptor( io_service,
                           tcp::endpoint(tcp::v4(), port) ) {
    new_accept();
}

void tcp_server::new_accept() {
    session* new_session = new session(_io_service);
    _acceptor.async_accept(new_session->socket(),
            boost::bind(&tcp_server::do_accept, this, new_session,
                        boost::asio::placeholders::error));
}

void tcp_server::do_accept(session* new_session,
                        const boost::system::error_code& error) {
    if (!error) {
        new_session->start();
    } else {
        delete new_session;
    }

    new_accept();
}
