#include <iostream>
#include "Frontend.h"

using namespace std;

int main() {
    Frontend frontend(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8090));
    frontend.handle_connections();
}