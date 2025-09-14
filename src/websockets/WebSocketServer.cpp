#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <websockets/WebSocketServer.h>

void WebSockets::WebSocketServer::run_server()
{
    tcp::acceptor acceptor{io_context_, tcp::endpoint(tcp::v4(), port_)};
    tcp::socket web_socket{io_context_};
    acceptor.async_accept()
}

void WebSockets::WebSocketServer::socket_session(tcp::socket &web_socket)
{
    
}