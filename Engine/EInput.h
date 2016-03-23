#pragma once

#ifndef __Engine__Input__H__
#define __Engine__Input__H__

namespace Engine
{
	namespace Input
	{
		extern bool g_Keys[255];
		void Init();
		void Read();
		void InputKeyCallBack(unsigned int i_VKeyID, bool bWentDown);
		bool IsKeyDown(unsigned int i_VkeyID);
		void Shutdown();

	} // namespace Input
}// namespace Engine

#endif /* (__Engine__Input__H__) */
