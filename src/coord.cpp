#include "coord.h"

const coord_t coord_t::inf_neg = coord_t(-1000, -1000, -1000);
const coord_t coord_t::inf_pos = coord_t( 1000,  1000,  1000);

direction_t axis2direction(const axis_t& axis, const bool& inverted) 
{ 
	return (direction_t) (axis * 2 + (inverted ? 1 : 0));
}

axis_t direction2axis(const direction_t& direction, bool& inverted) 
{ 
	inverted = (direction % 2) == 1;
	return (axis_t) (direction / 2);
}

coord_t direction2delta(const direction_t& direction) 
{ 
	static const coord_t deltas[direction_numof] = 
	{
		coord_t( 1,  0,  0), // x
		coord_t(-1,  0,  0), // x inv
		coord_t( 0,  1,  0), // y
		coord_t( 0, -1,  0), // y	inv
		coord_t( 0,  0,  1), // z
		coord_t( 0,  0, -1)  // z inv
	};
	
	return deltas[direction];
}
