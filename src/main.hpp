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

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }

    private:
        bool m_run_thread_loop = false;
        std::thread m_test_thread;

        void thread_function();
    };
}
