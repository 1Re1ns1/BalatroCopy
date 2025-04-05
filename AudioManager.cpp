#include "AudioManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

sf::Music AudioManager::music;
sf::Sound AudioManager::clickSound;
sf::SoundBuffer AudioManager::clickBuffer;
AudioManager::Track AudioManager::currentTrack;
float AudioManager::musicVolume = 100.f;
float AudioManager::masterVolume = 100.f;

std::unordered_map<AudioManager::Track, std::string> AudioManager::trackPaths = {
    { Track::Menu, "Music/MenuTheme.ogg" },
};

void AudioManager::init() {
    loadConfig();

    if (!clickBuffer.loadFromFile("Button sound/click.ogg")) {
        std::cerr << "Error loading click sound\n";
    }
    clickSound.setBuffer(clickBuffer);
    clickSound.setVolume(masterVolume);

    play(Track::Menu); // по умолчанию
}

void AudioManager::play(Track track) {
    if (currentTrack == track && music.getStatus() == sf::Music::Playing) return;

    if (!music.openFromFile(trackPaths[track])) {
        std::cerr << "Ошибка загрузки трека!" << std::endl;
        return;
    }

    currentTrack = track;
    music.setLoop(true);
    music.setVolume(musicVolume * (masterVolume / 100.f));
    music.play();
}

void AudioManager::stop() {
    music.stop();
}

void AudioManager::setMusicVolume(float v) {
    musicVolume = v;
    music.setVolume(musicVolume * (masterVolume / 100.f));
}

void AudioManager::setMasterVolume(float v) {
    masterVolume = v;
    music.setVolume(musicVolume * (masterVolume / 100.f));
    clickSound.setVolume(masterVolume);
}

float AudioManager::getMusicVolume() {
    return musicVolume;
}

float AudioManager::getMasterVolume() {
    return masterVolume;
}

bool AudioManager::isPlaying() {
    return music.getStatus() == sf::Music::Playing;
}

void AudioManager::playClick() {
    clickSound.play();
}

void AudioManager::saveConfig() {
    std::ofstream file("config.txt");
    if (!file.is_open()) return;

    file << "musicVolume=" << musicVolume << std::endl;
    file << "masterVolume=" << masterVolume << std::endl;
}

void AudioManager::loadConfig() {
    std::ifstream file("config.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "musicVolume") {
                musicVolume = std::stof(value);
            } else if (key == "masterVolume") {
                masterVolume = std::stof(value);
            }
        }
    }
}

