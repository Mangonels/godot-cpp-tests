#pragma once

#include <godot_cpp/classes/node.hpp>

namespace ns::inline systems {
    class AudioPlayer;
}

namespace ns {
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main() = default;
        ~Main() = default;

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }
    };
}
