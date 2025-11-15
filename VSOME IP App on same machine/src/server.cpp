#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "common.hpp"
#include "colors.hpp"

using namespace SomeIPConfig;

static std::shared_ptr<vsomeip::application> app;

void on_request(const std::shared_ptr<vsomeip::message> &msg) {
    // If shutdown -> stop app
    if (msg->get_method() == METHOD_SHUTDOWN) {
        std::cout << RED << "[SERVER] Shutdown request received. Stopping..." << RESET << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        app->stop();
        return;
    }

    std::cout << CYAN << "[SERVER] Request received. Sending response..." << RESET << "\n";

    auto response = vsomeip::runtime::get()->create_response(msg);

    std::string text = "Hello From Server";
    std::vector<vsomeip::byte_t> data(text.begin(), text.end());

    auto payload = vsomeip::runtime::get()->create_payload();
    payload->set_data(data);

    response->set_payload(payload);
    app->send(response);

    std::cout << GREEN << "[SERVER] Response sent." << RESET << "\n";
}

int main() {
    app = vsomeip::runtime::get()->create_application("server-app");

    if (!app) {
        std::cerr << RED << "[SERVER] Failed to get runtime application." << RESET << "\n";
        return 1;
    }

    app->init();

    app->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_ID, on_request);
    app->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_SHUTDOWN, on_request);

    app->offer_service(SERVICE_ID, INSTANCE_ID);

    std::cout << YELLOW << "[SERVER] Offer service done. Waiting for client..." << RESET << "\n";

    app->start();
    std::cout << MAGENTA << "[SERVER] Stopped." << RESET << "\n";
    return 0;
}
