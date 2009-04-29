#ifndef FIGURE_TRANSFORMATION_ENUMERATOR_H_INCLUDED
#define FIGURE_TRANSFORMATION_ENUMERATOR_H_INCLUDED

#include "typedef.h"

#include "figure.h"


struct transformed_figure_t;
struct figure_rotator_t;



struct figure_transformation_enumerator_t
{

public:

	enum strategy_t
	{
		strategy_universal,
		strategy_spec_brute_force,
		strategy_spec_greedy
	};
	
	struct figure_transformation_operator_t
	{
		direction_t direction;
		angle_t			angle;
		coord3D_t			position;
		figure_transformation_operator_t(	direction_t direction_, angle_t angle_, coord3D_t position_) :
			direction(direction_),	angle(angle_), position(position_)
		{}
	};
	
private:

	strategy_t							strategy;
	
	const int								node_level;
	const figure_rotator_t&	figure;

	const figure_transformation_operator_t*	configurations;
	
	mutable int							it;	
	
public:

	figure_transformation_enumerator_t(
																			int node_level, 
																			const figure_rotator_t& figure_,
																			const strategy_t strategy_ 
																		);
	virtual ~figure_transformation_enumerator_t() {}
	
	int										get_quantity_of_iterations() const;
	
	int										get_interation_number() const { return it; }
	void									start_enumeration() const;
	transformed_figure_t	next() const;
	bool									enumeration_is_ended() const;
};

#endif // FIGURE_TRANSFORMATION_ENUMERATOR_H_INCLUDED
