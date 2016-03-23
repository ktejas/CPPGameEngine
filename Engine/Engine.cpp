#include "Engine.h"
#include "EInput.h"
#include "Timing.h"
#include "AI.h"
#include "Physics.h"
#include "Renderer.h"

#include "GLib.h"

#include <iostream>

namespace Engine
{
	bool g_bQuit = false;

	bool Init(HINSTANCE i_hInstance, int i_nCmdShow, unsigned int i_WindowWidth, unsigned int i_WindowHeight)
	{
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Flappy Bird", -1, i_WindowWidth, i_WindowHeight);

		if (bSuccess)
		{
			g_bQuit = false;

			Input::Init();
			Timing::Init();
			AI::Init();
			Physics::Init();
			Renderer::Init();
		}
		
		return true;
	}

	void Run()
	{
		do
		{
			GLib::Service(g_bQuit);

			if (!g_bQuit)
			{
				float dt = Timing::TimeSinceLastFrame();
				Input::Read();
				AI::Update(dt);

				Physics::Update(dt);

				Renderer::Draw();
			}

		} while (g_bQuit == false);
	}

	void Shutdown()
	{
		Renderer::ShutDown();
		Physics::Shutdown();
		AI::Shutdown();
		Input::Shutdown();
	}

} // namespace Engine