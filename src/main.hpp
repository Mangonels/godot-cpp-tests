#pragma once

#include <godot_cpp/classes/audio_stream_ogg_vorbis.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>

namespace ns::inline systems
{
    class AudioPlayer;
}

namespace ns {
    class Main : public godot::Node
    {
        GDCLASS(Main, godot::Node);

    public:
        Main() = default;
        ~Main() = default;

        void _input(const godot::Ref<godot::InputEvent>& event);

    protected:
        void _notification(int p_notification);

        static void _bind_methods()
        {
        }

    private:
        godot::Ref<godot::AudioStreamOggVorbis> m_test_music;
        bool m_is_playing = false;
    };
}
