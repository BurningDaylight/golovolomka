#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED

#include "coord.h"
#include "cube.h"

const unsigned int MAX_FIGURE_SIZE = 6;

#define FOR_ALL_FIGURES(num_figures, i)	for(char i=0; (i)<(num_figures); (i)++)

// TODO:	Generalize it!
//				We need figures of any dimension in order to implement projections!

// Note: Settings for 3D solving only!
#define BASIC_COORD								coord3D_t
#define BASIC_CUBE_ELEM						CUBE_3D_ELEM
#define DEF_BASIC_CUBE						DEF_CUBE_3D
#define FOR_EACH_BASIC_CUBE_ELEM	FOR_EACH_CUBE_3D_ELEM


struct figure_t 
{
private:	
	static const figure_t m_null_figure;
	
	BASIC_COORD	m_size;
	char				m_filler;
	
	DEF_CUBE_3D( m_data, MAX_FIGURE_SIZE);
	
	mutable figure_t* m_rotated_figures[axis_numof][angle_numof];
	
public:	

	figure_t();
	figure_t(const BASIC_COORD size);
	figure_t(const char filler, const BASIC_COORD size, const char* data);
	figure_t(const char filler, const BASIC_COORD size, const BASIC_COORD* coords, int q);
	
	~figure_t();

	static const figure_t& get_null_figure() { return m_null_figure; }
	
	BASIC_COORD get_size() const { return m_size; }
	char		get_filler() const { return m_filler; }
	
	void copy(const figure_t& figure);
	
	bool has_solid_line(const BASIC_COORD& start, axis_t axis) const;
	//bool get_projection(axis_t axis) const;
	
	BASIC_COORD* get_coords_of_subfigure(int& size, char filler = 0) const; // 0 == any
	point_group3D_t* get_coords_of_all_subfigures(int& size) const;
	
	const figure_t& rotate_around_axis(axis_t axe, angle_t angle) const;

	bool try_place_figure(const figure_t& figure, const BASIC_COORD coords);
	bool remove_figure(const figure_t& figure, const BASIC_COORD coords);

	int get_movable_subfigure_index(direction_t& direction) const;

	void sprint(char* s, const char* caption, const char* string_start) const;
};


#endif // FIGURE_H_INCLUDED