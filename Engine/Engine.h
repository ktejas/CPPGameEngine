#pragma once

#ifndef __Engine__Engine__H__
#define __Engine__Engine__H__

#include "Actor.h"

#include <Windows.h>

namespace Engine
{
	extern bool g_bQuit;

	bool Init(HINSTANCE i_hInstance, int i_nCmdShow, unsigned int i_WindowWidth, unsigned int i_WindowHeight);
	void Run();
	void Shutdown();
}

#endif /*(__Engine__Engine__H__)*/