cmake_minimum_required(VERSION 3.12.2)

project(Caravan)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(Caravan
  ../../../../../../dev/OpenGL/src/glad.c
  game.cpp
  game.h
  game_objects/card.cpp
  game_objects/card.h
  game_objects/card_stack.cpp
  game_objects/card_stack.h
  game_objects/game_object.cpp
  game_objects/game_object.h
  main.cpp
  table.cpp
  table.h
  utilities/mouse_picker.cpp
  utilities/mouse_picker.h
  utilities/resource_manager.cpp
  utilities/resource_manager.h
  utilities/shader.cpp
  utilities/shader.h
  utilities/sprite_renderer.cpp
  utilities/sprite_renderer.h
  utilities/texture.cpp
  utilities/texture.h
)
# Preprocessor definitions
target_compile_definitions(Caravan PRIVATE
  $<$<CONFIG:Debug>:_MBCS;>
  $<$<CONFIG:Release>:_MBCS;>
)

# SDL check
target_compile_options(Caravan PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(Caravan PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(Caravan PRIVATE
    ""
  )
endif ()
