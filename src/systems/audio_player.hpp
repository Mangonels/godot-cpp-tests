#pragma once

#include <godot_cpp/classes/audio_stream_ogg_vorbis.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/tween.hpp>

#include "util/bind.hpp"

namespace godot
{
    class AudioStreamPlayer;
    class AudioStreamPlayer3D;
}

namespace morph::client
{
    /** AudioPlayer singleton (meant to be godot autoloaded) */
    class AudioPlayer : public godot::Node
    {
        GDCLASS(AudioPlayer, godot::Node)

    public:
        AudioPlayer() = default;

        ~AudioPlayer();

        static AudioPlayer* get();

        // ---
        // MUSIC
        // ---

        /**
         * Meant for playing non spatial music from specifiable seconds position.
         * If music is already playing, stops previous, and optionally, fades it out
         * (even if same as new).
         * Music to be played can also be faded in, you can choose if it should loop, and
         * Change it's pitch (0 to 2) and volume (0 to 1).
         */
        void play_music(const godot::Ref<godot::AudioStreamOggVorbis>& music, float volume = 1.0f, float pitch = 1.0f, bool loop = true, float loop_offset = 0.0f, float fade_in_time = 0.0f, float prev_stream_fade_out_time = 0.0f, float from_position = 0.0f);
        /** Immediately stops active music (also stops any other music already programmed to run after) */
        void stop_music();

    protected:
        static void _bind_methods()
        {
            bind_member_function(AudioPlayer, play_music);
            bind_member_function(AudioPlayer, stop_music);
        }

        void _notification(int p_notification);

    private:
        static inline AudioPlayer* m_static_inst{ nullptr };

        godot::AudioStreamPlayer* m_global_music = nullptr;

        godot::Ref<godot::Tween> m_music_fadeout_tween = nullptr;
        godot::Ref<godot::Tween> m_music_fadein_tween = nullptr;

        void play_music_internal(const godot::Ref<godot::AudioStreamOggVorbis>& music, const float volume, const float pitch, bool loop, float loop_offset, const float fade_in_time, const float from_position);
    };
}