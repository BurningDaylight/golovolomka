#include "figure.h"

#include <stdio.h>
#include <string.h>

const char SOLID = '#';
const char EMPTY = '.';

#define USE_UNIFICATED_BLOCK_PRINT


void rotate2D_hacked(coord_value_t& x, coord_value_t& y, coord_value_t cos_a, coord_value_t sin_a )
{
	coord_value_t x1 = x;
	coord_value_t y1 = y;

	x = x1 * cos_a - y1 * sin_a;
	y = x1 * sin_a + y1 * cos_a;
}


void rotate_around_axis(coord3D_t* coords, int q, axis_t axis, angle_t angle)
{
	static const coord_value_t coss[angle_numof] =
	{
		 1, // angle_none
		 0, // angle_90
		-1, // angle_180
		 0, // angle_270
	};

	static const coord_value_t sins[angle_numof] =
	{
		 0, // angle_none
		 1, // angle_90
		 0, // angle_180
		-1, // angle_270
	};

	coord_value_t cos_a = coss[angle];
	coord_value_t sin_a = sins[angle];

	for(int i = 0; i<q; i++)
	{
		switch(axis)
		{
			case axis_z:
					rotate2D_hacked(coords[i].x, coords[i].y, cos_a, sin_a);
				break;
			case axis_x:
					rotate2D_hacked(coords[i].y, coords[i].z, cos_a, sin_a);
				break;
			case axis_y:
					rotate2D_hacked(coords[i].x, coords[i].z, cos_a, sin_a);
				break;
			default:
				break;
		}
	}
}


BASIC_COORD determine_size_and_adjust_coords_to_positive_values(BASIC_COORD* coords, int q)
{
	BASIC_COORD min_coords = BASIC_COORD::get_inf_pos();
	BASIC_COORD max_coords = BASIC_COORD::get_inf_neg();

  //printf("determine start: %d %d %d, %d %d %d\n", min_coords.x, min_coords.y, min_coords.z, max_coords.x, max_coords.y, max_coords.z);

	for(int i = 0; i<q; i++)
	{
    //printf("%d, coord: %d %d %d\n", i, coords[i].x, coords[i].y, coords[i].z);
		min_coords.set_min(coords[i]);
		max_coords.set_max(coords[i]);
	}

	//printf("determine end: %d %d %d, %d %d %d\n", min_coords.x, min_coords.y, min_coords.z, max_coords.x, max_coords.y, max_coords.z);

	for(int i = 0; i<q; i++)
  {
		coords[i].sub(min_coords);
  }

	max_coords.sub(min_coords);
	max_coords.add_scalar(1);

	return max_coords;
}



//------------------------------- figure_t -----------------------------------------


const figure_t figure_t::m_null_figure;

figure_t::figure_t(const char filler, const BASIC_COORD size, const char* data)
{
	m_filler = filler;
	m_size = size;
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures));
	memset(m_data, 0, sizeof(m_data));

	FOR_EACH_BASIC_CUBE_ELEM(p,size)
		CUBE_3D_ELEM(m_data,p) =
								(data[p.x + (p.y + p.z * size.y) * size.x] == SOLID) ? m_filler : 0;
}


figure_t::figure_t(const char filler, const BASIC_COORD size, const BASIC_COORD *coords, int q)
{
	m_filler = filler;
	m_size = size;
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures));
	memset(m_data, 0, sizeof(m_data));

	for(int i = 0; i<q; i++) BASIC_CUBE_ELEM(m_data,coords[i]) = m_filler;
}


figure_t::figure_t() : m_size(0,0,0), m_filler(0)
{
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures));
	memset(m_data, 0, sizeof(m_data));
}


figure_t::figure_t(const BASIC_COORD size) : m_size(size), m_filler(0)
{
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures));
	memset(m_data, 0, sizeof(m_data));
}


figure_t::~figure_t()
{
	FOR_ALL_ENUM(axis)
		FOR_ALL_ENUM(angle)
			if(m_rotated_figures[axis][angle])
			{
				delete m_rotated_figures[axis][angle];
				m_rotated_figures[axis][angle] = 0;
			}
}


void figure_t::copy(const figure_t& figure)
{
	m_filler = figure.get_filler();
	m_size = figure.get_size();
	memcpy(m_data, figure.m_data, sizeof(m_data));
}


bool figure_t::try_place_figure(const figure_t& figure, const BASIC_COORD point)
{
	BASIC_COORD size = figure.get_size();

	FOR_EACH_BASIC_CUBE_ELEM(p1,size)
	{
		BASIC_COORD p_plus_offs(p1);
		p_plus_offs.add(point);
		if (BASIC_CUBE_ELEM(figure.m_data,p1) != 0 && BASIC_CUBE_ELEM(m_data,p_plus_offs) != 0)
			return false;
	}

	FOR_EACH_BASIC_CUBE_ELEM(p,size)
	{
		BASIC_COORD p_plus_offs(p);
		p_plus_offs.add(point);
		BASIC_CUBE_ELEM(m_data,p_plus_offs) += BASIC_CUBE_ELEM(figure.m_data,p);
	}

	m_filler = MAX(m_filler, figure.get_filler());

	return true;
}


bool figure_t::remove_figure(const figure_t& figure, const BASIC_COORD point)
{
	BASIC_COORD size = figure.get_size();
	BASIC_COORD zero_coord, max_coord(point);
	max_coord.add(size);

	if(	point.any_coord_is_less(zero_coord) || m_size.any_coord_is_less(max_coord) )
		return false;

	FOR_EACH_BASIC_CUBE_ELEM(p,size)
	{
		BASIC_COORD p_plus_offs(p);
		p_plus_offs.add(point);
		BASIC_CUBE_ELEM(m_data,p_plus_offs) -= BASIC_CUBE_ELEM(figure.m_data,p);
	}

	return true;
}


