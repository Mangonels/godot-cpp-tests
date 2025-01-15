#include <godot_cpp/variant/utility_functions.hpp>

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
                test_thread = std::thread(&Main::thread_function, this);

				break;
            }
            case NOTIFICATION_PROCESS:
            {
                godot::UtilityFunctions::print("Main Thread!");

				break;
            }
            case NOTIFICATION_EXIT_TREE:
            {
                run_thread_loop = false;
                test_thread.join();

				break;
            }
        }
    }

    void Main::thread_function()
    {
        /* NOTE: my computer runs 1702 loop iterations from this separate thread 
        between each main thread PROCESS notification, so godot's NOTIFICATION_PROCESS
        (which is the "highest frequency loop" for Godot that I know of)
        is much less frequent.

		It was actually possible to run a print from utility functions at this frequency,
		as long as we don't call .join() but it's unconfirmed what other Godot Engine API
		functions may be runnable.

        There are also some limitations as to which API functionalities can be called
        from an extra thread:
        https://docs.godotengine.org/en/stable/tutorials/performance/thread_safe_apis.html#doc-thread-safe-apis

        - PixelRain */

        while (run_thread_loop)
            godot::UtilityFunctions::print("Extra Thread!"); 
    }
}
