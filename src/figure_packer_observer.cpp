#include <stdio.h>
#include <math.h>

#include "typedef.h"

#include "figure.h"
#include "figure_packer_observer.h"

#define DT  1000


void figure_packer_observer_t::on_search_start()
{
	prev_processed_variant_portion = 0.f;
	
	quantity_of_attempts_to_place_figure = 0;
	
	current_index_of_pseudodecision = 0;
	current_index_of_decision = 0;
	
	max_variants = 0;
	
	time_start = time_prev = clock();
}


void figure_packer_observer_t::on_place_next_figure(
																					const int			/*quantity_of_placed*/,
																					const double	/*max_variants*/,
																					const double	processed_variant_portion,
																					const double	/*summ_weight_of_current_iteration*/
																				)
{
	ensure(
		"Decrease of completion percent",
		processed_variant_portion >= prev_processed_variant_portion
	);
	prev_processed_variant_portion = processed_variant_portion;
}


void figure_packer_observer_t::on_attempt_to_place_figure()
{
	quantity_of_attempts_to_place_figure++;
}

											
void figure_packer_observer_t::on_found_solution(
																						const double	max_variants_,
																						const double	processed_variant_portion	
																					)
{
	prev_processed_variant_portion = processed_variant_portion;
	
	current_index_of_pseudodecision++;
	
	direction_t direction;
	int movable_figure_index = field.get_movable_subfigure_index(direction);
	
	if(movable_figure_index > 0)
		current_index_of_decision++;
	
	max_variants = max_variants_;
	
	
	clock_t curr_time = clock();
	
	if(curr_time - time_prev > DT)
	{
		time_prev = curr_time;
		
		printf(	"%2.2lf%%, Decisions: %.0lf(%.0lf) N = %.0lf, Move = [%d, %d], max = 2^%.0lf, secs left = %.0lf/%.0lf\n",
						 100 * processed_variant_portion,
						 current_index_of_decision, current_index_of_pseudodecision,
						 quantity_of_attempts_to_place_figure,
						 movable_figure_index, direction, 
						 log(max_variants),
						 1.f / 1000 * (curr_time - time_start) * (1 / processed_variant_portion - 1),
						 1.f / 1000 * (curr_time - time_start) * 1 / processed_variant_portion
					);
	}
}


void figure_packer_observer_t::on_search_end()
{
	printf(	"End of search. Decisions: %.0lf(%.0lf) N: %.0lf. Max variants: 2^%.0lf\n",
					 current_index_of_decision, current_index_of_pseudodecision,
					 quantity_of_attempts_to_place_figure,
					 log(max_variants)
				);
}



