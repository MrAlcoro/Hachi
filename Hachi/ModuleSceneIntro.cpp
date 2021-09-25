#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


using namespace ImGui;

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled){}

ModuleSceneIntro::~ModuleSceneIntro(){}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& io = GetIO(); (void)io;
	StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, NULL);
	ImGui_ImplOpenGL3_Init();

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	DestroyContext();
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();	

	return true;
}

update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	NewFrame();

	static bool showDemoWindow = false;

	if (showDemoWindow)
		ShowDemoWindow(&showDemoWindow);

	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("Exit"))
				return UPDATE_STOP;
			
			ImGui::EndMenu();
		}

		if (BeginMenu("Help"))
		{
			ImGui::MenuItem("Demo window", NULL, &showDemoWindow);

			ImGui::EndMenu();
		}

		EndMainMenuBar();
	}

	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	return UPDATE_CONTINUE;
}