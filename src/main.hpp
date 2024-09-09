#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot
{
    class Node3D;
}

namespace ns
{
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main();
        ~Main() = default;

        godot::Node3D* get_node_3d_ref() const;

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }

    private:
        godot::Node3D* m_instanced_node3d = nullptr;
    };
}
