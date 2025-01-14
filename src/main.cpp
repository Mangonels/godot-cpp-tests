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

				test_thread = memnew(godot::Thread);

				static godot::Callable c = callable_mp(this, &Main::thread_function);
                test_thread->start(c);  // Start extra thread
            }
            case NOTIFICATION_PROCESS:
            {
                godot::UtilityFunctions::print("Main Thread!");
            }
            case NOTIFICATION_EXIT_TREE:
            {
                run_thread_loop = false;
                //test_thread->wait_to_finish(); //End thread freezes game
            }
            break;
        }
    }

    void Main::thread_function()
    {
        while (run_thread_loop)
            godot::UtilityFunctions::print("Extra Thread!"); //This doesn't even run
    }
}