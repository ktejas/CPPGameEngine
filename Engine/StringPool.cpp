#include "StringPool.h"
#include "EConsolePrint.h"

#include <cstring>
#include <malloc.h>
#include <assert.h>

namespace Engine
{
	namespace Memory
	{
		StringPool * StringPool::Create(size_t i_bytesInPool)
		{
			uint8_t * pPool = reinterpret_cast<uint8_t *>(_aligned_malloc(i_bytesInPool, 4));
			return new StringPool(pPool, i_bytesInPool);
		}

		StringPool::StringPool(uint8_t * i_pPool, size_t i_SizePool) :
			m_pStart(i_pPool),
			m_pCurrent(i_pPool),
			m_SizePool(i_SizePool),
			m_pEnd(i_pPool + i_SizePool)
		{

		}

		StringPool::~StringPool()
		{
			assert(m_pStart);
			free(m_pStart);
		}

		const char * StringPool::add(const char * i_pString)
		{
			size_t strlength = std::strlen(i_pString);
			// should assert if the len requires a bigger data type to store

			assert(m_pCurrent + sizeof(strsize_t) + strlength + 1 <= m_pEnd); // + 1 to account for '\0'

			const char * pPoolAddr = find(i_pString);
			if (pPoolAddr) return pPoolAddr;

			strsize_t * pStrSize = reinterpret_cast <strsize_t *> (m_pCurrent);
			*pStrSize = static_cast<strsize_t>(strlength);

			char * pStr = reinterpret_cast<char *> (m_pCurrent + sizeof(strsize_t));
			strcpy_s(pStr, strlength + 1, i_pString);

			m_pCurrent = reinterpret_cast <uint8_t *>(pStr + strlength + 1);

			return pStr;

		}

		const char * StringPool::find(const char * i_pString)
		{
			uint8_t * pStart = m_pStart;
			size_t strlength = std::strlen(i_pString);
			char  * pFoundStr = NULL;

			while (pStart < m_pCurrent)
			{
				strsize_t * pLen = reinterpret_cast<strsize_t *>(pStart);
				char * pStr = reinterpret_cast<char *>(pStart + sizeof(strsize_t));

				if (*pLen == strlength && strcmp(pStr, i_pString) == 0)
				{
					pFoundStr = pStr;
					break;
				}
				else
				{
					pStart += sizeof(strsize_t) + *pLen + 1;
				}
			}

			return pFoundStr;
		}
	} // namespace Memory
}// namespace Engine