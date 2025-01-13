#pragma once

#include <cstdint>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/main_loop.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/physics_server3d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

namespace ns::inline utils {
    namespace gdeng {
        /* ENGINE */

        extern inline godot::Engine* get()
        {
            return godot::Engine::get_singleton();
        }

        extern inline godot::MainLoop* main_loop()
        {
            auto engine = get();
            return engine->get_main_loop();
        }

        extern inline godot::SceneTree* scene_tree()
        {
            auto loop = main_loop();
            return ::godot::Object::cast_to<godot::SceneTree>(loop);
        }

        extern inline godot::Window* root_window()
        {
            auto tree = scene_tree();
            return tree->get_root();
        }

        extern inline godot::Node* root_node()
        {
            return godot::Object::cast_to<godot::Node>(root_window());
        }

        /* SERVERS */

        extern inline godot::RenderingServer* rendering_server()
        {
            return godot::RenderingServer::get_singleton();
        }

        extern inline godot::PhysicsServer3D* physics_server_3d()
        {
            return godot::PhysicsServer3D::get_singleton();
        }

        /* SETTINGS */

        extern inline void set_fps(const uint32_t fps)
        {
            auto engine = get();
            return engine->set_max_fps(fps);
        }

        extern inline int32_t max_fps()
        {
            auto engine = get();
            return engine->get_max_fps();
        }

        extern inline bool editor_active()
        {
            auto engine = get();
            return engine->is_editor_hint();
        }
    }
}