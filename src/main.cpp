#include <godot_cpp/variant/utility_functions.hpp>

#include "main.hpp"
#include "util/engine.hpp"

namespace ns {
    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                set_process(true);
                // set_physics_process(true);
                // set_process_mode(PROCESS_MODE_PAUSABLE);

				call_deferred("change_cursor");

				// THIS WON'T WORK AS EXPECTED
                //godot::DisplayServer::get_singleton()->cursor_set_shape(godot::DisplayServer::CursorShape::CURSOR_HSIZE);

                break;
            }
            case NOTIFICATION_PROCESS:
            {
                // THIS WON'T WORK AS EXPECTED, BUT IT DOES AT LEAST CHANGE THE CURSOR
                //godot::DisplayServer::get_singleton()->cursor_set_shape(godot::DisplayServer::CursorShape::CURSOR_HSIZE);
            }
        }
    }

    void Main::_input(const godot::Ref<godot::InputEvent>& p_event)
    {
        const godot::Vector2 mouse_position = get_viewport()->get_mouse_position();

        if (p_event.is_valid() && p_event->is_class("InputEventMouseMotion"))
        {
            // THIS WON'T WORK AT ALL, WHICH IS WEIRD, SINCE NOTIFICATION_PROCESS CALLS WILL WORK, WHAT'S THE DIFFERENCE WITH _input?
            godot::DisplayServer::get_singleton()->cursor_set_shape(godot::DisplayServer::CursorShape::CURSOR_HSIZE);
            godot::UtilityFunctions::print("Mouse moving around.");

        }
    }
}
