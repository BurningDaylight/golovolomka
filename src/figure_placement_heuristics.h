#ifndef FIGURE_PLACEMENT_HEURISTICS_H_INCLUDED
#define FIGURE_PLACEMENT_HEURISTICS_H_INCLUDED

#include "figure.h"

// TODO: Use projections on each edge of field!


struct figure_placement_heuristics_t
{
private:
	const figure_t&	field;
	
	DEF_BASIC_CUBE( solid_lines, MAX_FIGURE_SIZE);

public:

	figure_placement_heuristics_t(const figure_t&	field);

	bool can_place_figure(const figure_t& figure, const BASIC_COORD coords) const;
	void on_figure_placement(const figure_t& figure, const BASIC_COORD coords);
	void on_figure_removal(const figure_t& figure, const BASIC_COORD coords);
};


#endif // FIGURE_PLACEMENT_HEURISTICS_H_INCLUDED