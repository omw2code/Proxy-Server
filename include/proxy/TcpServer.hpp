#ifndef TCP_SERVER_H_
#define TCP_SERVEER_H_

#include <proxy/Connection.hpp>

namespace proxy
{
    class TcpServer
    {
    public:
        TcpServer(boost::asio::io_context& io_context, short port) 
            : io_context_(io_context),
                acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
            {
                start_accept();
            }
        ~TcpServer() = default;

        // Open requests from the client
        void start_accept();

        // Handle the new connection to the server
        void handler(Connection::ptr new_connection, const boost::system::error_code& error);
    
    private:
        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
    }; // class BoostServer
} // namespace proxy

#endif