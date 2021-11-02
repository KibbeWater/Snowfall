#pragma once

//-----------------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------------

typedef unsigned __int8		byte;
typedef wchar_t				wchar;
#if defined(__cpp_char8_t)
typedef char8_t				char8;
typedef char16_t			char16;
typedef char32_t			char32;
#endif

typedef signed __int8		int8;
typedef signed __int16		int16;
typedef signed __int32		int32;
typedef signed __int64		int64;

typedef unsigned __int32	uint;
typedef unsigned __int8		uint8;
typedef unsigned __int16	uint16;
typedef unsigned __int32	uint32;
typedef unsigned __int64	uint64;

typedef unsigned __int64	QWORD;

#ifdef _WIN64
	typedef unsigned __int64  INTPTR;
#else
	typedef unsigned __int32  INTPTR;
#endif


//-----------------------------------------------------------------------------
// Usings
//-----------------------------------------------------------------------------

using std::unordered_map;
using std::ofstream;
using std::ifstream;
using std::to_string;
using std::stringstream;


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

// Build version
#if _DEBUG
	#define DEBUG 1
#else
	#define _RELEASE 1
#endif

// Using inlines
#if DEBUG
	#define INL 
#else
	#define INL __forceinline
#endif

// u8 fix for C++20
#if defined(__cpp_char8_t)
	#define u8(x) (const char*)u8##x
#else
	#define u8(x) u8##x
#endif

// Other
#define NOINL __declspec(noinline)
#define UNSIG unsigned
#define ARR_SIZE(a) sizeof(a) / sizeof(*a)
