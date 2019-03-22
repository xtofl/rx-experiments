#include <cstdio>
#include <sstream>
#include "rxcpp/rx.hpp"
#include "boost/asio.hpp"
#include "boost/asio/async_result.hpp"



namespace Rx {
using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;
}
using namespace Rx;


int main() {
    puts("Starting Chatroom\n");
    using namespace boost::asio::ip;
    boost::asio::io_service context;
 
    context.post([&]{
        tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 2000));
        auto socket = std::make_shared<tcp::socket>(context);
        acceptor.async_accept(
            *socket,
            [socket=std::move(socket), &context] (auto &error)
        {
            if(error) return;
            auto r = context.post([socket=std::move(socket)]
            {
                auto buffer = std::make_shared<boost::asio::streambuf>();

                auto r = boost::asio::async_read(*socket, *buffer, [buffer=std::move(buffer)]
                (const auto &error, const auto number_of_bytes)
                {
                    printf("%lu bytes READ\n", number_of_bytes);
                });
                puts("CONNECTED!\n");
                return r;
            });
            return r;
        });
        puts("Accepted\n");
    });
    context.run();
    puts("Closed Chatroom\n");
}
