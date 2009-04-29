#include "figure_transformation_enumerator.h"
#include "figure_rotator.h"
#include "transformed_figure.h"

static const int num_points_per_face = 2;

static const coord3D_t points[direction_numof][num_points_per_face] = 
{
	{coord3D_t(0, 1, 2), coord3D_t(0, 3, 2)	}, // x
	{coord3D_t(0, 1, 2), coord3D_t(0, 3, 2)	}, // x inv 
	{coord3D_t(2, 0, 1), coord3D_t(2, 0, 3)	}, // y
	{coord3D_t(2, 0, 1), coord3D_t(2, 0, 3)	}, // y inv
	{coord3D_t(1, 2, 0), coord3D_t(3, 2, 0)	}, // z
	{coord3D_t(1, 2, 0), coord3D_t(3, 2, 0)	}  // z inv
};


#define FC(d,a,p) \
	figure_transformation_enumerator_t::figure_transformation_operator_t((d), (a), points[(d)][(p)])


//----------- Using same configuration set used for each figure --------------

const int size_of_transformation_set_unified = 
						direction_numof * angle_numof * num_points_per_face;

static const figure_transformation_enumerator_t::figure_transformation_operator_t 
										transformation_set_unified[size_of_transformation_set_unified] = 
{
  // direction, angle, point
  FC( direction_x, 			angle_none, 0 ),
  FC( direction_x, 			angle_90,   0 ),
  FC( direction_x, 			angle_180,  0 ),
  FC( direction_x, 			angle_270,  0 ),

  FC( direction_x_inv, 	angle_none, 0 ),
  FC( direction_x_inv, 	angle_90,   0 ),
  FC( direction_x_inv, 	angle_180,  0 ),
  FC( direction_x_inv, 	angle_270,  0 ),

  FC( direction_y, 			angle_none, 0 ),
  FC( direction_y, 			angle_90,   0 ),
  FC( direction_y, 			angle_180,  0 ),
  FC( direction_y, 			angle_270,  0 ),

  FC( direction_y_inv, 	angle_none, 0 ),
  FC( direction_y_inv, 	angle_90,   0 ),
  FC( direction_y_inv, 	angle_180,  0 ),
  FC( direction_y_inv, 	angle_270,  0 ),

  FC( direction_z, 			angle_none, 0 ),
  FC( direction_z, 			angle_90,   0 ),
  FC( direction_z, 			angle_180,  0 ),
  FC( direction_z, 			angle_270,  0 ),
  
  FC( direction_z_inv, 	angle_none, 0 ),
  FC( direction_z_inv, 	angle_90,   0 ),
  FC( direction_z_inv, 	angle_180,  0 ),
  FC( direction_z_inv, 	angle_270,  0 ),


  FC( direction_x, 			angle_none, 1 ),
  FC( direction_x, 			angle_90,   1 ),
  FC( direction_x, 			angle_180,  1 ),
  FC( direction_x, 			angle_270,  1 ),

  FC( direction_x_inv, 	angle_none, 1 ),
  FC( direction_x_inv, 	angle_90,   1 ),
  FC( direction_x_inv, 	angle_180,  1 ),
  FC( direction_x_inv, 	angle_270,  1 ),

  FC( direction_y, 			angle_none, 1 ),
  FC( direction_y, 			angle_90,   1 ),
  FC( direction_y, 			angle_180,  1 ),
  FC( direction_y, 			angle_270,  1 ),

  FC( direction_y_inv, 	angle_none, 1 ),
  FC( direction_y_inv, 	angle_90,   1 ),
  FC( direction_y_inv, 	angle_180,  1 ),
  FC( direction_y_inv, 	angle_270,  1 ),
  
  FC( direction_z, 			angle_none, 1 ),
  FC( direction_z, 			angle_90,   1 ),
  FC( direction_z, 			angle_180,  1 ),
  FC( direction_z, 			angle_270,  1 ),
  
  FC( direction_z_inv, 	angle_none, 1 ),
  FC( direction_z_inv, 	angle_90,   1 ),
  FC( direction_z_inv, 	angle_180,  1 ),
  FC( direction_z_inv, 	angle_270,  1 )
};


//--------- Using different configuration sets for each figure ---------------


static const int size_of_transformation_set_first = angle_numof;

static figure_transformation_enumerator_t::figure_transformation_operator_t
									transformation_set_x_1[size_of_transformation_set_first] = 
{
  FC( direction_x, 			angle_none, 0 ),
  FC( direction_x, 			angle_90,   0 ),
  FC( direction_x, 			angle_180,  0 ),
  FC( direction_x, 			angle_270,  0 ),
};

static const int size_of_transformation_set_other = 2 * angle_numof;

static figure_transformation_enumerator_t::figure_transformation_operator_t
									transformation_set_y_1[size_of_transformation_set_other] = 
{
  FC( direction_y, 			angle_none, 0 ),
  FC( direction_y, 			angle_90,   0 ),
  FC( direction_y, 			angle_180,  0 ),
  FC( direction_y, 			angle_270,  0 ),
  FC( direction_y_inv, 	angle_none, 0 ),
  FC( direction_y_inv, 	angle_90,   0 ),
  FC( direction_y_inv, 	angle_180,  0 ),
  FC( direction_y_inv, 	angle_270,  0 ),
};

