#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "Main.hpp"
#include "systems/audio_player.hpp"
#include "util/engine.hpp"

namespace ns {
    void Main::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                set_process(true);

                godot::UtilityFunctions::print("Main node ready ", gdeng::get()->get_version_info());

                // Load the test music (AudioPlayer is accessed via static get() as it's an autoload)
                godot::Ref<godot::Resource> resource = godot::ResourceLoader::get_singleton()->load("res://main_menu_theme.ogg");
                if (resource.is_valid())
                {
                    m_test_music = resource;
                }

                if (m_test_music.is_null())
                {
                    godot::UtilityFunctions::printerr("Failed to load res://main_menu_theme.ogg");
                }
                else
                {
                    godot::UtilityFunctions::print("Audio file loaded successfully. Press M to test play/stop music.");
                }

                break;
            }
        }
    }

    void Main::_input(const godot::Ref<godot::InputEvent>& event)
    {
        // Check if this is a key event
        godot::Ref<godot::InputEventKey> key_event = event;
        if (key_event.is_null())
            return;

        // Only handle when key is pressed (not released)
        if (!key_event->is_pressed() || key_event->is_echo())
            return;

        // Check for M key
        if (key_event->get_keycode() == godot::Key::KEY_M)
        {
            if (m_test_music.is_null())
            {
                godot::UtilityFunctions::printerr("Test music not loaded!");
                return;
            }

            // Toggle between play and stop using AudioPlayer autoload
            AudioPlayer* audio_player = AudioPlayer::get();
            if (audio_player == nullptr)
            {
                godot::UtilityFunctions::printerr("AudioPlayer autoload not initialized! Make sure GlobalAudioPlayer is set up in project settings.");
                return;
            }

            if (!m_is_playing)
            {
                godot::UtilityFunctions::print("Playing music...");
                audio_player->play_music(m_test_music, 1.0f, 1.0f, true, 0.0f, 0.0f);
                m_is_playing = true;
            }
            else
            {
                godot::UtilityFunctions::print("Stopping music...");
                audio_player->stop_music();
                m_is_playing = false;
            }
        }
    }
}
