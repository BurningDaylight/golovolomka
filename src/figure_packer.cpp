#include <memory.h>

#include "figure.h"
#include "figure_rotator.h"

#include "figure_set_enumerator.h"
#include "figure_transformation_enumerator.h"

#include "transformed_figure.h"
#include "figure_packer.h"
#include "figure_packer_observer.h"


figure_packer_t::figure_packer_t(	
				figure_t&																				field_, 
				const figure_rotator_t*													figures_,
				int																							quantity_,
				figure_packer_observer_t&												observer_,
				figure_set_enumerator_t::strategy_t							set_enum_strategy_,
				figure_transformation_enumerator_t::strategy_t	transformation_enum_strategy_
																)
	: field(field_), figures(figures_),	figure_placement_heuristics(field_),
		quantity_of_figures(quantity_), observer(observer_),
		set_enum_strategy(set_enum_strategy_),
		transformation_enum_strategy(transformation_enum_strategy_)
{
}
									
									
figure_packer_t::~figure_packer_t()
{
}


bool figure_packer_t::place_next_figure(
							const int												quantity_of_placed,
							const double										max_variants,
							const double										processed_variant_portion,
							const double										weight_of_current_iteration,
							const figure_set_enumerator_t&	figure_set_enum										)
{
	observer.on_place_next_figure(
		quantity_of_placed,
		max_variants,
		processed_variant_portion,
		weight_of_current_iteration
	);
	
	if(figure_set_enum.get_quantity_of_iterations() == 0)
	{
		observer.on_found_solution( max_variants,  processed_variant_portion);
		return true;
	}
		
	int processed_figures = 0;

	//Open figure_set node
	figure_set_enum.start_enumeration();
	while(!figure_set_enum.enumeration_is_ended())
	{
		int placed_figure_index = figure_set_enum.next();
		ensure("placed_figure_index must be >= 0", placed_figure_index >= 0);
		
		figure_set_enumerator_t next_figure_set_enum(
																figure_set_enum, 
																placed_figure_index,
																set_enum_strategy
															);
		
		//Open figure_transformation node
		figure_transformation_enumerator_t transformation_enum(
																											quantity_of_placed, 
																											figures[placed_figure_index],
																											transformation_enum_strategy
																										);
		transformation_enum.start_enumeration();
		while(!transformation_enum.enumeration_is_ended())
		{
			transformed_figure_t transformed_figure = transformation_enum.next();
			
			observer.on_attempt_to_place_figure();
			if(figure_placement_heuristics.can_place_figure(
							transformed_figure.figure, transformed_figure.position))
			{
				if(field.try_place_figure(
							transformed_figure.figure, transformed_figure.position))
				{
					figure_placement_heuristics.on_figure_placement(
									transformed_figure.figure, transformed_figure.position);
									
					const double variants_per_figure = 
						transformation_enum.get_quantity_of_iterations();
														
					const double current_variants = 
						figure_set_enum.get_quantity_of_iterations() * variants_per_figure;

					const double next_max_variants = max_variants * current_variants;
					
					const double weight_of_next_iteration = 
						weight_of_current_iteration / current_variants;
					
					double processed_variants = 
						1.f * processed_figures * variants_per_figure 
						+ transformation_enum.get_interation_number() - 1;
					
					if( place_next_figure(
								quantity_of_placed + 1,
								next_max_variants,
								processed_variant_portion + processed_variants * weight_of_next_iteration,
								weight_of_next_iteration,
								next_figure_set_enum
						))	
					{
						if(observer.get_current_index_of_decision() >= requested_index_of_decision)
							return true;
					}
						
					figure_placement_heuristics.on_figure_removal(
									transformed_figure.figure, transformed_figure.position);
									
					field.remove_figure(transformed_figure.figure, transformed_figure.position);
				}
			}
		}
		processed_figures++;
	}
				
	ensure(
		"Invalid number of processed figures!",
		processed_figures == figure_set_enum.get_quantity_of_iterations()
	);
	
	return false;
}


bool figure_packer_t::place_all_figures(	
																					int num_of_figures_to_place, 
																					int requested_index_of_decision_
																				)
{
	observer.on_search_start();
	
	requested_index_of_decision	=	requested_index_of_decision_;
	
	figure_set_enumerator_t figure_set_enum(
																						quantity_of_figures, 
																						num_of_figures_to_place,
																						set_enum_strategy
																					);
	
	bool result = place_next_figure(0, 1, 0, 1, figure_set_enum);
	
	observer.on_search_end();

	return result;
}


