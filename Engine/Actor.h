#pragma once

#ifndef __Engine__Actor__H__
#define __Engine__Actor__H__

#include "GameObject.h"
#include "PhysicsInfo.h"
#include "Renderer.h"
#include "AIController.h"

namespace Engine
{

	class Actor
	{
	public:
		Actor();
		Actor(const char * i_pName, const char * i_pType);
		bool IsType(const char * i_pType);
		void SetPhysicsInfo(Physics::PhysicsInfo * i_pInfo);
		void SetRenderInfo(Renderer::RenderInfo * i_pInfo);
		void SetGameObject(GameObject * i_pGameObject);
		void SetController(AI::AIController * i_pAIController);
		Physics::PhysicsInfo * GetPhysicsInfo();
		Renderer::RenderInfo * GetRenderInfo();
		GameObject * GetGameObject();
		~Actor();

	private:

		const char *			m_pName;
		const char *			m_pType;
		GameObject *			m_pGameObject;
		Physics::PhysicsInfo *	m_pPhysicsInfo;
		Renderer::RenderInfo *	m_pRenderInfo;
		AI::AIController *		m_pController;

	};
} //namespace Engine

#endif /* (__Engine__Actor__H__) */