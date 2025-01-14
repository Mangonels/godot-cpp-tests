#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/thread.hpp>

#include "main.hpp"

namespace ns {
    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                set_process(true);

                run_thread_loop = true;
                test_thread = godot::Ref<godot::Thread>(memnew(godot::Thread));

                test_thread->start(callable_mp(this, &Main::thread_function));

                break;
            }
            case NOTIFICATION_PROCESS:
            {
                godot::UtilityFunctions::print("Main Thread!");

                break;
            }
            case NOTIFICATION_EXIT_TREE:
            {
                godot::UtilityFunctions::print("Exit tree notification received.");

                run_thread_loop = false;
                test_thread->wait_to_finish();

                break;
            }
        }
    }

    void Main::thread_function()
    {
        while (run_thread_loop)
            godot::UtilityFunctions::print("Extra Thread!");
    }
}