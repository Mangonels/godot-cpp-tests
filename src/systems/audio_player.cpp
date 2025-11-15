#include <godot_cpp/classes/audio_stream_playback.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_player3d.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "systems/audio_player.hpp"
#include "util/conversions.hpp"
#include "util/engine.hpp"

namespace morph::client
{
    AudioPlayer::~AudioPlayer()
    {
        m_static_inst = nullptr;
    }

    AudioPlayer* AudioPlayer::get()
    {
        return m_static_inst;
    }

    void AudioPlayer::_notification(int p_notification)
    {
        switch (p_notification)
        {
            case NOTIFICATION_READY:
            {
                m_global_music = memnew(godot::AudioStreamPlayer);
                m_global_music->set_bus("music");
                add_child(m_global_music);

                if (m_static_inst == nullptr)
                    m_static_inst = this;
                else if (m_static_inst != this)
                    godot::UtilityFunctions::printerr("AudioPlayer: Multiple instances detected in on ready!");

                break;
            }
        }
    }

    void AudioPlayer::play_music(const godot::Ref<godot::AudioStreamOggVorbis>& music, const float volume, const float pitch, const bool loop, const float loop_offset, const float fade_in_time, const float prev_stream_fade_out_time, const float from_position)
    {
        if (m_music_fadein_tween != nullptr)
            m_music_fadein_tween->stop();
        if (m_music_fadeout_tween != nullptr)
            m_music_fadeout_tween->stop();
        if (m_global_music->is_playing() && prev_stream_fade_out_time > 0.0f && m_music_fadeout_tween != nullptr)
        {
            m_music_fadeout_tween = create_tween();
            m_music_fadeout_tween->tween_property(m_global_music, "volume_linear", 0.0f, prev_stream_fade_out_time);
            m_music_fadeout_tween->connect("finished", callable_mp(this, &AudioPlayer::play_music_internal).bind(music, volume, pitch, loop, loop_offset, fade_in_time, from_position));
        }
        else
        {
            play_music_internal(music, volume, pitch, loop, loop_offset, fade_in_time, from_position);
        }
    }

    void AudioPlayer::stop_music()
    {
        if (m_music_fadein_tween != nullptr)
            m_music_fadein_tween->stop();
        if (m_music_fadeout_tween != nullptr)
            m_music_fadeout_tween->stop();

        m_global_music->stop();
    }

    void AudioPlayer::play_music_internal(const godot::Ref<godot::AudioStreamOggVorbis>& music, const float volume, const float pitch, bool loop, float loop_offset, const float fade_in_time, const float from_position)
    {
        m_global_music->set_stream(music);
        m_global_music->set_pitch_scale(pitch);

        music->set_loop(loop);
        music->set_loop_offset(loop_offset);

        m_global_music->play(from_position);
        if (fade_in_time > 0.0f)
        {
            m_music_fadein_tween = create_tween();
            m_music_fadein_tween->tween_property(m_global_music, "volume_linear", volume, fade_in_time)->from(0.0f);
        }
        else
        {
            m_global_music->set_volume_linear(volume);
        }
    }