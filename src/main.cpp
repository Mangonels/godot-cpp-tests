#include <chrono>
#include <thread>

#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "main.hpp"
#include "util/engine.hpp"

namespace ns {

    Main::Main()
    {
    }

    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                RUNTIME_OR_RELEASE_GUARD


            }
            break;
        }
    }
}
