add_library( web_server
  WebSocketServer.cpp
  WebSocketClient.cpp
  Session.cpp
)

target_include_directories(web_server
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/>
  $<INSTALL_INTERFACE:include/>
)

add_executable(web_socket_server main.cpp)
target_link_libraries(web_socket_server PRIVATE webServer)