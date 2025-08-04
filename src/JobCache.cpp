#include <proxy/JobCache.hpp>

namespace proxyServer = proxy::server;

proxyServer::JobCache::~JobCache()
{
    //Implement
}

std::optional<std::string> proxyServer::JobCache::get(std::string_view key)
{
    // Implement
    std::lock_guard<std::shared_mutex> lock(cacheMutex_);
}

void proxyServer::JobCache::put(std::string_view key)
{
    // Implement
    std::lock_guard<std::shared_mutex> lock(cacheMutex_);

}

bool proxyServer::JobCache::isExpired(std::chrono::steady_clock::time_point timePoint)
{
    // Implement
    return false;
}