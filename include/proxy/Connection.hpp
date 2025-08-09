#ifndef BOOST_SERVER_HPP_
#define BOOST_SERVER_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <shared_mutex>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/smart_ptr/enable_shared_from.hpp>
#include <boost/asio/ip/tcp.hpp> 
#include <proxy/JobCache.hpp>
#include <proxy/JobFetcher.hpp>

namespace proxy
{
    class Connection : public boost::enable_shared_from_this<Connection>
    {
    public:
        typedef boost::shared_ptr<Connection> ptr;

        // create a new connection to our server
        static ptr create(boost::asio::io_context& io_context)
        {
            return ptr(new Connection(io_context));
        }

        // grab the socket of this connection
        boost::asio::ip::tcp::socket& socket()
        {
            return socket_;
        }

        // enable reading and writing with this connection to the server
        void start()
        {
            boost::asio::async_write(socket_, 
                boost::asio::buffer(data_), 
                boost::bind(&proxy::Connection::handleWrite,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));;

            boost::asio::async_read(socket_,
                    boost::asio::buffer(data_, max_length_),
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
            // Convert bytes transfer
            return;
        }

        void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            std::unique_lock<std::shared_mutex> lock(connectionMutext_, std::adopt_lock);
            // Need to now query the api

            // construct our string
            const std::string job(data_, bytes_transferred);

            if (cache_.get(job).has_value()) {
                // writer back our json str to the client
            }
            else {
                auto error = jobFetcher_.queryJob(job);
            }
        }

        boost::asio::ip::tcp::socket socket_;
        static constexpr int max_length_{ 1024 };
        char data_[max_length_];
        std::shared_mutex connectionMutext_;
        const JobCache cache_;
        const JobFetcher jobFetcher_;

    }; // class Connection
} // namespace proxy

#endif