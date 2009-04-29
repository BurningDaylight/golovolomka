#include "coord.h"

#define MAX_NUM 1000

const coord2D_t coord2D_t::inf_neg = coord2D_t(-MAX_NUM, -MAX_NUM);
const coord2D_t coord2D_t::inf_pos = coord2D_t( MAX_NUM,  MAX_NUM);

const coord3D_t coord3D_t::inf_neg = coord3D_t(-MAX_NUM, -MAX_NUM, -MAX_NUM);
const coord3D_t coord3D_t::inf_pos = coord3D_t( MAX_NUM,  MAX_NUM,  MAX_NUM);


direction_t axis2direction(const axis_t& axis, const bool& inverted) 
{ 
	return (direction_t) (axis * 2 + (inverted ? 1 : 0));
}

axis_t direction2axis(const direction_t& direction, bool& inverted) 
{ 
	inverted = (direction % 2) == 1;
	return (axis_t) (direction / 2);
}


coord2D_t direction2delta_2D(const direction_t& direction) 
{ 
	static const coord2D_t deltas[direction_numof] = 
	{
		coord2D_t( 1,  0), // x
		coord2D_t(-1,  0), // x inv
		coord2D_t( 0,  1), // y
		coord2D_t( 0, -1), // y	inv
	};
	
	return deltas[direction];
}

coord3D_t direction2delta_3D(const direction_t& direction) 
{ 
	static const coord3D_t deltas[direction_numof] = 
	{
		coord3D_t( 1,  0,  0), // x
		coord3D_t(-1,  0,  0), // x inv
		coord3D_t( 0,  1,  0), // y
		coord3D_t( 0, -1,  0), // y	inv
		coord3D_t( 0,  0,  1), // z
		coord3D_t( 0,  0, -1)  // z inv
	};
	
	return deltas[direction];
}
