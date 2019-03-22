#include <cstdio>
#include "rxcpp/rx.hpp"
#include "boost/asio.hpp"


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
        auto connection = tcp::socket(context);
        acceptor.async_accept(connection,
                              [&](auto &error) {});
        puts("Accepted\n");
    });
    context.run();
    puts("Closed Chatroom\n");
}
