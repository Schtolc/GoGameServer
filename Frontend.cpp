//
// Created by pavelgolubev345 on 11.04.16.
//

#include "Frontend.h"

Frontend::Frontend(boost::asio::ip::tcp::endpoint endpoint, int playerAmount) : io_service(), ep(endpoint) {
    backend = new Backend(playerAmount);
}

void Frontend::handle_connections() {
    boost::asio::ip::tcp::acceptor acceptor(io_service, ep);

    try {
        while(true) {
            boost::asio::ip::tcp::socket sock(io_service);
            acceptor.accept(sock);
            std::array<int, BUFFER_SIZE> data;
            boost::system::error_code error;

            sock.read_some(boost::asio::buffer(data), error);
            std::array<int, BUFFER_SIZE> response = backend->handle_request(data);


            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);

            sock.write_some(boost::asio::buffer(response));
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

Frontend::~Frontend() {
    delete backend;
}
