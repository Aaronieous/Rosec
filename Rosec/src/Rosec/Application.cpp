#include "rscpch.h"
#include "Application.h"

#include "Input.h"

#include <glad/glad.h>


namespace Rosec {


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		RSC_CORE_ASSERT(!s_Instance, "Application already exists! Instance must be NULL!")
		s_Instance = this;

		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(RSC_BIND_FN(Application::OnEvent));
		Shader::Create();


	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RSC_BIND_FN(Application::OnWindowClose));

		//RSC_CORE_TRACE("{0}", e);	

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	//----------------------------Main Loop-----------------------------------//

	void Application::Run()
	{

		
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();


			m_Window->OnUpdate();
		}
	}

	//------------------------------------------------------------------------//

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
};
