add_library( server
  TcpServer.cpp
  JobCache.cpp
)

target_include_directories(server
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/>
  $<INSTALL_INTERFACE:include/>
)

add_executable(proxy_server main.cpp)
target_link_libraries(proxy_server PRIVATE server)