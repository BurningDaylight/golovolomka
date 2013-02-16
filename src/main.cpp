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
			//figure_set_enumerator_t::strategy_universal;
			figure_set_enumerator_t::strategy_root_node_must_be_only_the_first_figure;

const figure_transformation_enumerator_t::strategy_t
	default_figure_transformation_enum_strategy =
			//figure_transformation_enumerator_t::strategy_universal;
			figure_transformation_enumerator_t::strategy_spec_brute_force;
			//figure_transformation_enumerator_t::strategy_spec_greedy;




//#define TIME_MEASUREMENT_MODE

#define USE_SORTED_ORDER_OF_FIGURES

const unsigned int FIELD_X = 6;
const unsigned int FIELD_Y = 6;
const unsigned int FIELD_Z = 6;


#define BURNING_DAYLIGHT_1  1
#define GRIGORUSHA_1        2
#define GRIGORUSHA_2        3

#define PUZZLE_TYPE BURNING_DAYLIGHT_1


const unsigned int QUANTITY_OF_ORIGINAL_FIGURES = 6;


//-----------------------------------------------------------------------------


#define DEFINE_FIGURE(number, s) figure_t figure_##number((number), coord3D_t(6, 2, 2), (s));


//--------------------------- initial figures ---------------------------------


figure_rotator_t* init_figures(int& q, const bool use_dummy_figures = false)
{
  if (use_dummy_figures)
  {
    const unsigned int QUANTITY_OF_DUMMY_FIGURES = 2;
    figure_rotator_t* dummy_figures = dnew figure_rotator_t[QUANTITY_OF_DUMMY_FIGURES];

    dummy_figures[0].init(figure_t( 1, coord3D_t(1, 1, 1), "#"));
    dummy_figures[1].init(figure_t( 2, coord3D_t(1, 1, 1), "#"));

    q = QUANTITY_OF_DUMMY_FIGURES;
    return dummy_figures;
  }

  #if PUZZLE_TYPE == BURNING_DAYLIGHT_1

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

  #elif PUZZLE_TYPE == GRIGORUSHA_1

  // First puzzle from http://grigr.narod.ru/another/treepuzzle.htm

  DEFINE_FIGURE(1,
                  "######"
                  "###~##"
                          "#~#~~#"
                          "#~~~~#")
  DEFINE_FIGURE(2,
                  "######"
                  "###~~#"
                          "##~###"
                          "##~~##")
  DEFINE_FIGURE(3,
                  "######"
                  "#~#~~#"
                          "##~~##"
                          "#~~~##")
  DEFINE_FIGURE(4,
                  "######"
                  "#~~#~#"
                          "##~~##"
                          "##~~##")
  DEFINE_FIGURE(5,
                  "######"
                  "###~##"
                          "#~~~~#"
                          "#~~~~#")
  DEFINE_FIGURE(6,
                  "##~~##"
                  "######"
                          "##~~##"
                          "#~~~~#")

  #elif PUZZLE_TYPE == GRIGORUSHA_2

  // Second puzzle from http://grigr.narod.ru/another/treepuzzle.htm
  DEFINE_FIGURE(1,
                  "######"
                  "###~##"
                          "#~~~~#"
                          "#~#~~#")
  DEFINE_FIGURE(2,
                  "##~~##"
                  "######"
                          "##~~##"
                          "#~~~~#")
  DEFINE_FIGURE(3,
                  "######"
                  "##~###"
                          "##~###"
                          "#~~~##")
  DEFINE_FIGURE(4,
                  "######"
                  "##~~##"
                          "#~~#~#"
                          "#~~~~#")
  DEFINE_FIGURE(5,
                  "######"
                  "#~~~~#"
                          "##~~##"
                          "###~##")
  DEFINE_FIGURE(6,
                  "######"
                  "###~##"
                          "#~~~~#"
                          "#~~~~#")

  #endif


  figure_rotator_t* figures = dnew figure_rotator_t[QUANTITY_OF_ORIGINAL_FIGURES];

  #ifdef USE_SORTED_ORDER_OF_FIGURES
    figures[0].init(figure_1);
    figures[1].init(figure_2);
    figures[2].init(figure_3);
    figures[3].init(figure_4);
    figures[4].init(figure_5);
    figures[5].init(figure_6);
  #else
    figures[0].init(figure_6);
    figures[1].init(figure_5);
    figures[2].init(figure_4);
    figures[3].init(figure_3);
    figures[4].init(figure_2);
    figures[5].init(figure_1);
  #endif


  q = QUANTITY_OF_ORIGINAL_FIGURES;
  return figures;
}


void delete_figures(figure_rotator_t* figures)
{
  delete[] figures;
}


//------------------------------------------------------------
//												MAIN
//------------------------------------------------------------

int main(int argc, char* argv[])
{
	ENABLE_MEMORY_LEAK_CONTROL

	printf("---------------------------------------------------------\n");
	printf("     GOLOVOLOMKA SOLVER. (C) Dmitry Potapov, 2009-2013.  \n");
	printf("---------------------------------------------------------\n");

  int q = 0;
  figure_rotator_t* figures = init_figures(q, false);

	FOR_ALL_FIGURES(q, i)
	{
		char figure_as_text[BIG_BUFFER] = "";
		figures[i].get(direction_x, angle_none).sprint(figure_as_text, "", "");
		printf("%s", figure_as_text);
	}
	printf("---------------------------------------------------------\n");

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

      delete_figures(figures);

			printf("<Press any key to quit>");
			WAIT_KEY_PRESSED
			return 0;
		}

		printf("Figures have been placed. Max variants ~ 2^%.0lf\n",
						log(figure_packer_observer.get_max_variants()	)	);

		write_figure_into_obj_file("result.obj", field);
		printf("Resulting field has been saved.\n");
	#endif

  delete_figures(figures);

	printf("<Press 'Enter' key to quit>");
	WAIT_KEY_PRESSED
	return 0;
}