void figure_t::sprint(char* s, const char* caption, const char* string_start) const
{
	s[0] = 0;

	if(string_start)
		sprintf(s+strlen(s), "%s", string_start);
  sprintf(s+strlen(s), "%s\n", caption);

	BASIC_COORD p;
	for(p.z=0; p.z<m_size.z; p.z++)
		for(p.y=0; p.y<m_size.y; p.y++)
		{
			if(string_start)
				sprintf(s+strlen(s), "%s", string_start);
			for(int m=0; m<p.z*m_size.x; m++) sprintf(s+strlen(s), " ");
			for(p.x=0; p.x<m_size.x; p.x++)
				#ifdef USE_UNIFICATED_BLOCK_PRINT
					sprintf(s+strlen(s), "%c", (BASIC_CUBE_ELEM(m_data,p) !=0 ? SOLID : EMPTY));
				#else
					sprintf(s+strlen(s), "%c", '0' + BASIC_CUBE_ELEM(m_data,p));
				#endif
			sprintf(s+strlen(s), "\n");
		}
	sprintf(s+strlen(s),"\n");
}


int figure_t::get_movable_subfigure_index(direction_t& out_direction) const
{
	if(m_filler <= 0)
		return 0;

	typedef bool can_move_t [direction_numof];

	bool* encountered = dnew bool[m_filler+1];
	memset(encountered, 0, sizeof(bool) * m_filler);		// set all to false

	can_move_t* can_move = dnew can_move_t[m_filler+1];
	memset(can_move, 1, sizeof(can_move_t) * m_filler);	// set all to true

	BASIC_COORD zero_coord;

	FOR_EACH_BASIC_CUBE_ELEM(p,m_size)
	{
		char v = BASIC_CUBE_ELEM(m_data,p);
		if(v > 0)
			FOR_ALL_ENUM(direction)
			{
				BASIC_COORD c = direction2delta_3D(direction);
				c.add(p);

				encountered[v] = true;

				if( can_move[v][direction] &&
						c.each_coord_is_greater_equal(zero_coord) &&
						c.each_coord_is_less(m_size)									)
				{
					char v1 = BASIC_CUBE_ELEM(m_data,c);
					can_move[v][direction] &=  v1 == 0 || v1 == v;
				}
			}
	}

	for(int i=1; i<=m_filler; i++)	//Note: ignoring zero filler
		if(encountered[i])
			FOR_ALL_ENUM(direction)
				if(can_move[i][direction])
				{
					delete[] encountered;
					delete[] can_move;
					out_direction = direction;
					return i;
				}

	delete[] encountered;
	delete[] can_move;
	return 0;
}

bool figure_t::has_solid_line(const BASIC_COORD& start, axis_t axis) const
{
	BASIC_COORD d = direction2delta_3D(axis2direction(axis, false));

	for(	BASIC_COORD curr(start); curr.each_coord_is_less(m_size); curr.add(d) )
		if( BASIC_CUBE_ELEM(m_data,curr) == 0)
			return false;

	return true;
}

BASIC_COORD* figure_t::get_coords_of_subfigure(int& q, char filler) const
{
	q = 0;

	FOR_EACH_BASIC_CUBE_ELEM(p1,m_size)
		if(	filler > 0  && BASIC_CUBE_ELEM(m_data,p1) == filler ||
				filler == 0 && BASIC_CUBE_ELEM(m_data,p1) !=0						)
			q++;

	if(q==0)
	  return 0;

  //printf("q=%d\n", q);

	BASIC_COORD* vertices = dnew BASIC_COORD[q];

	int count = 0;
	FOR_EACH_BASIC_CUBE_ELEM(p,m_size)
		if(	filler > 0  && BASIC_CUBE_ELEM(m_data,p) == filler ||
				filler == 0 && BASIC_CUBE_ELEM(m_data,p) !=0						)
			vertices[count++] = p;

	return vertices;
}

point_group3D_t* figure_t::get_coords_of_all_subfigures(int& size) const
{
	if(m_filler <= 0)
		return 0;

	point_group3D_t* groups = dnew point_group3D_t[m_filler];

	size = 0;
	for( int i=1; i<=m_filler; i++)
	{
		int quantity;
		BASIC_COORD* coords = get_coords_of_subfigure(quantity, i);
		if(coords)
		{
			groups[size].coords		=	coords;
			groups[size].quantity	=	quantity;
			size++;
		}
	}

	return groups;
}


const figure_t& figure_t::rotate_around_axis(axis_t axis, angle_t angle) const
{
	if(m_rotated_figures[axis][angle])
		return *m_rotated_figures[axis][angle];

	int q;
	BASIC_COORD* coords = get_coords_of_subfigure(q);
	if(!coords)
		return m_null_figure;

	::rotate_around_axis(coords, q, axis, angle);

	BASIC_COORD new_size = determine_size_and_adjust_coords_to_positive_values(coords, q);

	m_rotated_figures[axis][angle] = dnew figure_t(m_filler, new_size, coords, q);
  //printf("new size: %d, %d, %d, %d %d %d\n", q, (int)axis, (int)angle, new_size.x, new_size.y, new_size.z);

	delete[] coords;

	return *m_rotated_figures[axis][angle];
}

