#include <Rosec.h>

#include "Tests/Player.h"


class ExampleLayer : public Rosec::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Player(0.0f, 0.0f), m_XPos(m_Player.getX()), m_YPos(m_Player.getY()) 
	{
		
	}

	void OnAttach() override
	{
		//Rosec::Shader& shader = Rosec::Shader::Get();
		

	}

	void OnUpdate() override
	{
		//RSC_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rosec::Event& event) override
	{
		//RSC_TRACE("{0}", event);
		if (Rosec::Input::IsKeyPressed(RSC_KEY_Y))
			RSC_WARN("Warning");
	}

private:
	Player m_Player;
	float m_XPos, m_YPos;
};

class Sandbox : public Rosec::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Rosec::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Rosec::Application* Rosec::CreateApplication()
{
	return new Sandbox();
}
