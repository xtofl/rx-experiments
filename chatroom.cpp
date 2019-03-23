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

    tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 2000));
    context.post([&context, &acceptor]{
        auto socket = std::make_shared<tcp::socket>(context);
        acceptor.async_accept(
            *socket,
            [socket, &context] (auto &error)
        {
            if(error) return;

            context.post([socket=std::move(socket)]
            {
                auto buffer = std::make_shared<boost::asio::streambuf>();

                boost::asio::async_read(*socket, *buffer, [buffer]
                (const auto &error, const auto number_of_bytes)
                {
                    printf("%lu bytes READ\n", number_of_bytes);
                    puts(boost::asio::buffer_cast<const char*>(buffer->data()));
                });
                puts("CONNECTED!\n");
            });
        });
        puts("Accepted\n");
    });
    context.run();
    puts("Closed Chatroom\n");
}
