#include "Engine.h"
#include "Game.h"

#include <windows.h>
#include <iostream>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	if (Engine::Init(i_hInstance, i_nCmdShow, 800, 600))
	{
		if (Game::Init())
		{
			Engine::Run();
			Game::Shutdown();
		}
		Engine::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}