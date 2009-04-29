#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED

#include <stdio.h>


const unsigned int BIG_BUFFER = 100000;

#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))

#define FOR_ALL_ENUM(it) for(it##_t it=it##_first; it != it##_numof; it = (it##_t)(it+1))
#define FOR_ALL_ENUM2(it,prefix) for(prefix##_t it=prefix##_first; it != prefix##_numof; it = (prefix##_t)(it+1))

#ifdef WIN32

	#include <conio.h>

	#include <crtdbg.h>

	#ifdef _DEBUG
		#define dnew new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#else
		#define dnew new
	#endif
	
	#define ENABLE_MEMORY_LEAK_CONTROL										\
		int dbgflag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);	\
		dbgflag |= _CRTDBG_LEAK_CHECK_DF;										\
		_CrtSetDbgFlag(dbgflag);
		
	#define WAIT_KEY_PRESSED _getch();
	
#else

	#define dnew new
	#define ENABLE_MEMORY_LEAK_CONTROL
	
	#define WAIT_KEY_PRESSED
	
#endif											

 
#define error(M) { printf("Error: %s", (M)); throw 0; }

#ifdef _DEBUG
	#define ensure(M,V) { if(!(V)) { printf("Error: %s", (M)); throw 0; } }
#else
	//#define ensure(M,V) { if(!(V)) { printf("Error: %s", (M)); throw 0; } }
	#define ensure(M,V) {}
#endif


typedef int coord_value_t;


enum angle_t
{
	angle_none,
	angle_first = angle_none,
	
	angle_90,
	angle_180,
	angle_270,
	
	angle_numof
};

#define error_call_of_pure_virtual_method(CN) \
							{ error(#CN ": Call of base class pure virtual method"); }

#endif // TYPEDEF_H_INCLUDED