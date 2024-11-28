#include <godot_cpp/classes/node3d.hpp>

#include "core/assert.hpp"
#include "main.hpp"
#include "util/engine.hpp"

namespace ns {

    Main::Main()
    {
    }

    godot::Node3D* Main::get_node_3d_ptr() const
    {
        return m_instanced_node3d;
    }

    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                m_instanced_node3d = memnew(godot::Node3D);
                runtime_assert(m_instanced_node3d != nullptr);
            }
            break;
        }
    }
}
