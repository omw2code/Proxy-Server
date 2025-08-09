#ifndef JOB_FETCHER_HPP_
#define JOB_FETCHER_HPP_

#include <optional>
#include <proxy/JobCache.hpp>
namespace proxy
{
    class JobFetcher
    {
    public:
        JobFetcher() = default;
        ~JobFetcher() = default;

        std::optional<std::string> queryJob(const std::string& query) const;
    private:
        const JobCache cache_;
    };
}

#endif