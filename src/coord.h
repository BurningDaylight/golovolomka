#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

#include "typedef.h"

struct coord_t
{
private:
	static const coord_t inf_neg, inf_pos;
	
public:
	coord_value_t x, y, z;

	coord_t() : x(0), y(0), z(0) {}
	coord_t(coord_value_t _x, coord_value_t _y, coord_value_t _z) : x(_x), y(_y), z(_z) {}

	static const coord_t& get_inf_neg() { return inf_neg; }
	static const coord_t& get_inf_pos() { return inf_pos;	}

	void set_min(const coord_t& rh)	{	x = MIN(rh.x, x);	y = MIN(rh.y, y);	z = MIN(rh.z, z);	}
	void set_max(const coord_t& rh)	{	x = MAX(rh.x, x);	y = MAX(rh.y, y);	z = MAX(rh.z, z);	}
	void add(const coord_t& rh)	{	x += rh.x; y += rh.y; z += rh.z; }
	void sub(const coord_t& rh)	{	x -= rh.x; y -= rh.y; z -= rh.z; }
	void add_scalar(int v)	{	x += v; y += v; z += v; }
	
	bool any_coord_is_less(const coord_t& rh) const			{	return x<rh.x || y<rh.y || z<rh.z; }
	bool each_coord_is_less(const coord_t& rh) const		{	return x<rh.x && y<rh.y && z<rh.z; }
	bool any_coord_is_greater(const coord_t& rh) const  {	return x>rh.x || y>rh.y || z>rh.z; }
	bool each_coord_is_greater(const coord_t& rh) const {	return x>rh.x && y>rh.y && z>rh.z; }
	bool any_coord_is_greater_equal(const coord_t& rh) const  {	return x>=rh.x || y>=rh.y || z>=rh.z; }
	bool each_coord_is_greater_equal(const coord_t& rh) const {	return x>=rh.x && y>=rh.y && z>=rh.z; }
};


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

#endif // COORD_H_INCLUDED