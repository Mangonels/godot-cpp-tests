# =======================================================================
# Godot-cpp bindings submodule update/init
# =======================================================================

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/godot-cpp/src")
    message(NOTICE "godot-cpp bingings source not found")
    message(NOTICE "initializing/updating the godot-cpp submodule...")

    execute_process(
        COMMAND git submodule update --init extern/godot-cpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
endif()

# =======================================================================
# Godot C++ bindings library setup/configuration
# =======================================================================

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/godot-cpp)
