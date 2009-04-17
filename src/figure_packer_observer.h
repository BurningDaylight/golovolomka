#ifndef FIGURE_PACKER_OBSERVER_H_INCLUDED
#define FIGURE_PACKER_OBSERVER_H_INCLUDED

#include <time.h>

struct figure_t;

struct figure_packer_observer_t
{
	const figure_t& field;
	
	double	prev_processed_variant_portion;
	
	double	quantity_of_attempts_to_place_figure;
	double	current_index_of_pseudodecision;
	double	current_index_of_decision;
	
	double	max_variants;
	
	clock_t time_start, time_prev;
	
	figure_packer_observer_t(const figure_t& field_) : 
		field(field_),
		prev_processed_variant_portion(0),
		max_variants(0),
		current_index_of_pseudodecision(0),
		current_index_of_decision(0),
		time_start(0), time_prev(0)
	{
	}

	
	void on_search_start();
	void on_search_end();
																	
	void on_found_solution(
													const double	max_variants,
													const double	processed_variant_portion	);
																	
	void on_place_next_figure(
															const int			quantity_of_placed,
															const double	max_variants,
															const double	processed_variant_portion,
															const double	summ_weight_of_current_iteration	);
															
	void on_attempt_to_place_figure();
															
	double get_max_variants() const { return max_variants; }
	double get_current_index_of_decision() const { return current_index_of_decision; }
															
};


#endif // FIGURE_PACKER_OBSERVER_H_INCLUDED
