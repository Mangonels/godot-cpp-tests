#include "main.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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

                const auto file_to_open_res = "res://file-access/Scene.tscn";

				//---
                //(A) FileAccess file_exists static method call
                //---

                if (godot::FileAccess::file_exists(file_to_open_res))
                    godot::UtilityFunctions::print("C++ (A) godot::FileAccess returned existing file.");
                else
                    godot::UtilityFunctions::print("C++ (A) godot::FileAccess returned NON existing file.");

				//---
                //(B) ResourceLoader singleton exists method call
                //---
                if (godot::ResourceLoader::get_singleton()->exists(file_to_open_res))
                    godot::UtilityFunctions::print(
                        "C++ (B) ResourceLoader::get_singleton()->exists returned existing file.");
                else
                    godot::UtilityFunctions::print(
                        "C++ (B) ResourceLoader::get_singleton()->exists returned NON existing file.");
            }
            break;
        }
    }
}
