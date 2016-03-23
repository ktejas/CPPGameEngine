#include "Actor.h"
#include "EConsolePrint.h"
#include <string.h>
#include <assert.h>

namespace Engine
{
	Actor::Actor(const char * i_pName, const char * i_pType) : 
		m_pName( _strdup (i_pName) ),
		m_pType( _strdup (i_pType) )
	{

	}

	bool Actor::IsType(const char * i_pType)
	{
		assert(i_pType);
		return strcmp(m_pType, i_pType) == 0;
	}

	void Actor::SetPhysicsInfo(Physics::PhysicsInfo * i_pInfo)
	{
		m_pPhysicsInfo = i_pInfo;
	}

	void Actor::SetRenderInfo(Renderer::RenderInfo * i_pInfo)
	{
		m_pRenderInfo = i_pInfo;
	}

	void Actor::SetGameObject(GameObject * i_pGameObject)
	{
		m_pGameObject = i_pGameObject;
	}

	void Actor::SetController(AI::AIController * i_pAIController)
	{
		m_pController = i_pAIController;
	}


	Actor::~Actor()
	{

		free(const_cast<char *>(m_pName));
		free(const_cast<char *>(m_pType));

		delete m_pRenderInfo;
		delete m_pPhysicsInfo;
		delete m_pController;
		delete m_pGameObject;
	}
} //namespace Engine