#ifndef MIXER_H
#define MIXER_H

#include <SDL_mixer.h>

class Mixer {
	public:
		Mixer();
		bool init();
		void free();
		void playRotateSound();
		void playMusic();
		void pauseMusic();

	private:
		Mix_Music* themeMusic;
		Mix_Chunk* rotateSound;
		

};

#endif

