#include "main.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "util/engine.hpp"
#include <optional>

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
                
            }
            break;
        }
    }
}
