#include "GLib.h"

namespace Engine
{
	namespace Input
	{
		bool g_Keys[255];

		void InputKeyCallBack(unsigned int i_VKeyID, bool bWentDown)
		{
			g_Keys[i_VKeyID] = bWentDown;
		}

		void Init()
		{
			GLib::SetKeyStateChangeCallback(InputKeyCallBack);
		}

		void Read()
		{

		}

		bool IsKeyDown(unsigned int i_VKeyID)
		{
			return g_Keys[i_VKeyID];
		}

		void Shutdown()
		{

		}
	}// namespace Input
} // namespace Engine