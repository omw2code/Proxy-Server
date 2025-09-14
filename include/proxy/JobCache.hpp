#ifndef JOB_CACHE_HPP_
#define JOB_CACHE_HPP_

#include <unordered_map>
#include <string>
#include <optional>
#include <shared_mutex>
#include <chrono>

// TODO: Make me a singleton please
namespace proxy
{

class JobCache
{
public:
    struct CacheHit
    {
        std::string jsonData;
        std::chrono::steady_clock::time_point expireTime; // time to live 
    };

    static constexpr std::chrono::minutes default_ttl{5};
    JobCache(std::chrono::minutes ttl = default_ttl)
        : cacheDuration_(ttl)
    {}
    
    ~JobCache() = default;

    // check if in cache
    std::optional<std::string> get(const std::string& query);

    // put in cache, disk, and database
    void put(std::string_view key, std::string jsonData);


    // check if the cache is expired
    static bool isExpired(const std::chrono::steady_clock::time_point& timePoint);

private:
    void proxy::JobCache::clearExpired(std::string& key);
    std::unordered_map<std::string, CacheHit> cache_;
    mutable std::shared_mutex cacheMutex_;
    std::chrono::seconds cacheDuration_;
}; // namespace server

} // namespace proxy

#endif