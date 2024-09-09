/**
License details have been added to this "substantial portion of
the original software", at: https://github.com/vorlac/godot-roguelite
as established by it's license as of 25-Mar-24:

"MIT License

Copyright (c) 2023 sal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE."
*/

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