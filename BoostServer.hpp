#ifndef BOOST_SERVER_H_
#define BOOST_SERVER_H_

#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr/enable_shared_from.hpp>
#include <boost/asio/ip/tcp.hpp> 

namespace proxy
{
    namespace server
    {
        class Connection : public boost::enable_shared_from_this<Connection>
        {
        public:
            typedef boost::shared_ptr<Connection> ptr;

            static ptr create(boost::asio::io_context& io_context)
            {
                return ptr(new Connection(io_context));
            }

            boost::asio::ip::tcp::socket& socket()
            {
                return socket_;
            }
            void start()
            {
                boost::asio::async_write(socket_, boost::asio::buffer(json_), boost::bind(handleWrite));
                boost::asio::async_read(socket_, boost::asio::buffer(json_, max_length_), boost::bind(&handleRead,json_, max_length_));
            }

        private:
            Connection(boost::asio::io_context& io_context)
                : socket_(io_context)
            {}

            void handleWrite() 
            {
                // Implement
            }

            void handleRead(char &search, int max_length)
            {
                std::unique_lock<std::mutex> lock(connectionMutext_, std::adopt_lock);
                // Need to now query the api

                // get the data

            }
            
            boost::asio::ip::tcp::socket socket_;
            static constexpr int max_length_{ 1024 };
            char json_[max_length_];
            std::mutex connectionMutext_;
        }; // class Connection

        class TcpServer
        {
        public:
            TcpServer(boost::asio::io_context& io_context, short port) 
                : io_context_(io_context),
                  acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
                {
                    start_accept();
                }

            void start_accept()
            {
                Connection::ptr new_connection = Connection::create(io_context_);

                acceptor_.async_accept(new_connection->socket(), boost::bind(&TcpServer::handler, 
                                                                             this, 
                                                                             new_connection, 
                                                                             boost::asio::placeholders::error));
            }

            void handler(Connection::ptr new_connection, const boost::system::error_code& error)
            {
                if (!error)
                {
                    new_connection->start();
                }
                start_accept();
            }
            
            ~TcpServer() = default;
        
        private:
            boost::asio::io_context& io_context_;
            boost::asio::ip::tcp::acceptor acceptor_;
        }; // class BoostServer
    } 
}

#endif