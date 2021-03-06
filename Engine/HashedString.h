#pragma once

#ifndef __Engine__HashedString__H__
#define __Engine__HashedString__H__

namespace Engine
{
	class HashedString
	{
	public:
		HashedString();
		~HashedString();

		HashedString(const char * i_string);
		HashedString(const HashedString & i_other);
		HashedString & operator=(const HashedString & i_other);

		unsigned int Get() const;

		bool operator==(const HashedString & i_other) const;

		static unsigned int Hash(const char * i_string);
		static unsigned int Hash(const void * i_bytes, unsigned int i_count);
	private:
		unsigned int 	m_Hash;

#ifdef DEBUG_KEEP_STRING
		const char * 	m_pString;
#endif
	};
} //namespace Engine

#include "HashedString-inl.h"

#endif /* (__Engine__HashedString__H__) */
