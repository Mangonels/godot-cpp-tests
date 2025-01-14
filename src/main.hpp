
#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/thread.hpp>

namespace ns {
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main() = default;
        ~Main() = default;

        bool run_thread_loop = false;
        godot::Ref<godot::Thread> test_thread;

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }
    private:
        void thread_function();
    };
}
