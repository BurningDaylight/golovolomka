#include "figure.h"

#include <stdio.h>
#include <string.h>


#define USE_UNIFICATED_BLOCK_PRINT


void rotate2D_hacked(coord_value_t& x, coord_value_t& y, coord_value_t cos_a, coord_value_t sin_a )
{
	coord_value_t x1 = x + 1;
	coord_value_t y1 = y + 1;
	
	x = x1 * cos_a - y1 * sin_a;
	y = x1 * sin_a + y1 * cos_a;
}


void rotate_around_axis(coord_t* coords, int q, axis_t axis, angle_t angle)
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


coord_t determine_size_and_adjust_coords_to_positive_values(coord_t* coords, int q)
{
	coord_t min_coords = COORD_INF_POS;
	coord_t max_coords = COORD_INF_NEG;

	for(int i = 0; i<q; i++)
	{
		min_coords.set_min(coords[i]);
		max_coords.set_max(coords[i]);
	}
	
	for(int i = 0; i<q; i++)
		coords[i].sub(min_coords);
	
	max_coords.sub(min_coords);
	max_coords.add_scalar(1);
		
	return max_coords;
}



//------------------------------- figure_t -----------------------------------------


const figure_t figure_t::m_null_figure;

figure_t::figure_t(const char filler, const coord_t size, const char* data)
{
	m_filler = filler;
	m_size = size;
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures)); 
	memset(m_data, 0, sizeof(m_data));
	
	FOR_ALL_CUBE(x,y,z,size)
		m_data[x][y][z] =	(data[x + (y + z * size.y) * size.x] == SOLID) ? m_filler : 0; 
}


figure_t::figure_t(const char filler, const coord_t size, const coord_t *coords, int q)
{
	m_filler = filler;
	m_size = size;
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures)); 
	memset(m_data, 0, sizeof(m_data));
	
	for(int i = 0; i<q; i++)
		m_data[coords[i].x][coords[i].y][coords[i].z] = m_filler;
}


figure_t::figure_t() : m_size(0,0,0), m_filler(0) 
{
	memset(m_rotated_figures, 0, sizeof(m_rotated_figures)); 
	memset(m_data, 0, sizeof(m_data)); 
}


figure_t::figure_t(const coord_t size) : m_size(size), m_filler(0) 
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


bool figure_t::try_place_figure(const figure_t& figure, const coord_t point)
{
	coord_t size = figure.get_size();
	
	if(
		 point.x < 0 || m_size.x < point.x + size.x ||
		 point.y < 0 || m_size.y < point.y + size.y ||
		 point.z < 0 || m_size.z < point.z + size.z			)
		return false;

	FOR_ALL_CUBE(x,y,z,size)	
		if (figure.m_data[x][y][z]!=0 && m_data[x+point.x][y+point.y][z+point.z] != 0)
			return false;
				
	FOR_ALL_CUBE(x,y,z,size)	
		m_data[x+point.x][y+point.y][z+point.z] += figure.m_data[x][y][z];
				
	m_filler = MAX(m_filler, figure.get_filler());
				
	return true;
}


bool figure_t::remove_figure(const figure_t& figure, const coord_t point)
{
	coord_t size = figure.get_size();
	
	if(
		 point.x < 0 || m_size.x < point.x + size.x ||
		 point.y < 0 || m_size.y < point.y + size.y ||
		 point.z < 0 || m_size.z < point.z + size.z			)
		return false;
	
	FOR_ALL_CUBE(x,y,z,size)	
		m_data[x+point.x][y+point.y][z+point.z] -= figure.m_data[x][y][z];
				
	return true;
}


void figure_t::print(const char* caption) const
{
  printf("%s\n", caption);
 
	for(int z=0; z<m_size.z; z++)
		for(int y=0; y<m_size.y; y++)
		{
			for(int m=0; m<z*m_size.x; m++) printf(" ");
			for(int x=0; x<m_size.x; x++) 
				#ifdef USE_UNIFICATED_BLOCK_PRINT
					printf("%c", (m_data[x][y][z] !=0 ? SOLID : EMPTY));
				#else
					printf("%c", '0' + m_data[x][y][z]);
				#endif
			printf("\n");
		}
}


void figure_t::sprint(char* s, const char* caption, const char* string_start) const
{
	s[0] = 0;
	
	if(string_start)
		sprintf(s+strlen(s), "%s", string_start);
  sprintf(s+strlen(s), "%s\n", caption);
 
	for(int z=0; z<m_size.z; z++)
		for(int y=0; y<m_size.y; y++)
		{
			if(string_start)
				sprintf(s+strlen(s), "%s", string_start);
			for(int m=0; m<z*m_size.x; m++) sprintf(s+strlen(s), " ");
			for(int x=0; x<m_size.x; x++) 
				#ifdef USE_UNIFICATED_BLOCK_PRINT
					sprintf(s+strlen(s), "%c", (m_data[x][y][z] !=0 ? SOLID : EMPTY));
				#else
					sprintf(s+strlen(s), "%c", '0' + m_data[x][y][z]);
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

	FOR_ALL_CUBE(x,y,z,m_size)	
	{
		char v = m_data[x][y][z];
		if(v > 0)
			FOR_ALL_ENUM(direction)
			{
				coord_t c = direction2delta(direction); 
				c.x += x; c.y += y; c.z += z;
				
				encountered[v] = true;
				
				if( can_move[v][direction] &&
						c.x >= 0 && c.x < m_size.x && 
						c.y >= 0 && c.y < m_size.y &&
						c.z >= 0 && c.z < m_size.z		)
				{
					char v1 = m_data[c.x][c.y][c.z];
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

bool figure_t::has_solid_line(const coord_t& start, axis_t axis) const
{
	coord_t d = direction2delta(axis2direction(axis, false));
	
	for(	coord_t curr(start);
				curr.x < m_size.x && curr.y < m_size.y && curr.z < m_size.z;
				curr.x += d.x, curr.y += d.y, curr.z += d.z
			)
		if( m_data[curr.x][curr.y][curr.z] == 0)
			return false;
			
	return true;
}

coord_t* figure_t::get_coords_of_subfigure(int& q, char filler) const
{
	q = 0;
	
	FOR_ALL_CUBE(x,y,z,m_size)	
		if(	filler>0 && m_data[x][y][z] == filler || filler == 0 && m_data[x][y][z] !=0 )
			q++;
					
	if(q==0)
	  return 0;
					
	coord_t* vertices = dnew coord_t[q];
			
	int count = 0;
	FOR_ALL_CUBE(x,y,z,m_size)	
		if(	filler>0 && m_data[x][y][z] == filler || filler == 0 && m_data[x][y][z] !=0 )
			vertices[count++] = coord_t(x, y, z);
			
	return vertices;
}

point_group_t* figure_t::get_coords_of_all_subfigures(int& size) const
{
	if(m_filler <= 0)
		return 0;
		
	point_group_t* groups = dnew point_group_t[m_filler];
	
	size = 0;
	for( int i=1; i<=m_filler; i++)
	{
		int quantity;
		coord_t* coords = get_coords_of_subfigure(quantity, i);
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
	coord_t* coords = get_coords_of_subfigure(q);
	if(!coords)
		return m_null_figure;
		
	::rotate_around_axis(coords, q, axis, angle);
	
	coord_t new_size = determine_size_and_adjust_coords_to_positive_values(coords, q);
	
	m_rotated_figures[axis][angle] = dnew figure_t(m_filler, new_size, coords, q);
	
	delete[] coords;
	
	return *m_rotated_figures[axis][angle];
}

