#pragma once


//-----------------------------------------------------------------------------
// Macro
//-----------------------------------------------------------------------------

// Build version
#if _DEBUG
	#define DEBUG 1
#else
	#define RELEASE 1
#endif

// Using inlines
#if DEBUG
	#define INL 
#else
	#define INL __forceinline
#endif


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define NOINL __declspec(noinline)
#define UNSIG unsigned

#define ARR_SIZE(a) sizeof(a) / sizeof(*a)


//-----------------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------------

typedef wchar_t				wchar; // _wc
typedef long long			lon; // _l

typedef unsigned int		uint; // _ui
typedef unsigned long long	ulon; // _ul

typedef unsigned char		byte;
typedef unsigned short		word;
typedef unsigned int		dword;
typedef unsigned long long	tword;

typedef signed char			int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;
typedef unsigned int		uintptr;


//-----------------------------------------------------------------------------
// Usings
//-----------------------------------------------------------------------------

//using std::string;
//using std::vector;
using std::unordered_map;
using std::ofstream;
using std::ifstream;



