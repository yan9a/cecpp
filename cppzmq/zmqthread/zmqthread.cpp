#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <zmq.hpp>

using namespace std;
using namespace std::chrono_literals;
void startsvr() 
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");

    // prepare some static data for responses
    const std::string data{"World"};

    for (;;) 
    {
        zmq::message_t request;

        // receive a request from client
        zmq::recv_result_t r = socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received " << request.to_string() << std::endl;

        // simulate work
        std::this_thread::sleep_for(2s);

        // send the reply to the client
        socket.send(zmq::buffer(data), zmq::send_flags::none);
    }
}

void client(int i)
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REQ (request) socket and connect to interface
    zmq::socket_t socket{context, zmq::socket_type::req};
    socket.connect("tcp://localhost:5555");
    socket.set(zmq::sockopt::rcvtimeo,5000); // 5 s

    // set up some static data to send
    const std::string data{"Hello "+to_string(i)};

    for (auto request_num = 0; request_num < 10; ++request_num) 
    {
        try{
            // send the request message
            std::cout << "Sending Hello "<< i << " " << request_num << "..." << std::endl;
            socket.send(zmq::buffer(data), zmq::send_flags::none);
        }
        catch(const zmq::error_t& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Sending error." << std::endl;
        }
        // wait for reply from server
        zmq::message_t reply{};
        try{
            zmq::recv_result_t r = socket.recv(reply, zmq::recv_flags::none);

            std::cout << "Received " << i << " " << reply.to_string(); 
            std::cout << " (" << request_num << ")";
            std::cout << std::endl;
        }
        catch(const zmq::error_t& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "No reply received within timeout." << std::endl;
        }
    }
}

int main() 
{
    thread t([&]() { startsvr(); });
    t.detach();

    thread t2([&](){ client(1);});
    t2.detach();

    client(2);
    return 0;
}



