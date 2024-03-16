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

				const auto file_to_open = "res://Hello.txt";

				//---
				//(A) FileAccess static method call
                //---

                if (godot::FileAccess::open(file_to_open, godot::FileAccess::READ).is_null())
                    godot::UtilityFunctions::print("(A) godot::FileAccess open static method call is null.");
				else
                    godot::UtilityFunctions::print("(A) godot::FileAccess open static method call returned FileAccess successfully.");

				//---
				//(B) FileAccess stack object calls
                //---

                godot::FileAccess file_access_stack;
                const auto file_access_B = file_access_stack.open(file_to_open, godot::FileAccess::READ);
                if (file_access_B.is_null())
                {
                    godot::UtilityFunctions::print("(B) Stack file access static method call is null.");
                }
                else
                {
                    godot::UtilityFunctions::print("(B) Stack file access open static method call returned FileAccess successfully.");
                }

				//---
				//(C) FileAccess ref counted instance calls
                //---

                //const godot::Ref file_access_ref(memnew(godot::FileAccess));
                //if (file_access_ref == nullptr)
                //{
                //    godot::UtilityFunctions::print("(C) Ref fileaccess is nullptr.");
                //}
                //else
                //{
                //    godot::UtilityFunctions::print("(C) Ref fileaccess initialization successful.");
                //    auto file_access = file_access_ref->open(file_to_open, godot::FileAccess::READ);
                //    if (file_access == nullptr)
                //    {
                //        godot::UtilityFunctions::print("(C) Ref fileaccess is nullptr.");
                //    }
                //    else
                //    {
                //        godot::UtilityFunctions::print("(C) Ref fileaccess initialization successful.");
                //    }
                //}
            }
            break;
        }
    }
}
