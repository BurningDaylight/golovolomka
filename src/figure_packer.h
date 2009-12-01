#ifndef FIGURE_PACKER_H_INCLUDED
#define FIGURE_PACKER_H_INCLUDED

#include "figure_placement_heuristics.h"

#include "figure_set_enumerator.h"
#include "figure_transformation_enumerator.h"

struct figure_t;
struct figure_rotator_t;

struct figure_packer_observer_t;



struct figure_packer_t
{
private:
	figure_packer_observer_t&			observer;

	figure_placement_heuristics_t figure_placement_heuristics;

	figure_set_enumerator_t::strategy_t							set_enum_strategy;
	figure_transformation_enumerator_t::strategy_t	transformation_enum_strategy;


	figure_t&											field;
	const figure_rotator_t*				figures;
	const int											quantity_of_figures;

	int														requested_index_of_decision;

	bool place_next_figure(
								const int												quantity_of_placed,
								const double										max_variants,
								const double										percent_processed_variants,
								const double										weight_of_current_iteration,
								const figure_set_enumerator_t&	figure_set_enumerator
							);
public:

	figure_packer_t(
				figure_t&																				field,
				const figure_rotator_t*													figures,
				int																							quantity,
				figure_packer_observer_t&												observer,
				figure_set_enumerator_t::strategy_t							set_enum_strategy,
				figure_transformation_enumerator_t::strategy_t	transformation_enum_strategy
			);

	virtual ~figure_packer_t();

	bool place_all_figures(
													int num_of_figures_to_place,
													int requested_index_of_decision = 1	);
};

#endif // FIGURE_PACKER_H_INCLUDED
