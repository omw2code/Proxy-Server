#ifndef BOOST_SERVER_H_
#define BOOST_SERVER_H_

#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
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
                boost::asio::async_write(socket_, 
                    boost::asio::buffer(json_), 
                    boost::bind(&proxy::server::Connection::handleWrite,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));;

                boost::asio::async_read(socket_,
                        boost::asio::buffer(json_, max_length_),
                        boost::bind(&Connection::handleRead,
                                    shared_from_this(),
                                    boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred));
            }

        private:
            Connection(boost::asio::io_context& io_context)
                : socket_(io_context)
            {}

            void handleWrite(const boost::system::error_code& error, std::size_t bytes_transferred) 
            {
                // Implement
                return;
            }

            void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred)
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
    } 
}

#endif