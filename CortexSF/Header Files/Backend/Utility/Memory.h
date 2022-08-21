#pragma once

namespace Memory
{
	inline bool Check( uint64_t ptr )
	{
		if ( !ptr ) return false;
		return ( ptr > 0x00010000 && ptr < 0x7FFFFFFEFFFF );
	}
}