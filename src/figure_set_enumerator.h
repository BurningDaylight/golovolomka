#ifndef FIGURE_SET_ENUMERATOR_H_INCLUDED
#define FIGURE_SET_ENUMERATOR_H_INCLUDED

#include "typedef.h"

#define USE_STATIC_PLACED_FIGURE_FLAGS

struct figure_set_enumerator_t
{

public:

	enum strategy_t
	{
		strategy_universal,
		strategy_root_node_must_be_only_the_first_figure
	};

private:

	strategy_t		strategy;
	
	const int			node_level;
	
	const int			last_placed_figure;
	
	const int			quantity;
	const int			num_of_figures_to_place;
	
	const int			quantity_of_placed;
	
	#ifdef USE_STATIC_PLACED_FIGURE_FLAGS
		static bool*	placed_figures;
	#else
		bool*	placed_figures;
	#endif

	mutable int		it;	
	mutable int		index;	
	
public:

	figure_set_enumerator_t(
														const int quantity, 
														const int num_of_figures_to_place,
														const strategy_t strategy_ 
													);
	figure_set_enumerator_t(
														const figure_set_enumerator_t&	previous,
														const int												last_placed_figure,
														const strategy_t strategy_ 
													);
	virtual ~figure_set_enumerator_t();
	
	int					get_quantity_of_iterations() const;
	
	int					get_interation_number() const { return it; }
	void				start_enumeration() const;
	int					next() const;
	bool				enumeration_is_ended() const;
};

#endif // FIGURE_SET_ENUMERATOR_H_INCLUDED
