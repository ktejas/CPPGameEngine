#include "LuaWrapper.h"
#include "Engine.h"
#include "GameObject.h"
#include "Physics.h"
#include "AI.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

namespace Engine
{
	Actor * CreateActor(const char * i_pScriptFilename)
	{
		// Initialize us a lua_State
		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);

		luaL_openlibs(pLuaState);

		// Read in a file
		size_t			sizeFile = 0;
		uint8_t *		pFileContents = LoadFile(i_pScriptFilename, sizeFile);

		Actor * actor = NULL;

		if (pFileContents  && sizeFile)
		{
			int			result = 0;

			// Do the initial buffer parsing
			result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
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

			delete[] pFileContents;

			//float	Position[3]
			//float Velocity[3];
			//const char * pPath;

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
			actor = new Actor("Sam", "Player");
			actor->SetGameObject(obj);
			actor->SetPhysicsInfo(phyInfo);
			actor->SetRenderInfo(renInfo);
			actor->SetController(controller);

		}
		lua_close(pLuaState);
		return actor;
	}

	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
	{
		assert(i_pFilename != NULL);

		FILE * pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;

		assert(pFile != NULL);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		uint8_t * pBuffer = new uint8_t[FileSize];
		assert(pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}

	int GetLuaTableEntries(lua_State * i_pState, int i_index)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);

		lua_len(i_pState, i_index);
		assert(lua_type(i_pState, -1) == LUA_TNUMBER);

		lua_Integer table_entries = lua_tointeger(i_pState, -1);
		lua_pop(i_pState, 1);

		assert(table_entries <= INT_MAX);

		return static_cast<int>(table_entries);
	}

	size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);

		size_t	index = 0;

		lua_pushnil(i_pState);

		while (lua_next(i_pState, i_index - 1) != 0)
		{
			if (lua_type(i_pState, -1) == LUA_TNUMBER)
			{
				lua_Integer lValue = lua_tointeger(i_pState, -1);
				assert(lValue <= INT_MAX);

				o_pInts[index] = lValue < INT_MAX ? int(lValue) : INT_MAX;
			}
			else
			{
				// DEBUG_PRINT( "Expected a number at position %d while reading table as int array.\n", index );
			}

			lua_pop(i_pState, 1);

			if (++index == i_numInts)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}

		return index;
	}

	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);

		size_t				index = 0;

		lua_pushnil(i_pState);

		while (lua_next(i_pState, i_index - 1) != 0)
		{
			if (lua_type(i_pState, -1) == LUA_TNUMBER)
			{
				o_pFloats[index] = float(lua_tonumber(i_pState, -1));
			}
			else
			{
				// DEBUG_PRINT( "Expected a number at position %d while reading table as float array.\n", index );
			}

			// pop the value now that we've retrieved it
			lua_pop(i_pState, 1);
			if (++index == i_numFloats)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}
		return index;
	}

	size_t GetFloatArray(lua_State * i_pState, int i_indexTable, const char * i_pArrayKey, float * o_pFloats, size_t i_numFloats)
	{
		assert(i_pArrayKey);

		lua_pushstring(i_pState, i_pArrayKey);
		i_indexTable--;

		int type = lua_gettable(i_pState, i_indexTable);

		size_t itemsRead = 0;

		if (type == LUA_TTABLE)
			itemsRead = ReadFloatArray(i_pState, i_indexTable, o_pFloats, i_numFloats);
		else
		{
			// DEBUG_PRINT( "Expected Lua table for %s found value of type %d.\n", i_pArrayKey, type );
		}

		lua_pop(i_pState, 1);

		return itemsRead;
	}

	Vector3 GetVector3(lua_State * i_pState, int i_index)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);

		const size_t		numFloats = 3;
		float				v[numFloats] = { 0 };

		size_t	readFloats = ReadFloatArray(i_pState, i_index, v, numFloats);

		return Vector3(v[0], v[1], v[2]);
	}


} //namespace Engine