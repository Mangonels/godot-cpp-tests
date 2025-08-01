#include <godot_cpp/variant/utility_functions.hpp>

#include "main.hpp"
#include "util/engine.hpp"

namespace ns {
    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                // set_process(true);
                // set_physics_process(true);
                // set_process_mode(PROCESS_MODE_PAUSABLE);

                godot::UtilityFunctions::print("Main node ready ", gdeng::get()->get_version_info());

                break;
            }
        }
    }
}
