#include "Game.h"

#include "Engine.h"
#include "GameObject.h"
#include "Physics.h"
#include "AI.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "SmartPtr.h"
#include "StringPool.h"
#include "HashedString.h"
#include "LuaWrapper.h"
#include "EConsolePrint.h"
#include "ThreadedFileProcessor.h"
#include "LuaLoad.h"
#include "Actor.h"

namespace Game
{
	Engine::GameObject * obj = NULL;
	Engine::Physics::PhysicsInfo * phyInfo;
	Engine::AI::AIController * controller;
	Engine::Renderer::RenderInfo * renInfo;
	Engine::LuaLoadTask * loadTask;

	bool Init()
	{

		//StringPoolUnitTest();
		//HashedStringUnitTest();
		using namespace Engine;
		ThreadedFileProcessor &Processor = ThreadedFileProcessor::GetInstance();

		loadTask = new LuaLoadTask("data\\Player.lua");
		Processor.AddToLoadQueue(*loadTask);
		
		return true;
	}

	void StringPoolUnitTest()
	{
		using namespace Engine;
		int poolSize = 1024 * 10;
		Memory::StringPool * pPool = Memory::StringPool::Create(poolSize);

		const char * pName1 = pPool->add("Teja");
		const char * pName2 = pPool->add("Krishna");
		const char * pName3 = pPool->add("Teja");

		if (pName1 == pName3)
		{
			DEBUG_PRINT("StringPool Unit Test Successful\n");
		}

	}

	void HashedStringUnitTest()
	{
		using namespace Engine;

		HashedString testString("This is a test");
		HashedString duplicateString("This is a test");

		if (testString == duplicateString)
		{
			DEBUG_PRINT("HashedString Unit Test Successful\n");
		}

	}

	void Shutdown()
	{
		Engine::Actor * actor = loadTask->GetActor();
		delete actor;
		delete loadTask;
		Engine::ThreadedFileProcessor::Shutdown();
		/*delete renInfo;
		delete controller;
		delete phyInfo;
		delete obj;*/
	}
} // namespace Game