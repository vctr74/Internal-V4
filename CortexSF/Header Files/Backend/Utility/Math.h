#pragma once

namespace Math
{
	bool Transform( __int64 bones, __m128* bone_info, __m128* output )
	{
		__m128 v5; // xmm2
		__m128 v6; // xmm3
		__m128 v7; // xmm0
		__m128 v8; // xmm4
		__m128 v9; // xmm1

		__m128 v10 = { 0.500f, 0.500f, 0.500f, 0.500f };
		__m128 v11 = { 2.000f, 2.000f, 2.000f, 0.000f };

		__m128 v12 = *( __m128* )( bones );
		__m128 v13 = *( __m128* )( bones + 0x10 );

		v5 = v13;

		v6 = _mm_mul_ps( *( __m128* )bone_info, v5 );
		v6.m128_f32[ 0 ] = v6.m128_f32[ 0 ]
			+ ( float ) ( _mm_cvtss_f32( _mm_shuffle_ps( v6, v6, 0x55 ) ) + _mm_cvtss_f32( _mm_shuffle_ps( v6, v6, 0xAA ) ) );
		v7 = _mm_shuffle_ps( v13, v5, 0xFF );
		v8 = _mm_sub_ps(
			_mm_mul_ps( _mm_shuffle_ps( v5, v5, 0xD2 ), *( __m128* )bone_info ),
			_mm_mul_ps( _mm_shuffle_ps( *( __m128* )bone_info, *( __m128* )bone_info, 0xD2 ), v5 ) );
		v9 = _mm_shuffle_ps( v12, v12, 0x93 );
		v9.m128_f32[ 0 ] = 0.0;
		*( __m128* )output = _mm_add_ps(
			_mm_shuffle_ps( v9, v9, 0x39 ),
			_mm_mul_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps( _mm_shuffle_ps( v8, v8, 0xD2 ), v7 ),
						_mm_mul_ps( _mm_shuffle_ps( v6, v6, 0 ), v5 ) ),
					_mm_mul_ps(
						_mm_sub_ps( _mm_mul_ps( v7, v7 ), ( __m128 )v10 ),
						*( __m128* )bone_info ) ),
				( __m128 )v11 ) );
		return true;
	}
	
	const vec4_t ToVector( const __m128i* m128 )
	{
		__m128i quat = _mm_load_si128( m128 );
		return *( vec4_t* ) &quat;
	} 
}