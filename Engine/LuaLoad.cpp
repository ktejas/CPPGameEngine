#include "LuaLoad.h"

#include "LuaWrapper.h"
#include "Engine.h"
#include "Actor.h"
#include "GameObject.h"
#include "Physics.h"
#include "AI.h"

namespace Engine
{

	LuaLoadTask::LuaLoadTask(const char * i_pFilename) : ThreadedFileProcessor::LoadTask(i_pFilename)
	{

	}

	void LuaLoadTask::ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes)
	{

		// Initialize us a lua_State
		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);

		luaL_openlibs(pLuaState);

		if (i_pBuffer && i_BufferBytes)
		{
			int			result = 0;

			// Do the initial buffer parsing
			result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(i_pBuffer), i_BufferBytes, nullptr);
			assert(result == 0);
			lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);

			int			type = LUA_TNIL;

			// Find the global variable named "Player" and push it onto stack.
			// If it doesn't find it it pushes a nil value instead
			result = lua_getglobal(pLuaState, "Player");
			assert(result == LUA_TTABLE);

			// Get the Actor name from the Player table
			// 1. Push the key string
			lua_pushstring(pLuaState, "name");
			// 2. Get the value associated with the key
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TSTRING);
			const char * pName = lua_tostring(pLuaState, -1);
			assert(pName != NULL);
			if (pName)
				pName = _strdup(pName);

			// 3. Remove the value from the stack now that we're done with it
			lua_pop(pLuaState, 1);

			// get initial_position from the Player table
			lua_pushstring(pLuaState, "initial_position");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float		Position[3] = { 0.0f };
			ReadFloatArray(pLuaState, -1, Position, 3);

			// we're done with the "initial_position" table - pop it
			lua_pop(pLuaState, 1);

			// get initial_velocity from the Player table
			lua_pushstring(pLuaState, "initial_velocity");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float		Velocity[3] = { 0.0f };
			ReadFloatArray(pLuaState, -1, Velocity, 3);

			// we're done with the "initial_velocty" table - pop it
			lua_pop(pLuaState, 1);

			// get bounding box table
			lua_pushstring(pLuaState, "bounding_box");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			// get bounding box offset
			lua_pushstring(pLuaState, "offset");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float		BoundingBox_Offset[3] = { 0.0f };
			ReadFloatArray(pLuaState, -1, BoundingBox_Offset, 3);

			// we're done with the "offset" table - pop it
			lua_pop(pLuaState, 1);

			// get size from bounding box
			lua_pushstring(pLuaState, "size");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float		BoundingBox_Size[4] = { 0.0f };
			ReadFloatArray(pLuaState, -1, BoundingBox_Size, 4);

			// we're done with the "size" table - pop it
			lua_pop(pLuaState, 1);
			// we're done with the "bounding_box" table - pop it
			lua_pop(pLuaState, 1);

			// let's process the "physics_settings" sub table
			lua_pushstring(pLuaState, "physics_settings");
			type = lua_gettable(pLuaState, -2);
			// It either needs to be a table or not there (no physics applied)
			assert((type == LUA_TNIL) || (type == LUA_TTABLE));

			if (type == LUA_TTABLE)
			{
				lua_pushstring(pLuaState, "mass");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TNUMBER);

				lua_pushstring(pLuaState, "drag");
				type = lua_gettable(pLuaState, -3);
				assert(type == LUA_TNUMBER);

				float mass = float(lua_tonumber(pLuaState, -2));
				float drag = float(lua_tonumber(pLuaState, -1));

				// pop the "mass" and "drag" values together
				lua_pop(pLuaState, 2);
			}

			// we're done with the "physics_settings" table - pop it
			// NOTE: If it didn't exist Lua would have pushed a nil value so still need the pop
			lua_pop(pLuaState, 1);

			// let's process the "render_settings" sub table
			const char * pPath;
			lua_pushstring(pLuaState, "render_settings");
			type = lua_gettable(pLuaState, -2);
			assert((type == LUA_TNIL) || (type == LUA_TTABLE));

			if (type == LUA_TTABLE)
			{
				lua_pushstring(pLuaState, "sprite");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TTABLE);
				{
					//----------------------------------//
					lua_pushstring(pLuaState, "path");
					type = lua_gettable(pLuaState, -2);
					assert(type == LUA_TSTRING);

					pPath = lua_tostring(pLuaState, -1);
					assert(pPath != NULL);
					if (pPath)
						pPath = _strdup(pPath);

					//remove path value from the stack now that we're done with it
					lua_pop(pLuaState, 1);
					//----------------------------------//

					lua_pushstring(pLuaState, "offset");
					type = lua_gettable(pLuaState, -2);
					assert(type == LUA_TTABLE);

					float Sprite_Offset[2] = { 0.0f };
					ReadFloatArray(pLuaState, -1, Sprite_Offset, 2);

					// pop "offset" table
					lua_pop(pLuaState, 1);

					lua_pushstring(pLuaState, "extents");
					type = lua_gettable(pLuaState, -2);
					assert(type == LUA_TTABLE);

					float Sprite_Extents[4] = { 0.0f };
					ReadFloatArray(pLuaState, -1, Sprite_Extents, 4);

					// pop "extents" table
					lua_pop(pLuaState, 1);


				}
				// pop "sprite" table
				lua_pop(pLuaState, 1);

				lua_pushstring(pLuaState, "sprite_color");
				type = lua_gettable(pLuaState, -2);
				if (type == LUA_TTABLE)
				{
					int			SpriteRGBA[4];
					ReadIntArray(pLuaState, -1, SpriteRGBA, 4);
				}

				// pop "sprite_color" table
				lua_pop(pLuaState, 1);
			}

			// pop "render_settings" table
			lua_pop(pLuaState, 1);

			// pop "Player" table
			lua_pop(pLuaState, 1);

			int stack_items = lua_gettop(pLuaState);
			assert(stack_items == 0);

			Engine::GameObject * obj = NULL;
			Engine::Physics::PhysicsInfo * phyInfo;
			Engine::AI::AIController * controller;
			Engine::Renderer::RenderInfo * renInfo;

			obj = new GameObject(Vector3(Position[0], Position[1], Position[2]), Vector3(Velocity[0], Velocity[1], Velocity[2]));

			phyInfo = new Physics::PhysicsInfo(obj);
			Physics::RegisterPhysicsInfo(phyInfo);

			controller = new AI::AIController(obj);
			AI::RegisterAIController(controller);

			renInfo = new Renderer::RenderInfo(obj, pPath);
			Renderer::RegisterRenderInfo(renInfo);
			m_pActor = new Actor("Sam", "Player");
			m_pActor->SetGameObject(obj);
			m_pActor->SetPhysicsInfo(phyInfo);
			m_pActor->SetRenderInfo(renInfo);
			m_pActor->SetController(controller);

		}
		lua_close(pLuaState);
	}

	Actor * LuaLoadTask::GetActor(void)
	{
		return m_pActor;
	}

} // namespace Engine