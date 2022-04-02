#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Shader.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"


namespace Rosec {

	class ROSEC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window>m_Window;
		LayerStack m_LayerStack;

		bool m_Running = true;


		static Application* s_Instance;
	};

	// TO BE defined in client-----------------
	Application* CreateApplication();

}
