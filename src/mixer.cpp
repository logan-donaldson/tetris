#include "mixer.h"
#include <SDL_mixer.h>
#include <iostream>

Mixer::Mixer() {
	this->rotateSound = nullptr;
	this->themeMusic = nullptr;
}

bool Mixer::init() {
	this->rotateSound = Mix_LoadWAV("assets/sounds/Blip_Select58.wav");
	this->themeMusic = Mix_LoadMUS("assets/sounds/chill-out.mp3");
	Mix_VolumeMusic(50);
	Mix_VolumeChunk(this->rotateSound, 50);
	if (!this->rotateSound || !this->themeMusic) {
		std::cout << "Failed to load music!";
		return false;
	}
	return true;
}

void Mixer::free() {
	Mix_FreeChunk(this->rotateSound);
	Mix_FreeMusic(this->themeMusic);
	this->rotateSound = nullptr;
	this->themeMusic = nullptr;
}

void Mixer::playRotateSound() {
	Mix_PlayChannel(-1, this->rotateSound, 0);
}

void Mixer::playMusic() {
	Mix_PlayMusic(this->themeMusic, -1);
}

void Mixer::pauseMusic() {
	Mix_PauseMusic();
}


