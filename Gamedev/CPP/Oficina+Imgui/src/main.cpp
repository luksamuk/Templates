#include <OficinaFramework/OficinaFramework.hpp>
#include <string>
#include <list>
#include "imgui_impl_sdl.hpp"
using namespace OficinaFramework;

class TestScreen : public ScreenSystem::Screen
{
	private:
		bool show_test_window = true;
		bool show_another_window = false;
		ImVec4 clear_color;
	public:
		TestScreen()
		{
			SetActive(true);
			SetVisible(true);
		}

		void Initialize() override
		{
			// Start ImGui
			ImGui_ImplSdl_Init(ScreenSystem::GetWindowHandle());
			clear_color = ImColor(114, 144, 154);

			ScreenSystem::Screen::Initialize();
		}

		void LoadContent() override
		{
			ScreenSystem::Screen::LoadContent();
		}

		void UnloadContent() override
		{
			ScreenSystem::Screen::UnloadContent();
		}

		void Update() override
		{
			// TODO: Make ImGui process input events (typing-related)
			// or write an event handler for ImGui myself
			ImGui_ImplSdl_NewFrame(ScreenSystem::GetWindowHandle());

			{
				static float f = 0.0f;
				ImGui::Text("Hello, world!");
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
				ImGui::ColorEdit3("clear color", (float*)&clear_color);
				if (ImGui::Button("Test Window")) show_test_window ^= 1;
				if (ImGui::Button("Another Window")) show_another_window ^= 1;
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			// 2. Show another simple window, this time using an explicit Begin/End pair
			if (show_another_window)
			{
				ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
				ImGui::Begin("Another Window", &show_another_window);
				ImGui::Text("Hello");
				ImGui::End();
			}

			// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
			if (show_test_window)
			{
				ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
				ImGui::ShowTestWindow(&show_test_window);
			}
		}

		void Draw() override
		{
			ImGui::Render();
		}
};

int main(int argc, char** argv)
{
	std::list<std::string>* confv = new std::list<std::string>;
	confv->push_back("gamename=ImGui OficinaFramework Test");
	confv->push_back("framerate=60Hz");
	confv->push_back("resolution=720p");

	EngineCore::Initialize(argc, argv, confv);
	//RenderingSystem::glClearColorM(BLACK);
	ScreenSystem::Debug_SetFont(RenderingSystem::TexturePool::LoadDefaultFont());
	InputSystem::BindDefaultKeys();

	ScreenSystem::SetDebug(true);
	RenderingSystem::SetCameraPosition(RenderingSystem::GetResolution().toVec2() / 2.0f);
	ScreenSystem::AddScreen(new TestScreen);

	return EngineCore::DoGameLoop();
}
