#include <proxy/TcpServer.hpp>

void proxy::TcpServer::start_accept()
{
    Connection::ptr new_connection = Connection::create(io_context_, cache_);

    acceptor_.async_accept(new_connection->socket(), boost::bind(&TcpServer::handler, 
                                                                    this, 
                                                                    new_connection, 
                                                                    boost::asio::placeholders::error));
}

void proxy::TcpServer::handler(Connection::ptr new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }
    start_accept();
}
