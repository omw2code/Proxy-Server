#include <cstdlib>
#include <proxy/JobFetcher.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

proxy::JobFetcher::JobFetcher(boost::asio::io_context& context) 
    : host_(std::getenv("HOST"))
    , port_(std::getenv("PORT"))
    , target_(std::getenv("TARGET"))
    , appKey_(std::getenv("APP_KEY"))
    , appID_(std::getenv("APP_ID"))
    , ioc_(context)
{}

proxy::JobFetcher::~JobFetcher()
{}

std::optional<std::string> proxy::JobFetcher::queryJob(const std::string& what, const std::string& where) const
{
    namespace http = boost::beast::http;
    namespace beast = boost::beast;
    namespace http = boost::beast::http;
    using tcp = boost::asio::ip::tcp;

    try
    {      
        // Resolve the host and port and connect TCP stream
        tcp::resolver resolver(ioc_);
        boost::beast::tcp_stream stream(ioc_);
        auto const results = resolver.resolve(host_, port_);
        stream.connect(results);
        
        // Send HTTP request
        http::request<http::string_body> req{boost::beast::http::verb::get, target_, 11};
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
            // throw beast::system_error{e};
        } 
        return beast::buffers_to_string(res.body().data());   
    }
    catch(const std::exception& e)
    {
        // TODO: Log information here
        return std::nullopt;
    }
}

void proxy::JobFetcher::unFoldRequest(std::string& json)
{
    // what_ 
    // where_
}

void proxy::JobFetcher::unFoldResponse(std::string& json)
{

}
