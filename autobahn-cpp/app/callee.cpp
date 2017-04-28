#include <iostream>
#include <memory>
#include <string>
//#include <thread>
#include <tuple>

#include <boost/asio.hpp>
#include <boost/version.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>

#include <autobahn/autobahn.hpp>


void log (const std::string& msg) {
    std::cerr << msg << std::endl;
    //std::cerr << msg << " [thread " << boost::this_thread::get_id() << "]" << std::endl;
}


void add2(autobahn::wamp_invocation invocation)
{
    auto a = invocation->argument<uint64_t>(0);
    auto b = invocation->argument<uint64_t>(1);

    std::cerr << "Procedure com.examples.calculator.add2 invoked: " << a << ", " << b << std::endl;

    invocation->result(std::make_tuple(a + b));
}


void longop(autobahn::wamp_invocation invocation)
{
    auto a = invocation->argument<uint64_t>(0);
    std::cerr << "Procedure com.myapp.longop invoked: " << a << std::endl;
    uint64_t i = 0;
    for (; i < a; i++)
    {
//        boost::this_thread::sleep(boost::posix_time::milliseconds(3000));
        if (i < a)
        {
            invocation->progress(std::make_tuple(i));
        }
    }
    invocation->result(std::make_tuple(i));
}


int main(int argc, char** argv)
{
    try {
        log("starting program ..");

        boost::asio::io_service io;

        bool debug = true;

        auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("192.168.1.211"), 8080);

        auto transport = std::make_shared<autobahn::wamp_tcp_transport>(io, endpoint, debug);

        auto session = std::make_shared<autobahn::wamp_session>(io, debug);

        transport->attach(std::static_pointer_cast<autobahn::wamp_transport_handler>(session));

        transport->connect().then([&](boost::future<void> connected) {

            log("transport connected");

            session->start().then(boost::launch::deferred, [&](boost::future<void> started) {

                log("session started");

                session->join("realm1").then(boost::launch::deferred, [&](boost::future<uint64_t> joined) {

                    log("joined realm");

                    auto f1 = session->provide("com.examples.calculator.add2", &add2).then(
                        boost::launch::deferred,
                        [&](boost::future<autobahn::wamp_registration> registration) {
                        log("registered procedure com.examples.calculator.add2");
                    });

                    auto f2 = session->provide("com.myapp.longop", &longop).then(
                        boost::launch::deferred,
                        [&](boost::future<autobahn::wamp_registration> registration) {
                        log("registered procedure com.myapp.longop");
                    });

                    f1.get();
                    f2.get();
                }).get();

            }).get();
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
