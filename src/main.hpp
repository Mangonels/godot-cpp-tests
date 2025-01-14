
#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {
    class Thread;
}

namespace ns {
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main() = default;
        ~Main() = default;

        bool run_thread_loop = false;
        godot::Thread* test_thread;

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }
    private:
        void thread_function();
    };
}
