#pragma once

#ifndef __Engine__StringPool__H__
#define __Engine__StringPool__H__

#include <stdint.h>

#define strsize_t uint8_t

namespace Engine
{
	namespace Memory
	{
		class StringPool
		{
		public:

			static StringPool * Create(size_t i_bytesInPool);
			~StringPool();
			const char * add(const char * i_pString);
			const char * find(const char * i_pString);

		private:
			StringPool(uint8_t * i_pPool, size_t i_SizePool);

			size_t				m_SizePool;
			uint8_t *			m_pStart;
			uint8_t *			m_pEnd;
			uint8_t *			m_pCurrent;
		};

	} // namespace Memory
} //namespace Engine

#endif /* (__Engine__StringPool__H__) */