#ifndef JOB_CACHE_H_
#define JOB_CACHE_H_

#include <unordered_map>
#include <string>
#include <optional>
#include <shared_mutex>
#include <chrono>

namespace proxy
{
    class JobCache
    {
    public:
        struct CacheHit
        {
            std::string jsonData;
            std::chrono::steady_clock::time_point ttl; // time to live 
        };

        JobCache(std::chrono::seconds ttl = std::chrono::seconds(300))
            : ttl_(ttl)
        {}
        
        ~JobCache();

        // check if in cache
        std::optional<std::string> get(std::string_view key);

        // put in cache, disk, and database
        void put(std::string_view key);

        // check if the cache is expired
        bool isExpired(std::chrono::steady_clock::time_point timePoint);

    private:
        // key -> job search values seperated by | delimiter
        // val -> previously searched job
        std::unordered_map<int, CacheHit> cache_;

        mutable std::shared_mutex cacheMutex_;
        
        std::chrono::seconds ttl_;
    }; // namespace server
} // namespace proxy

#endif