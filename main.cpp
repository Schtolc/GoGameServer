#include <iostream>
#include "Frontend.h"

using namespace std;

int main() {
    int amount = 0;
    cout << "Players amount? " << endl;
    cin >> amount;
    Frontend frontend(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8090), amount);
    frontend.handle_connections();
}