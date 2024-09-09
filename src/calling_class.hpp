#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {
    class Node3D;
}

namespace ns {
    class Main;
}

namespace ns
{
    class CallingClass : public godot::Node
    {
        GDCLASS(CallingClass, godot::Node);

    public:
        CallingClass();
        ~CallingClass() = default;

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }
    private:
        Main* m_parent_node = nullptr;

		godot::Node3D* m_requested_node_ref = nullptr;
    };
}
