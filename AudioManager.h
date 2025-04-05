//
// Created by artem on 26.03.2025.
//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#pragma once
#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

class AudioManager {
public:
    enum class Track {
        Menu,
        Game,
        Victory
    };

    // Инициализация аудиосистемы
    static void init();

    // Управление воспроизведением
    static void play(Track track);
    static void stop();
    static bool isPlaying();

    // Установка громкости
    static void setMusicVolume(float volume);
    static void setMasterVolume(float volume);

    // Получение громкости
    static float getMusicVolume();
    static float getMasterVolume();

    // Клик-звук
    static void playClick();

    // Конфигурация
    static void saveConfig();
    static void loadConfig();

private:
    static sf::Music music;
    static sf::SoundBuffer clickBuffer;
    static sf::Sound clickSound;
    static Track currentTrack;

    static float musicVolume;
    static float masterVolume;

    static std::unordered_map<Track, std::string> trackPaths;
};


#endif //AUDIOMANAGER_H
