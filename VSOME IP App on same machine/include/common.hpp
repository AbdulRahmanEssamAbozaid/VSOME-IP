#pragma once

#include <cstdint>

namespace SomeIPConfig {

    enum : std::uint16_t {
        // ===== Service & Instance =====
        SERVICE_ID       = 0x1234,
        INSTANCE_ID      = 0x5678,

        // ===== Methods =====
        METHOD_ID        = 0x0421,    // Normal request method
        METHOD_SHUTDOWN  = 0x9999     // Shutdown method
    };

} // namespace SomeIPConfig
