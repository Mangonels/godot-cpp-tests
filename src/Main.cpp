#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "Main.hpp"
#include "util/engine.hpp"

namespace ns {
    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                godot::UtilityFunctions::print("Main node ready ", gdeng::get()->get_version_info());
            }
        }
    }
}
