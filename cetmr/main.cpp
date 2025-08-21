#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>
#include <csignal>

// Timer class from before
class Timer {
public:
    Timer(std::function<void()> func, std::chrono::milliseconds interval)
        : func_(func), interval_(interval), running_(false) {}

    void start() {
        running_ = true;
        thread_ = std::thread([this]() {
            while (running_) {
                auto next_call = std::chrono::steady_clock::now() + interval_;
                func_();
                std::this_thread::sleep_until(next_call);
            }
        });
    }

    void stop() {
        running_ = false;
        if (thread_.joinable())
            thread_.join();
    }

    ~Timer() {
        stop();
    }

private:
    std::function<void()> func_;
    std::chrono::milliseconds interval_;
    std::atomic<bool> running_;
    std::thread thread_;
};

// Global atomic flag to communicate between signal handler and main
std::atomic<bool> g_running(true);

// Signal handler for Ctrl+C
void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nSIGINT received, stopping...\n";
        g_running = false;
    }
}

int main() {
    // Register signal handler
    std::signal(SIGINT, signalHandler);

    Timer timer([]() {
        std::cout << "Triggered every 10 ms\n";
    }, std::chrono::milliseconds(1000));

    timer.start();

    // Main thread waits until Ctrl+C is pressed
    while (g_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    timer.stop();

    std::cout << "Timer stopped gracefully.\n";
    return 0;
}
