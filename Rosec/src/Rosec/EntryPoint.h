#pragma once

extern Rosec::Application* Rosec::CreateApplication();


int main(int argc, char** argv)
{
	Rosec::Log::Init();

	auto app = Rosec::CreateApplication();
	app->Run();
	delete app;
	return 0;
}