#include <cstdlib>
#include <proxy/JobFetcher.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/json.hpp>

proxy::JobFetcher::JobFetcher(boost::asio::io_context& context, std::shared_ptr<JobCache> cache) 
    : host_(std::string(std::getenv("HOST")))
    , port_(std::string(std::getenv("PORT")))
    , target_(std::string(std::getenv("TARGET")))
    , ioc_(context)
    , cache_(cache)
{}

std::optional<std::string> proxy::JobFetcher::findJob(const std::string& job)
{
    // string coming in looks like: "JOB|location"
    if (auto e = cache_.get()->get(job); e) return e;
    if (auto e = querySQL(job); e.has_value()) return e;
    if (auto e = queryAPI(job); e.has_value()) return e;
    
    return std::nullopt;
}

std::optional<std::string> proxy::JobFetcher::querySQL(std::string_view job) const
{
    // Make sure thread safe
    return std::nullopt;
}


std::optional<std::string> proxy::JobFetcher::queryAPI(std::string_view job)
{
    // TODO: Handle returning on random input from user
    namespace http = boost::beast::http;
    namespace beast = boost::beast;
    using tcp = boost::asio::ip::tcp;

    try
    {      
        auto jobParsed = splitJobQuery(job);
        if (!jobParsed)
            // TODO: log information here
            return std::nullopt;
        auto [what, where] = *jobParsed;

        // Resolve the host and port and connect TCP stream
        tcp::resolver resolver(ioc_);
        boost::beast::tcp_stream stream(ioc_);
        auto const results = resolver.resolve(host_, port_);
        stream.connect(results);
        
        // Construct the query
        auto target = target_;
        target.append("&what=").append(what)
              .append("&where=").append(where);

        // Send HTTP request
        http::request<http::string_body> req{boost::beast::http::verb::get, target, 11};
        req.set(http::field::host, host_);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        http::write(stream, req);
        
        //Receive HTTP response
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        beast::error_code e;    
        http::read(stream, buffer, res);

        // Close connection
        stream.socket().shutdown(tcp::socket::shutdown_both, e);
    
        if (e && e != beast::errc::not_connected) 
        {
            // TODO: Turn this into logged information  
            return std::nullopt;
        }

        auto jsonStr = beast::buffers_to_string(res.body().data());
        cache_.get()->put(job, jsonStr);
        return jsonStr;
    }
    catch(const std::exception& e)
    {
        // TODO: Log information here
        return std::nullopt;
    }
}

std::optional<std::pair<std::string_view, std::string_view>> proxy::JobFetcher::splitJobQuery(std::string_view job) const
{
    auto delim_pos = job.find('|', 0);
    if (delim_pos == std::string_view::npos) return std::nullopt;
    return std::make_pair(job.substr(0, delim_pos), job.substr(delim_pos + 1));
}