static figure_transformation_enumerator_t::figure_transformation_operator_t
									transformation_set_z_1[size_of_transformation_set_other] = 
{
  FC( direction_z, 			angle_none, 0 ),
  FC( direction_z, 			angle_90,   0 ),
  FC( direction_z, 			angle_180,  0 ),
  FC( direction_z, 			angle_270,  0 ),
  FC( direction_z_inv, 	angle_none, 0 ),
  FC( direction_z_inv, 	angle_90,   0 ),
  FC( direction_z_inv, 	angle_180,  0 ),
  FC( direction_z_inv, 	angle_270,  0 ),
};

static figure_transformation_enumerator_t::figure_transformation_operator_t
									transformation_set_x_2[size_of_transformation_set_other] = 
{
  FC( direction_x, 			angle_none, 1 ),
  FC( direction_x, 			angle_90,   1 ),
  FC( direction_x, 			angle_180,  1 ),
  FC( direction_x, 			angle_270,  1 ),
  FC( direction_x_inv, 	angle_none, 1 ),
  FC( direction_x_inv, 	angle_90,   1 ),
  FC( direction_x_inv, 	angle_180,  1 ),
  FC( direction_x_inv, 	angle_270,  1 ),
};

static figure_transformation_enumerator_t::figure_transformation_operator_t 
									transformation_set_y_2[size_of_transformation_set_other] = 
{
  FC( direction_y, 			angle_none, 1 ),
  FC( direction_y, 			angle_90,   1 ),
  FC( direction_y, 			angle_180,  1 ),
  FC( direction_y, 			angle_270,  1 ),
  FC( direction_y_inv, 	angle_none, 1 ),
  FC( direction_y_inv, 	angle_90,   1 ),
  FC( direction_y_inv, 	angle_180,  1 ),
  FC( direction_y_inv, 	angle_270,  1 ),
};

static figure_transformation_enumerator_t::figure_transformation_operator_t
									transformation_set_z_2[size_of_transformation_set_other] = 
{
  FC( direction_z, 			angle_none, 1 ),
  FC( direction_z, 			angle_90,   1 ),
  FC( direction_z, 			angle_180,  1 ),
  FC( direction_z, 			angle_270,  1 ),
  
  FC( direction_z_inv, 	angle_none, 1 ),
  FC( direction_z_inv, 	angle_90,   1 ),
  FC( direction_z_inv, 	angle_180,  1 ),
  FC( direction_z_inv, 	angle_270,  1 )
};

#undef FC

#define MAX_FIGURES 6

static const int sizes_of_transformation_set[MAX_FIGURES] = 
{
	size_of_transformation_set_first,
	size_of_transformation_set_other,
	size_of_transformation_set_other,
	size_of_transformation_set_other,
	size_of_transformation_set_other,
	size_of_transformation_set_other,
};

static const figure_transformation_enumerator_t::figure_transformation_operator_t* 
																			transformation_sets_brute_force [MAX_FIGURES] = 
{
	transformation_set_x_1,
	transformation_set_x_2,
	transformation_set_y_1,
	transformation_set_y_2,
	transformation_set_z_1,
	transformation_set_z_2,
};

static const figure_transformation_enumerator_t::figure_transformation_operator_t* 
																			transformation_sets_greedy [MAX_FIGURES] = 
{
	transformation_set_x_1,
	transformation_set_y_1,
	transformation_set_z_1,
	transformation_set_x_2,
	transformation_set_y_2,
	transformation_set_z_2,
};




//----------------------- figure transformation enumerator ---------------------------------


figure_transformation_enumerator_t::figure_transformation_enumerator_t(
		const int node_level_, 
		const figure_rotator_t& figure_,
		const strategy_t strategy_ 
	) : 
	node_level(node_level_),	figure(figure_),	it(0),	strategy(strategy_)
{
	ensure( "Too much figure index", node_level < MAX_FIGURES);
	
	switch (strategy)
	{
		case strategy_spec_brute_force:
			configurations = transformation_sets_brute_force[node_level];
			break;
			
		case strategy_spec_greedy:
			configurations = transformation_sets_greedy[node_level];
			break;
			
		case strategy_universal:
		default:
			configurations = transformation_set_unified;
	}
}


int figure_transformation_enumerator_t::get_quantity_of_iterations() const
{ 
	switch (strategy)
	{
		case strategy_spec_brute_force:
		case strategy_spec_greedy:
			return sizes_of_transformation_set[node_level];
			break;
		
		case strategy_universal:
		default:
			return size_of_transformation_set_unified;
	}
}



void figure_transformation_enumerator_t::start_enumeration() const
{
	it=0;
}

transformed_figure_t figure_transformation_enumerator_t::next() const
{
	if(enumeration_is_ended())
		return transformed_figure_t::get_invalid_object();
		
	it++;
	
	return transformed_figure_t(
		figure.get(configurations[it-1].direction, configurations[it-1].angle),
		configurations[it-1].direction, 
		configurations[it-1].angle,
		configurations[it-1].position	
	);
}

bool figure_transformation_enumerator_t::enumeration_is_ended() const
{
	return it >= get_quantity_of_iterations();
}


