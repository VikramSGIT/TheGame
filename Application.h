#pragma once

#include "MarsHeader.h"
#include "Window/Window.h"
#include "Window/Windows/WindowsWindow.h"
#include "RenderAPI/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLRenderer.h"
#include "RenderAPI/Mesh.h"
#include "RenderAPI/Shader.h"
#include "RenderAPI/OpenGL/OpenGLTexture.h"
#include "Window/Layers/ImGUI/imguiLayer.h"
#include "Utils/Timer.h"
#include "Addons/ParticleSystem.h"

#include <chrono>
#include <random>

class Application
{
private:
	Ref<ME::Renderer::RenderAPI> renderer;
	Ref<Window::Window> window;
	bool Running = true;
	Scope<ME::Addon::ParticleSystem> m_Smoke, m_Fire;

	void OnEvent(Event::Event& e);
public:
	Application();
	~Application();
	void Init();
	void Run();
	Ref<Window::Window> GetWindow() { return window; }
	static Application& GetInstance() { return *s_Application; }
	static Application* s_Application;
};
