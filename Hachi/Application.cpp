#include "Application.h"


Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);

	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(scene_intro);
	AddModule(renderer3D);
}

Application::~Application()
{
	list<Module*>::reverse_iterator item;
	item = list_modules.rbegin();

	while (item != list_modules.rend())
	{
		delete* item;
		item++;
	}

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	list<Module*>::iterator item_list;
	Module* it;

	for (item_list = list_modules.begin(); item_list != list_modules.end() && ret == true; ++item_list) {

			it = *item_list;
			ret = it->Init();
	}

	LOG("Application Start --------------");

	for (item_list = list_modules.begin(); item_list != list_modules.end() && ret == true; ++item_list) {

			it = *item_list;
			ret = it->Start();
	}
	
	ms_timer.Start();

	return ret;
}

void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

void Application::FinishUpdate(){}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	list<Module*>::iterator item_list;
	Module* it;

	for (item_list = list_modules.begin(); item_list != list_modules.end() && ret == UPDATE_CONTINUE; ++item_list) {

			it = *item_list;
			ret = it->PreUpdate(dt);
	}

	for (item_list = list_modules.begin(); item_list != list_modules.end() && ret == UPDATE_CONTINUE; ++item_list) {

			it = *item_list;
			ret = it->Update(dt);
	}

	for (item_list = list_modules.begin(); item_list != list_modules.end() && ret == UPDATE_CONTINUE; ++item_list) {

			it = *item_list;
			ret = it->PostUpdate(dt);
	}

	FinishUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	list<Module*>::reverse_iterator item;
	item = list_modules.rbegin();

	while (item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}