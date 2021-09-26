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
	ImFont* defaultFont = io.Fonts->AddFontFromFileTTF("../Fonts/arial_unicode.ttf", 17.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
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
	static bool showConfigWindow = false;

	if (showDemoWindow)
		ShowDemoWindow(&showDemoWindow);

	if (showConfigWindow)
	{
		ImGui::Begin("Engine configuration");
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::TextWrapped("Engine name: Hachi");
		}

		if (ImGui::CollapsingHeader("Window"))
		{
			// Lorem ipsum
		}

		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::TextWrapped("Mouse position:");
			ImGui::SameLine();
			ImGui::TextColored({ 255, 255, 0, 255 }, "X: %i ", App->input->GetMouseX());
			ImGui::SameLine();
			ImGui::TextColored({ 255, 255, 0, 255 }, "Y: %i", App->input->GetMouseY());
		}

		if (ImGui::CollapsingHeader("User's information"))
		{
			ImGui::BulletText("CPU cache line size: %d", SDL_GetCPUCacheLineSize());
			ImGui::BulletText("CPU cores available: %d", SDL_GetCPUCount());
			ImGui::BulletText("RAM configured: %d", SDL_GetSystemRAM());
			ImGui::BulletText("RAM configured: %d", SDL_GetSystemRAM());
			ImGui::BulletText("Has 3DNow!: %d", SDL_Has3DNow());
			ImGui::BulletText("Has AltiVec: %d", SDL_HasAltiVec());
			ImGui::BulletText("Has AVX: %d", SDL_HasAVX());
			ImGui::BulletText("Has AVX2: %d", SDL_HasAVX2());
			ImGui::BulletText("Has MMX: %d", SDL_HasMMX());
			ImGui::BulletText("Has RDTSC: %d", SDL_HasRDTSC());
			ImGui::BulletText("Has SSE: %d", SDL_HasSSE());
			ImGui::BulletText("Has SSE2: %d", SDL_HasSSE2());
			ImGui::BulletText("Has SSE3: %d", SDL_HasSSE3());
			ImGui::BulletText("Has SSE41: %d", SDL_HasSSE41());
			ImGui::BulletText("Has SSE42: %d", SDL_HasSSE42());
		}

		ImGui::End();
	}

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

			ImGui::MenuItem("Config window", NULL, &showConfigWindow);

			if (Button("About"))
				OpenPopup("About");

			ImVec2 center = GetMainViewport()->GetCenter();
			SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.4f));

			if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				Text(u8"ハチ (Hachi)\n3D game engine made by Alexis Cosano Rodriguez.\n\n");
				Separator();
				Spacing();
				Text("External resources used:\n");
				BulletText("ImGui v%s", ImGui::GetVersion());
				BulletText("SDL v%d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
				BulletText("OpenGL v3");
				BulletText("MathGeoLib v1.5\n\n");
				Separator();
				Spacing();
				TextWrapped("MIT License"

					"Copyright(c) 2021 Alexis Cosano\n\n"

					"Permission is hereby granted, free of charge, to any person obtaining a copy"
					"of this software and associated documentation files (the 'Software'), to deal"
					"in the Software without restriction, including without limitation the rights"
					"to use, copy, modify, merge, publish, distribute, sublicense, and /or sell"
					"copies of the Software, and to permit persons to whom the Software is"
					"furnished to do so, subject to the following conditions:\n\n"

					"The above copyright notice and this permission notice shall be included in all"
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