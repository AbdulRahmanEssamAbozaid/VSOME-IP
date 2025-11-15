#pragma once
#include <vsomeip/vsomeip.hpp>
#include "common.hpp"

void on_message(const std::shared_ptr<vsomeip::message> &request);
