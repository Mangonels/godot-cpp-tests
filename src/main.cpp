#include "main.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include "util/engine.hpp"
#include <optional>

namespace ns {

    Main::Main()
    {
    }

    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                RUNTIME_OR_RELEASE_GUARD

				const auto file_to_open = "res://file-access/Hello.txt";

				//---
                //(A) FileAccess file_exists static method call
                //---

                if (godot::FileAccess::file_exists(file_to_open))
                    godot::UtilityFunctions::print("(A) godot::FileAccess returned existing file.");
                else
                    godot::UtilityFunctions::print("(A) godot::FileAccess returned NON existing file.");

				//---
				//(B) FileAccess open static method call
                //---

                if (godot::FileAccess::open(file_to_open, godot::FileAccess::READ).is_null())
                    godot::UtilityFunctions::print("(B) godot::FileAccess open static method call is null.");
				else
                    godot::UtilityFunctions::print("(B) godot::FileAccess open static method call returned FileAccess successfully.");
            }
            break;
        }
    }
}
