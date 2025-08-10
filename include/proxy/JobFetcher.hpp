#ifndef JOB_FETCHER_HPP_
#define JOB_FETCHER_HPP_

#include <optional>
#include <proxy/JobCache.hpp>
namespace proxy
{
    class JobFetcher
    {
    public:
        JobFetcher(boost::asio::io_context& context);
        ~JobFetcher();

        std::optional<std::string> queryJob(const std::string& what, const std::string& where) const;
    private:
        void unFoldRequest(std::string& json);
        void unFoldResponse(std::string& json);

        std::string_view host_;
        std::string_view port_;
        std::string_view target_;
        std::string_view appKey_;
        std::string_view appID_;
        std::string_view what_;
        std::string_view where_;
        boost::asio::io_context& ioc_;
        const JobCache cache_;
    };
}

#endif