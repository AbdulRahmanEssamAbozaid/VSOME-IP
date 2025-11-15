#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "common.hpp"
#include "colors.hpp"

using namespace SomeIPConfig;

static std::shared_ptr<vsomeip::application> app;

void on_message(const std::shared_ptr<vsomeip::message> &msg) {
    auto payload = msg->get_payload();
    if (!payload) {
        std::cout << RED << "[CLIENT] Received empty payload" << RESET << "\n";
    } else {
        std::string data(reinterpret_cast<char*>(payload->get_data()), payload->get_length());
        std::cout << GREEN << "[CLIENT] Response received: " << data << RESET << "\n";
    }

    auto shutdown_msg = vsomeip::runtime::get()->create_request();
    shutdown_msg->set_service(SERVICE_ID);
    shutdown_msg->set_instance(INSTANCE_ID);
    shutdown_msg->set_method(METHOD_SHUTDOWN);
    shutdown_msg->set_reliable(true);

    std::cout << RED << "[CLIENT] Sending shutdown request..." << RESET << "\n";
    app->send(shutdown_msg);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    app->stop();
}

int main() {
    app = vsomeip::runtime::get()->create_application("client-app");

    if (!app) {
        std::cerr << RED << "[CLIENT] Failed to get runtime application." << RESET << "\n";
        return 1;
    }

    app->init();

    app->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_ID, on_message);

    app->request_service(SERVICE_ID, INSTANCE_ID);

    std::thread sender([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto req = vsomeip::runtime::get()->create_request();
        req->set_service(SERVICE_ID);
        req->set_instance(INSTANCE_ID);
        req->set_method(METHOD_ID);

        std::vector<vsomeip::byte_t> payload_data = {'H','i'};
        auto payload = vsomeip::runtime::get()->create_payload();
        payload->set_data(payload_data);
        req->set_payload(payload);

        std::cout << BLUE << "[CLIENT] Sending request..." << RESET << "\n";
        app->send(req);
    });

    sender.detach();

    std::cout << YELLOW << "[CLIENT] Waiting for response..." << RESET << "\n";

    app->start();
    std::cout << MAGENTA << "[CLIENT] Stopped." << RESET << "\n";
    return 0;
}
