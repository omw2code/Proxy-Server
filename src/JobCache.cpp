#include <proxy/JobCache.hpp>

proxy::JobCache::~JobCache()
{
    //Implement
}

std::optional<std::string> proxy::JobCache::get(std::string_view key)
{
    // Implement
    std::lock_guard<std::shared_mutex> lock(cacheMutex_);
}

void proxy::JobCache::put(std::string_view key)
{
    // Implement
    std::lock_guard<std::shared_mutex> lock(cacheMutex_);

}

bool proxy::JobCache::isExpired(std::chrono::steady_clock::time_point timePoint)
{
    // Implement
    return false;
}