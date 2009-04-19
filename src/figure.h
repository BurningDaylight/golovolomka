#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED

#include "typedef.h"

const unsigned int MAX_FIGURE_SIZE = 6;

#define FOR_ALL_FIGURES(num_figures, i)	for(char i=0; (i)<(num_figures); (i)++)

// TODO:	Generalize it!
//				We need figures of any dimension in order to implement projections!


struct figure_t 
{
private:	
	static const figure_t m_null_figure;
	
	coord_t		m_size;
	char			m_filler;
	
	DEF_CUBE( m_data, MAX_FIGURE_SIZE);
	
	mutable figure_t* m_rotated_figures[axis_numof][angle_numof];
	
public:	

	figure_t();
	figure_t(const coord_t size);
	figure_t(const char filler, const coord_t size, const char* data);
	figure_t(const char filler, const coord_t size, const coord_t* coords, int q);
	
	~figure_t();

	static const figure_t& get_null_figure() { return m_null_figure; }
	
	coord_t get_size() const { return m_size; }
	char		get_filler() const { return m_filler; }
	
	void copy(const figure_t& figure);
	
	bool has_solid_line(const coord_t& start, axis_t axis) const;
	//bool get_projection(axis_t axis) const;
	
	coord_t* get_coords_of_subfigure(int& size, char filler = 0) const; // 0 == any
	point_group_t* get_coords_of_all_subfigures(int& size) const;
	
	const figure_t& rotate_around_axis(axis_t axe, angle_t angle) const;

	bool try_place_figure(const figure_t& figure, const coord_t coords);
	bool remove_figure(const figure_t& figure, const coord_t coords);

	int get_movable_subfigure_index(direction_t& direction) const;

	void print(const char* caption) const;
	void sprint(char* s, const char* caption, const char* string_start) const;
};


#endif // FIGURE_H_INCLUDED