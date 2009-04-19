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

 
#ifdef _DEBUG
	#define ensure(M,V) { if(!(V)) { printf("Error: %s", (M)); throw 0; } }
#else
	//#define ensure(M,V) { if(!(V)) { printf("Error: %s", (M)); throw 0; } }
	#define ensure(M,V) {}
#endif

//---------------------------------------------------------

const char SOLID = '#';
const char EMPTY = '.';

typedef int coord_value_t;

struct coord_t
{
	coord_value_t x, y, z;
	coord_t() : x(0), y(0), z(0) {}
	coord_t(coord_value_t _x, coord_value_t _y, coord_value_t _z) : x(_x), y(_y), z(_z) {}

	void set_min(const coord_t& rh)	{	x = MIN(rh.x, x);	y = MIN(rh.y, y);	z = MIN(rh.z, z);	}
	void set_max(const coord_t& rh)	{	x = MAX(rh.x, x);	y = MAX(rh.y, y);	z = MAX(rh.z, z);	}
	void add(const coord_t& rh)	{	x += rh.x; y += rh.y; z += rh.z; }
	void sub(const coord_t& rh)	{	x -= rh.x; y -= rh.y; z -= rh.z; }
	void add_scalar(int v)	{	x += v; y += v; z += v; }
};

const coord_t COORD_INF_NEG = coord_t(-1000, -1000, -1000);
const coord_t COORD_INF_POS = coord_t( 1000,  1000,  1000);

#define DEF_CUBE(name, max_size) char name[(max_size)][(max_size)][(max_size)];

#define FOR_ALL_CUBE(x,y,z,size)	for(int z=0; z<(size).z; z++)				\
																		for(int y=0; y<(size).y; y++)			\
																			for(int x=0; x<(size).x; x++)		\


struct point_group_t {
	int				quantity;
	coord_t*	coords;
	
	point_group_t() : quantity(0), coords(0) {}
};


enum axis_t
{
	axis_x,
	axis_first = axis_x,
	axis_y,
	axis_z,
	
	axis_numof
};

enum direction_t
{
	direction_x,
	direction_first = axis_x,
	direction_x_inv,
	direction_y,
	direction_y_inv,
	direction_z,
	direction_z_inv,
	
	direction_numof
};

direction_t axis2direction(const axis_t& axis, const bool& inverted);
axis_t direction2axis(const direction_t& direction, bool& inverted);
coord_t direction2delta(const direction_t& direction);

enum angle_t
{
	angle_none,
	angle_first = angle_none,
	
	angle_90,
	angle_180,
	angle_270,
	
	angle_numof
};



#endif // TYPEDEF_H_INCLUDED