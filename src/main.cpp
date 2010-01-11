#include <stdio.h>
#include <math.h>
#include <time.h>

#include "typedef.h"
#include "obj_writer.h"
#include "figure.h"
#include "figure_rotator.h"
#include "figure_packer.h"
#include "figure_packer_observer.h"
#include "figure_serialization.h"

//Just to set strategies
#include "figure_set_enumerator.h"
#include "figure_transformation_enumerator.h"


const figure_set_enumerator_t::strategy_t 
	default_figure_set_enum_strategy = 
			figure_set_enumerator_t::strategy_universal;
			//figure_set_enumerator_t::strategy_root_node_must_be_only_the_first_figure;

const figure_transformation_enumerator_t::strategy_t 
	default_figure_transformation_enum_strategy = 
			figure_transformation_enumerator_t::strategy_universal;
			//figure_transformation_enumerator_t::strategy_spec_brute_force;
			//figure_transformation_enumerator_t::strategy_spec_greedy;




//#define TIME_MEASUREMENT_MODE

#define USE_SORTED_ORDER_OF_FIGURES

//#define USE_DUMMY_FIGURES


const unsigned int FIELD_X = 6;
const unsigned int FIELD_Y = 6;
const unsigned int FIELD_Z = 6;


#define DEFINE_FIGURE(number, s) figure_rotator_t figure_##number( \
																		figure_t((number), coord3D_t(6, 2, 2), (s)));

//--------------------------- initial figures ---------------------------------

const unsigned int QUANTITY_OF_ORIGINAL_FIGURES = 6;

DEFINE_FIGURE(1,
								"######" 
								"######"
												//"######" 
												//"######")
												"#.##.#"
												"#....#")
DEFINE_FIGURE(2,
								"######" 
								"##..##"
												//"######" 
												//"######")
												"#..#.#"
												"#....#")
DEFINE_FIGURE(3,
								"######" 
								"######"
												"#...##"
												"#...##")
DEFINE_FIGURE(4,
								"######" 
								"######"
												"#....#"
												"#....#")
DEFINE_FIGURE(5,
								"######" 
								"##.###"
												"#....#"
												"#....#")
DEFINE_FIGURE(6,
								"######" 
								"##..##"
												"##..##"
												"#....#")
			
figure_rotator_t original_figures[QUANTITY_OF_ORIGINAL_FIGURES] = 
{
#ifdef USE_SORTED_ORDER_OF_FIGURES
	figure_1,
	figure_2,
	figure_3,
	figure_4,
	figure_5,
	figure_6,
#else
	figure_6,
	figure_5,
	figure_4,
	figure_3,
	figure_2,
	figure_1,
#endif
};


const unsigned int QUANTITY_OF_DUMMY_FIGURES = 2;
figure_rotator_t dummy_figures[QUANTITY_OF_DUMMY_FIGURES] = 
{
	figure_rotator_t(figure_t( 1, coord3D_t(1, 1, 1), "#")),
	figure_rotator_t(figure_t( 2, coord3D_t(1, 1, 1), "#")),
};

//------------------------------------------------------------
//												MAIN
//------------------------------------------------------------

int main(int argc, char* argv[])
{
	ENABLE_MEMORY_LEAK_CONTROL

	printf("---------------------------------------------------------\n");
	printf("     GOLOVOLOMKA SOLVER. (C) Dmitry Potapov, 2009-2010.  \n");
	printf("---------------------------------------------------------\n");
	
	FOR_ALL_FIGURES(QUANTITY_OF_ORIGINAL_FIGURES, i) 
	{
		char figure_as_text[BIG_BUFFER] = "";
		original_figures[i].get(direction_x, angle_none).sprint(figure_as_text, "", "");
		printf(figure_as_text);
	}
	printf("---------------------------------------------------------\n");
	
	#ifndef USE_DUMMY_FIGURES
		figure_rotator_t* figures = original_figures;	
		const int q = QUANTITY_OF_ORIGINAL_FIGURES;
	#else
		figure_rotator_t* figures = dummy_figures; 
		const int q = QUANTITY_OF_DUMMY_FIGURES;
	#endif
	
	printf("Solving puzzle...\n");
	
	clock_t time = 0;
	
#ifdef TIME_MEASUREMENT_MODE
	for(int i=0; i<100; i++)	
	{
#endif	

		//Field
		figure_t field(coord3D_t(FIELD_X, FIELD_Y, FIELD_Z));
		
		const int quantity_of_figures_to_use	= q;
		const int num_of_figures_to_place			= q;
		const int index_of_decision						= 1000000;
		
		figure_packer_observer_t figure_packer_observer(field);
		
		figure_packer_t figure_packer(
																		field, 
																		figures, 
																		quantity_of_figures_to_use,
																		figure_packer_observer,
																		default_figure_set_enum_strategy,
																		default_figure_transformation_enum_strategy
																	);
		
		clock_t time_beg = clock();
		bool result = figure_packer.place_all_figures(num_of_figures_to_place, index_of_decision);
		time += clock() - time_beg;
	
#ifdef TIME_MEASUREMENT_MODE
	}	
#endif
		
	printf("---------------------------------------------------------\n");
	printf("Total time in secs = %.06lf.\n", time / 1000.f);

	#ifndef TIME_MEASUREMENT_MODE
		if(!result)
		{
			printf("Can't find %d solutions, last found = %.0lf.\n", 
				index_of_decision,
				figure_packer_observer.get_current_index_of_decision()			
			);
			printf("<Press any key to quit>");
			WAIT_KEY_PRESSED
			return 0;
		}
		
		printf("Figures have been placed. Max variants ~ 2^%.0lf\n", 
						log(figure_packer_observer.get_max_variants()	)	);
						
		write_figure_into_obj_file("result.obj", field);
		printf("Resulting field has been saved.\n");
	#endif

	
	printf("<Press any key to quit>");
	WAIT_KEY_PRESSED
	return 0;
}

