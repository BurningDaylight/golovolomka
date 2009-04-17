#ifndef TRANSFORMED_FIGURE_H_INCLUDED
#define TRANSFORMED_FIGURE_H_INCLUDED

#include "typedef.h"

#include "figure.h"


struct transformed_figure_t
{
private:
	static transformed_figure_t invalid_transformed_figure;

public:

	const figure_t&	figure;

	direction_t		direction;
	angle_t				angle;
	coord_t				position;
	
	transformed_figure_t() : 
		figure(figure_t::get_null_figure()), direction(direction_numof)
	{}
	
	transformed_figure_t(
		const figure_t& figure_, direction_t direction_, angle_t angle_, coord_t position_) :
		figure(figure_), direction(direction_), angle(angle_), position(position_)
	{}

	bool is_valid() const { return direction != direction_numof; }
	
	static const transformed_figure_t& get_invalid_object() { return invalid_transformed_figure;}
};

#endif // TRANSFORMED_FIGURE_H_INCLUDED
