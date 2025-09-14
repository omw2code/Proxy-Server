#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace WebSockets
{

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;

class WebSocketServer
{
public:
    WebSocketServer(boost::asio::io_context &io_context, short port)
    : io_context_(io_context)
    , port_(port)
    {
        run_server();
    }

    void run_server();
    void socket_session(tcp::socket web_socket);
    ~WebSocketServer();

private:
    boost::asio::io_context io_context_;
    short port_;
};



}

#endif