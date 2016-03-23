#pragma once

#ifndef __Engine__LuaUtility__H__
#define __Engine__LuaUtility__H__

#include "Lua\lua.hpp"

#include "Vector3.h"
#include "Actor.h"
#include <stdint.h>

namespace Engine
{
	Actor * CreateActor(const char * i_pScriptFilename);
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	int GetLuaTableEntries(lua_State * i_pState, int i_index);
	size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts);
	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);
	size_t GetFloatArray(lua_State * i_pState, int i_indexTable, const char * i_pArrayKey, float * o_pFloats, size_t i_numFloats);
	Vector3 GetVector3(lua_State * i_pState, int i_index);

} //namespace Engine

#endif /* (__Engine__LuaUtility__H__) */
