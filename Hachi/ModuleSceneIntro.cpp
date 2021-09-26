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

			if (Button("About"))
				OpenPopup("About");

			ImVec2 center = GetMainViewport()->GetCenter();
			SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

			if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				Text("Hachi\n3D game engine made by Alexis Cosano Rodriguez.\n\n");
				Separator();
				Spacing();
				Text("External resources used:\n");
				Text("- ImGui v%s", ImGui::GetVersion());
				Text("- SDL v%d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
				Text("- OpenGL v3");
				Text("- MathGeoLib v1.5\n\n");
				Separator();
				Spacing();
				TextWrapped("MIT License"

					"Copyright(c) 2021 Alexis Cosano\n\n"

					"Permission is hereby granted, free of charge, to any person obtaining a copy"
					"of this softwareand associated documentation files (the 'Software'), to deal"
					"in the Software without restriction, including without limitation the rights"
					"to use, copy, modify, merge, publish, distribute, sublicense, and /or sell"
					"copies of the Software, and to permit persons to whom the Software is"
					"furnished to do so, subject to the following conditions:\n\n"

					"The above copyright noticeand this permission notice shall be included in all"
					"copies or substantial portions of the Software.\n\n"

					"THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
					"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
					"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE"
					"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
					"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
					"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
					"SOFTWARE.\n\n\n");

				if (Button("Close", ImVec2(120, 0))) { CloseCurrentPopup(); }

				EndPopup();
			}

			ImGui::EndMenu();
		}

		EndMainMenuBar();
	}

	if (Begin("Console"))
	{

		End();
	}

	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	return UPDATE_CONTINUE;
}