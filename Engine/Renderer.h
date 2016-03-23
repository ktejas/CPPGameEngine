#pragma once

#ifndef __Engine__Renderer__H__
#define __Engine__Renderer__H__

#include "GLib.h"
#include "GameObject.h"

#include <list>

namespace Engine
{
	namespace Renderer
	{
		class RenderInfo
		{
		public:
			RenderInfo(GameObject * i_pGameObject, const char * i_pFilename);
			void Draw();
			~RenderInfo();
		private:
			GameObject				* m_pGameObject;
			GLib::Sprites::Sprite	* m_pSprite;
		};

		extern std::list<RenderInfo*> g_RenderObjects;

		void Init();
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
		void Draw();
		void RegisterRenderInfo(RenderInfo * i_pInfo);
		void ShutDown();
	}
}

#endif /* (__Engine__Renderer__H__) */