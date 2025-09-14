add_library( server
  TcpServer.cpp
  JobCache.cpp
  JobFetcher.cpp
)

target_include_directories(server
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/>
  $<INSTALL_INTERFACE:include/>
)

add_executable(tcp_proxy_server main.cpp)
target_link_libraries(tcp_proxy_server PRIVATE server)