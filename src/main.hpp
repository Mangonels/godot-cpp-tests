#pragma once

#include <thread>

#include <godot_cpp/classes/node.hpp>

namespace ns {
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main() = default;
        ~Main() = default;

        bool run_thread_loop = false;
        std::thread test_thread;

    protected:
        void _notification(int p_notification);
        void thread_function();

        static void _bind_methods()
        {
        }
    };
}
