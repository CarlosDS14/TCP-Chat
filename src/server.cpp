#include "Package.h"
#include <iostream>
#include <thread>
//#include <sqlite3.h>
//#include <bcrypt.h>
#include <boost/asio.hpp>

const std::string serverip = "127.0.0.1";
const int serverport = 45455;

int main()
{
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint());
    return 0;
}