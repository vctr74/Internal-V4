#pragma once 

namespace Anvil // overview
{ 
	class _CameraManager;
	class _GameManager; 
	class _RoundManager;

	_CameraManager* CameraManager;
	_GameManager* GameManager;
	_RoundManager* RoundManager;
	 
	namespace Player
	{ 
		class _Controller;
		class _ReplicationInformation;
		class _PawnComponent;
		class _Skeleon;
		class _ActorDescriptor;
		class _WeaponManager;
	} 
	inline void Initialize( ); 
}

namespace Anvil
{
	class _CameraManager
	{
	public:
		vec3_t DecryptView( __m128i encrypted )  
		{  

		}
		vec3_t ViewTranslation( )
		{ 
			 
		}
	};
	class _GameManager
	{
	public:   
		Player::_Controller* Controller( int Index )
		{
			uintptr_t controller_list = *( uintptr_t* ) ( this + 0x70 ) - 0x4A; 
			return *reinterpret_cast< Player::_Controller** >( ( controller_list + ( Index * 8i64 ) ) ); 
		}  
	}; 
	class _RoundManager
	{
	public: 
		/// <summary>
		/// RoundSwap = 0,
		///	OperatorSelection = 1,
		///	PreperationPhase = 2,
		///	ActionPhase = 3,
		///	RoundEnd = 4,
		///	MainMenu = 5
		/// </summary> 
		uint32_t RoundState( )
		{
			return ( ( *( uint32_t* ) ( this + 0xF8 ) ^ 0x98A1F310 ) >> 0x6 ) - 0x26;
		}
	};

	_CameraManager* GetCameraManager( )
	{
		return reinterpret_cast< _CameraManager* >( std::rotl( *( uintptr_t* ) ( *( uintptr_t* ) ( ( uintptr_t )Backend::skGetModuleHandleA( NULL ) + 0x6760E78 ) + 0x40 ) ^ 0xE86459E5EF6B5C18, 0x11 ) + 0x56737AE56A1000C7 );
	}
	_GameManager* GetGameManager( )
	{
		return reinterpret_cast< _GameManager* >( std::rotl( *( uintptr_t* ) ( ( uintptr_t ) Backend::skGetModuleHandleA( NULL ) + 0x81F7A60 ) - 0x24, 0x1A ) );
	} 
	_RoundManager* GetRoundManager( )
	{
		return reinterpret_cast< _RoundManager* >( std::rotl( *( uintptr_t* ) ( ( uintptr_t ) Backend::skGetModuleHandleA( NULL ) + 0x7583058 ) + 0x2C797E6189BC6F4D, 0x2D ) + 0x377614FB328C2FA0 );
	}
		 
	namespace Player
	{
		class _Controller
		{
		public:
			_PawnComponent* PawnComponent( )
			{ 
				return reinterpret_cast< _PawnComponent* >( ( ( *( uintptr_t* ) ( this + 0x38 ) - 0x46 ) ^ 0x7F ) + 0x4B10EB6F874EE4C7 );
			}
			_ReplicationInformation* ReplicationInformation( )
			{
				return reinterpret_cast< _ReplicationInformation* >( ( ( *( uintptr_t* ) ( this + 0xA8 ) - 0xB9BC19B078F9299 ) ^ 0x4B ) - 0x5F );
			}
		};
		class _ReplicationInformation
		{
		public:
			const char* PlayerName( )
			{
				return *( const char** ) ( this + 0x9D0 );
			} 
		};
		class _PawnComponent
		{
		public:   
			_ActorDescriptor* ActorDescriptor( )
			{
				return reinterpret_cast< _ActorDescriptor* >( ( ( *( uintptr_t* ) ( this + 0x18 ) - 0x64 ) ^ 0x47A9D613D41EBE75 ) - 0x12 );
			}
			_Skeleon* Skeleton( )
			{
				return reinterpret_cast< _Skeleon* >( ( ( *( uintptr_t* ) ( this + 0x9B8 ) ^ 0x5A4A3300808D5FBB ) - 101 ) ^ 0x4E1635573171789C );
			}
		};
		class _Skeleon
		{
		public:
			vec3_t BonePosition( int index )
			{ 
				auto bones = *( uint64_t* ) ( *( uint64_t* ) ( this + 0x0 ) + 0x250 );
				if ( !bones ) return {};

				auto id_ = *( uint32_t* ) ( *( uint64_t* ) ( *( uint64_t* ) ( this + 0x0 ) + 0xB8 ) + index * 0x4 );
				auto info = *( __m128* )( *( uint64_t* ) ( bones + 0x58 ) + ( 0x20 * id_ ) );
				if ( !( &info ) ) return {};

				__m128 result;

				Math::Transform( bones, &info, &result );

				return { result.m128_f32[ 0 ], result.m128_f32[ 1 ], result.m128_f32[ 2 ] };
			}
		private:
			 
		};
		class _ActorDescriptor 
		{
		public: 
			_WeaponManager* CurrentWeapon( )
			{ 
				auto current_weapon = std::rotl( *( uintptr_t* ) ( ( *( uintptr_t* ) ( ( *( uintptr_t* ) ( ( *( uint64_t* ) ( this->GetComponent( *( uintptr_t* ) ( this + 0x221 ) ) + 0x68 ) ^ 0x4310901AECDBC648i64 ) + 0x702BB7122605A1Ci64 ) ) + 0x1B0 ) ) + 0x268 ) - 0x6B88C874D9CB6D0Ai64, 0x2E ) - 0x8855542A312108Bi64; // was too lazy to do it proper.
				if ( !Memory::Check( current_weapon ) ) // ik its useless at that point 
					return { };
				return reinterpret_cast< _WeaponManager* >( current_weapon );
			}
		private:
			uintptr_t GetComponent( uint8_t index )
			{
				return *( uintptr_t* ) ( *( uintptr_t* ) ( ( uintptr_t ) this + 0xD8 ) + ( index * sizeof( uintptr_t ) ) );
			}
		};
		class _WeaponManager
		{
		public:
			void Shoot( )
			{
				if ( this )
					reinterpret_cast < void( __fastcall* )( __int64 ) > ( ( uintptr_t ) Backend::skGetModuleHandleA( NULL ) + 0x788690 ) ( ( __int64 ) this );
			}
			void Spread( std::uint32_t value )
			{
				if ( this )
					*( uint32_t* ) ( this + 0x30 ) = std::rotr<uint32_t>( std::rotr<uint32_t>( *( uint32_t* ) ( &value ), 24 ) + 1992768509, 1 );
			}
			void Shoot( vec3_t local_position, vec3_t target_position )
			{
				 
			}
		};
	}
	namespace Havok
	{ 
		 
	}

	inline void Initialize( )
	{ 
		CameraManager = GetCameraManager( );
		GameManager = GetGameManager( );
		RoundManager = GetRoundManager( ); 
	} 
}
 