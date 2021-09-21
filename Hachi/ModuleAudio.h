#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <vector>

#define DEFAULT_MUSIC_FADE_TIME 2.0f


using namespace std;

class ModuleAudio : public Module
{
public:

	ModuleAudio(Application* app, bool start_enabled = true);
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	unsigned int LoadFx(const char* path);

	bool PlayFx(unsigned int fx, int repeat = 0);

private:

	Mix_Music*			music;
	vector<Mix_Chunk*>	fx;
};

#endif