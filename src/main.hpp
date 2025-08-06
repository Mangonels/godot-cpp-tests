#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace ns {
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main() = default;
        ~Main() = default;

        void _input(const godot::Ref<godot::InputEvent>& p_event) override;

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }
    };
}
