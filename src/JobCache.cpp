#include <proxy/JobCache.hpp>

std::optional<std::string> proxy::JobCache::get(const std::string& query)
{
    // Implementa
    std::shared_lock<std::shared_mutex> readerLock(cacheMutex_);
    auto iter = cache_.find(query);
    if (iter != cache_.end())
    {
        if (isExpired(iter->second.expireTime)) // TODO: periodically check for expired cache instead of this
        {
            readerLock.unlock();
            std::lock_guard<std::shared_mutex> writerLock(cacheMutex_);
            cache_.erase(iter);
            return std::nullopt;
        }
        return iter->second.jsonData;
    }
    return std::nullopt;
}

void proxy::JobCache::put(std::string_view key, std::string jsonData)
{
    std::lock_guard<std::shared_mutex> write(cacheMutex_);
    cache_[std::string(key)] = {std::move(jsonData), std::chrono::steady_clock::now() + default_ttl};
}

bool proxy::JobCache::isExpired(const std::chrono::steady_clock::time_point& timePoint)
{
    // Implement
    return timePoint <= std::chrono::steady_clock::now();
}