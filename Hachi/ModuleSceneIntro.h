#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Globals.h"


class ModuleSceneIntro : public Module
{
public:

	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:

	bool showDemoWindow = false;
};

#endif