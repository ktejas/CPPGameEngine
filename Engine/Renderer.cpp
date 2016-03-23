#include "Renderer.h"
#include "GameObject.h"
#include "EConsolePrint.h"

#include <assert.h>
#include <stdio.h>

namespace Engine
{
	namespace Renderer
	{
		std::list<RenderInfo*> g_RenderObjects = std::list<RenderInfo*>();

		void Init()
		{
			
		}

		void Draw()
		{
			for (std::list<RenderInfo*>::iterator it = g_RenderObjects.begin(); it != g_RenderObjects.end(); it++)
			{
				GLib::BeginRendering();
				GLib::Sprites::BeginRendering();
				(*it)->Draw();
				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}
		}

		void RegisterRenderInfo(RenderInfo * i_pInfo)
		{
			g_RenderObjects.push_back(i_pInfo);
		}

		void ShutDown()
		{
			g_RenderObjects.clear();
			GLib::Shutdown();
		}

		RenderInfo::RenderInfo(GameObject * i_pGameObject, const char * i_pFilename) : m_pGameObject(i_pGameObject)
		{
			m_pSprite = CreateSprite(i_pFilename);
		}

		void RenderInfo::Draw()
		{
			Vector3 position = m_pGameObject->getPosition();
			GLib::Point2D point = { position.getX(), position.getY() };
			GLib::Sprites::RenderSprite(*m_pSprite, point);
		}

		RenderInfo::~RenderInfo()
		{
			GLib::Sprites::Release(m_pSprite);
		}

		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
		{
			assert(i_pFilename);

			size_t sizeTextureFile = 0;

			void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

			GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

			if (pTextureFile)
				delete[] pTextureFile;

			if (pTexture == nullptr)
				return NULL;

			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int depth = 0;

			bool result = GLib::GetDimensions(pTexture, width, height, depth);
			assert(result == true);
			assert((width > 0) && (height > 0));

			GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
			GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
			GLib::RGBA							Color = { 255, 255, 255, 255 };

			GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
			if (pSprite == nullptr)
			{
				GLib::Release(pTexture);
				return nullptr;
			}

			GLib::Sprites::SetTexture(*pSprite, *pTexture);

			return pSprite;
		}

		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
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
	} // namespace Renderer
} // namespace Engine