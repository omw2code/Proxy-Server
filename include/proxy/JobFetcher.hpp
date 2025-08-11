#ifndef JOB_FETCHER_HPP_
#define JOB_FETCHER_HPP_

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <proxy/JobCache.hpp>
namespace proxy
{
    class JobFetcher
    {
    public:
        JobFetcher(boost::asio::io_context& context, std::shared_ptr<JobCache> cache);
        ~JobFetcher() = default;

        std::optional<std::string> findJob(const std::string& job);
        std::optional<std::pair<std::string_view, std::string_view>> splitJobQuery(std::string_view job) const;

    private:
        std::optional<std::string> querySQL(std::string_view job) const;
        std::optional<std::string> queryAPI(std::string_view job);

        std::string host_;
        std::string port_;
        std::string target_;
        boost::asio::io_context& ioc_;
        std::shared_ptr<JobCache> cache_;
    };
}

#endif