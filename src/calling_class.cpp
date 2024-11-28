#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "calling_class.hpp"
#include "main.hpp"
#include "util/conversions.hpp"

namespace ns {
    CallingClass::CallingClass()
    {
    }

    void CallingClass::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                // set_process(true);
                // set_physics_process(true);
                // set_process_mode(PROCESS_MODE_PAUSABLE);

                m_parent_node = gdcast<Main>(get_parent());
                runtime_assert(m_parent_node != nullptr);
                godot::Node3D* ref = m_parent_node->get_node_3d_ptr();
                m_requested_node_ref = &ref;
                runtime_assert(m_requested_node_ref != nullptr);

                godot::UtilityFunctions::print("reached here");
            }
            break;
        }
    }
}
