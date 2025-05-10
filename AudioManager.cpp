#include "AudioManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

sf::Music AudioManager::music;
sf::Sound AudioManager::clickSound;
sf::SoundBuffer AudioManager::clickBuffer;
AudioManager::Track AudioManager::currentTrack = AudioManager::Track::Menu;
float AudioManager::musicVolume = 100.f;
float AudioManager::masterVolume = 100.f;

std::unordered_map<AudioManager::Track, std::string> AudioManager::trackPaths = {
    { Track::Menu, "Music/MenuTheme.ogg" },
};

void AudioManager::init() {
    loadConfig();

    if (!clickBuffer.loadFromFile("Button sound/click.ogg")) {
        std::cerr << "[AudioManager] Error loading click sound: Button sound/click.ogg\n";
    } else {
        clickSound.setBuffer(clickBuffer);
        clickSound.setVolume(masterVolume);
    }

    play(Track::Menu); // Воспроизведение по умолчанию
}

void AudioManager::play(Track track) {
    if (music.getStatus() == sf::Music::Playing)
        music.stop();

    auto it = trackPaths.find(track);
    if (it == trackPaths.end()) {
        std::cerr << "Track not found\n";
        return;
    }

    std::string path = it->second;

    if (!sf::SoundBuffer().loadFromFile(path)) {
        std::cerr << "Just test: file cannot be decoded properly: " << path << "\n";
        return;
    }

    if (!music.openFromFile(path)) {
        std::cerr << "Failed to open music file: " << path << "\n";
        return;
    }

    std::cout << "Loaded and about to play: " << path << "\n";

    music.setLoop(true);
    music.setVolume(musicVolume * (masterVolume / 100.f));
    music.play();

    if (music.getStatus() != sf::Music::Playing) {
        std::cerr << "[AudioManager] ERROR: music.play() failed\n";
    }
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
    if (clickBuffer.getDuration() == sf::Time::Zero) {
        std::cerr << "[AudioManager] Warning: click sound not loaded properly\n";
        return;
    }

    clickSound.stop();  // Прекращаем прежний щелчок, если ещё играет
    clickSound.play();
}

void AudioManager::saveConfig() {
    std::ofstream file("config.txt");
    if (!file.is_open()) return;

    file << "musicVolume=" << musicVolume << '\n';
    file << "masterVolume=" << masterVolume << '\n';
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
