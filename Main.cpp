#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "tcp_server.h"

using boost::asio::ip::tcp;

int _tmain(int argc, _TCHAR* argv[]) {
    int port;
    if (argc == 1) {
        port = 4444;
    } else if (argc == 2) {
        port = std::stoi(argv[1]);
    } else {
        std::cerr << "Usage: EchoServer [<port>]\n";
        return 1;
    }
    try {
        boost::asio::io_service io_service;
        tcp_server server(io_service, port);

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

