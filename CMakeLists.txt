cmake_minimum_required(VERSION 3.5...3.20)
project(Balatro)

# C++ стандарт
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Используем динамическую линковку для упрощения запуска и устранения ошибки 0xC0000135
set(BUILD_SHARED_LIBS ON)

# Подключаем SFML из GitHub
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

# Добавляем исполняемый файл
add_executable(Balatro main.cpp
        MenuBalatro.h
        MenuBalatro.cpp
        GameMenu.cpp
        GameMenu.h
        TextInput.cpp
        TextInput.h
        HadeMenu.cpp
        HadeMenu.h
        AudioManager.cpp
        AudioManager.h
        SettingsMenu.cpp
        SettingsMenu.h
        VolumeSlider.cpp
        VolumeSlider.h
        MenuPause.cpp
        MenuPause.h
        ExitPopup.cpp
        ExitPopup.h
        TextAnimator.cpp
        TextAnimator.h
        RectangleHover.cpp
        RectangleHover.h
        TitleLetters.cpp
        TitleLetters.h
        NamePopup.cpp
        NamePopup.h
        FadeEffect.cpp
        FadeEffect.h
        SwayText.cpp
        SwayText.h)

# Линкуем SFML (динамически)
target_link_libraries(Balatro PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
)

# Копирование DLL-файлов после сборки (Windows)
if (WIN32)
    add_custom_command(TARGET Balatro POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-audio>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:Balatro>
    )
endif()

# Базовые зависимости Windows API (опционально)
if (MINGW)
    target_link_libraries(Balatro PRIVATE
            winmm
            gdi32
            opengl32
    )

    # Копируем нужные папки в директорию сборки
    file(COPY ${CMAKE_SOURCE_DIR}/Pictures DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_SOURCE_DIR}/Fonts DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_SOURCE_DIR}/Music DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_SOURCE_DIR}/Button\ sound DESTINATION ${CMAKE_BINARY_DIR})
endif()