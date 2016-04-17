//
// Created by pavelgolubev345 on 11.04.16.
//

#ifndef GOGAMESERVER_FRONTEND_H
#define GOGAMESERVER_FRONTEND_H

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <utility>
#include <cstdlib>
#include "Backend.h"


class Frontend {
private:
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint ep;
    Backend* backend;
    Frontend() = default;
public:
    Frontend(boost::asio::ip::tcp::endpoint ep, int playerAmount);
    void handle_connections();
    ~Frontend();
};


#endif //GOGAMESERVER_FRONTEND_H
