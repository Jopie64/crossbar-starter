#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <sstream>
#include <cstdlib>

#include <boost/asio.hpp>

#include <autobahn/autobahn.hpp>


void log (const std::string& msg) {
    std::cerr << msg << " [thread " << boost::this_thread::get_id() << "]" << std::endl;
}


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: callee <RawSocket IP> <RawSocket PORT>" << std::endl;
        return -1;
    }

    try {
        log("starting program ..");

        boost::asio::io_service io;

        bool debug = false;

        boost::future<void> f1, f2, f3;

        auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(argv[1]), atoi(argv[2]));

        auto transport = std::make_shared<autobahn::wamp_tcp_transport>(io, endpoint, debug);

        auto session = std::make_shared<autobahn::wamp_session>(io, debug);

        transport->attach(std::static_pointer_cast<autobahn::wamp_transport_handler>(session));

        f1 = transport->connect().then([&](boost::future<void> connected) {

            connected.get();

            log("transport connected");

            f2 = session->start().then(boost::launch::deferred,
                                       [&](boost::future<void> started) {

                started.get();

                log("session started");

                f3 = session->join("realm1").then(boost::launch::deferred,
                                                  [&](boost::future<uint64_t> joined) {

                    joined.get();

                    log("joined realm");

                    auto f4 = session->leave().then(boost::launch::deferred,
                                                    [&](boost::future<std::string> reason) {
                        log("session left");

                        io.stop();
                    });
                    f4.get();
                });
                f3.get();
            });
            f2.get();
        });

        log("starting io service ..");
        io.run();
        log("stopped io service");
    }
    catch (const std::exception& e) {
        log(e.what());
        return -1;
    }

    return 0;
}
