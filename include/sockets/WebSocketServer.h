#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <proxy/TcpServer.hpp>

namespace sockets
{

class WebSocketServer: public proxy::TcpServer
{
    WebSocketServer() = default;
    ~WebSocketServer();
};



}

#endif