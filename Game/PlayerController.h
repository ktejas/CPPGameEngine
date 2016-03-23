#pragma once

#include "GameObject.h"
#include "AIController.h"

#ifndef __Game__PlayerController__H__
#define __Game__PlayerController__H__

class PlayerController : public Engine::AI::AIController
{
public:
	PlayerController(Engine::GameObject * i_GameObject);
	void Update(const float i_dt);
};

#endif