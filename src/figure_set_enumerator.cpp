#include <memory.h>
#include <stdlib.h>

#include "figure_set_enumerator.h"

#ifdef USE_STATIC_PLACED_FIGURE_FLAGS
	bool*	figure_set_enumerator_t::placed_figures = 0;
#endif


figure_set_enumerator_t::figure_set_enumerator_t(
															const figure_set_enumerator_t&	previous,
															const int												last_placed_figure_,
															const strategy_t								strategy_ 
														) :
	node_level(previous.node_level + 1),
	quantity(previous.quantity), 
	num_of_figures_to_place(previous.num_of_figures_to_place),
	quantity_of_placed(previous.quantity_of_placed + 1),
	last_placed_figure(last_placed_figure_),
	it(0), index(0), 	strategy(strategy_)
{
	#ifndef USE_STATIC_PLACED_FIGURE_FLAGS
		placed_figures = dnew bool[quantity];
		memcpy(placed_figures, previous.placed_figures, sizeof(bool) * quantity);
	#endif
	placed_figures[last_placed_figure] = true;
}

figure_set_enumerator_t::figure_set_enumerator_t(
																					const int					quantity_, 
																					const int					num_of_figures_to_place_,
																					const	strategy_t	strategy_ 
																			) :
	node_level(0),
	quantity(quantity_), 
	num_of_figures_to_place(num_of_figures_to_place_),
	quantity_of_placed(0),
	last_placed_figure(-1),
	it(0), index(0), 	strategy(strategy_)
{
	placed_figures = dnew bool[quantity];
	memset(placed_figures, 0, sizeof(bool) * quantity);
}

figure_set_enumerator_t::~figure_set_enumerator_t()
{ 
	#ifdef USE_STATIC_PLACED_FIGURE_FLAGS	
		if(last_placed_figure >= 0)
			placed_figures[last_placed_figure] = false;
			
		if(placed_figures && node_level == 0) 
		{ 
			delete[] placed_figures; 
			placed_figures = 0; 
		}
	#else
		if(placed_figures) 
			delete[] placed_figures; 
	#endif
}



int figure_set_enumerator_t::get_quantity_of_iterations() const 
{ 
	if(strategy == strategy_root_node_must_be_only_the_first_figure && node_level == 0)
	return 1;
	
	return num_of_figures_to_place - quantity_of_placed; 
}

void figure_set_enumerator_t::start_enumeration() const
{
	it = 0;
	index = 0;
}

int figure_set_enumerator_t::next() const
{
	if(it >= get_quantity_of_iterations())
		return -1;
		
	for(; index < quantity && placed_figures[index]; index++ );

	if(index >= quantity)
	{
		it = get_quantity_of_iterations();
		return -1;
	}

	it++;
	index++;
	return index - 1;
}

bool figure_set_enumerator_t::enumeration_is_ended() const
{
	return it >= get_quantity_of_iterations();
}


