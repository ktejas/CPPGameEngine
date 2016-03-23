#pragma once

#ifndef __Engine__Lua__Load__
#define __Engine__Lua__Load__

#include "ThreadedFileProcessor.h"
#include "Actor.h"

namespace Engine
{
	class LuaLoadTask : public ThreadedFileProcessor::LoadTask
	{
	public:
		LuaLoadTask(const char * i_pFilename);
		virtual void ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes);
		Actor * GetActor(void);

	private:
		Actor * m_pActor;
	};
} // namespace Engine

#endif /* (__Engine__Lua__Load__) */