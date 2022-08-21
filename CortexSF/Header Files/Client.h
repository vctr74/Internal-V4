#pragma once

namespace Cortex
{
	void Run( )
	{
		try
		{
			uint32_t round_state = Anvil::RoundManager->RoundState( );

			if ( round_state == 2 || round_state == 3 )
			{ 
				auto weapon = Anvil::GameManager->Controller( 0 )->PawnComponent( )->ActorDescriptor( )->CurrentWeapon( );
				 
				if ( Backend::skGetAsyncKeyState( VK_MBUTTON ) )
					weapon->Shoot( ), weapon->Spread( 0.0f );
			}
		} 
		catch ( ... )
		{

		} 
	} 
} 