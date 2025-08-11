#ifndef TCP_SERVER_HPP_
#define TCP_SERVEER_HPP_

#include <memory>
#include <proxy/Connection.hpp>

namespace proxy
{
    class TcpServer
    {
    public:
        TcpServer(boost::asio::io_context& io_context, short port) 
            : io_context_(io_context)
            , acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
            , cache_(std::make_shared<JobCache>())
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
        std::shared_ptr<JobCache> cache_;
    }; // class BoostServer
} // namespace proxy

#endif