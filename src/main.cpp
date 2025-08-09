#include <iostream>
#include <memory>
#include <proxy/TcpServer.hpp>

int main(int argc, char** argv)
{
    boost::asio::io_context context; 
    std::unique_ptr<proxy::TcpServer> server = std::make_unique<proxy::TcpServer>(context, 8080);
    return 0;
}