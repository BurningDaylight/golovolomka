#include <memory.h>

#include "figure_placement_heuristics.h"

figure_placement_heuristics_t::figure_placement_heuristics_t(const figure_t& field_) 
	: field(field_)
{
	memset(solid_lines, 0, sizeof(solid_lines));
}

bool figure_placement_heuristics_t::can_place_figure(
													const figure_t& figure, const BASIC_COORD ins_pos) const
{
	//BASIC_COORD field_size = field.get_size();
	//BASIC_COORD figure_size = figure.get_size();

	//if(ins_pos.x <= 0 && figure_size.x + ins_pos.x >= field_size.x)
	//{
	//	coord_value_t max_y = MIN(figure_size.y, field_size.y - ins_pos.y);
	//	coord_value_t max_z = MIN(figure_size.z, field_size.z - ins_pos.z);
	//	
	//	coord_value_t x = 0;
	//	for (coord_value_t y=0; y<max_y; y++ )
	//		for (coord_value_t z=0; z<max_z; z++ )
	//			if (	solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] && 
	//						figure.has_solid_line(BASIC_COORD(x,y,z),axis_x) )
	//				return false;
	//}
	//
	//if(ins_pos.y <= 0 && figure_size.y + ins_pos.y >= field_size.y)
	//{
	//	coord_value_t max_x = MIN(figure_size.x, field_size.x - ins_pos.x);
	//	coord_value_t max_z = MIN(figure_size.z, field_size.z - ins_pos.z);
	//	
	//	coord_value_t y = 0;
	//	for (coord_value_t x=0; x<max_x; x++ )
	//		for (coord_value_t z=0; z<max_z; z++ )
	//			if (	solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] && 
	//						figure.has_solid_line(BASIC_COORD(x,y,z),axis_x) )
	//				return false;
	//}
	//
	//if(ins_pos.z <= 0 && figure_size.z + ins_pos.z >= field_size.z)
	//{
	//	coord_value_t max_x = MIN(figure_size.x, field_size.x - ins_pos.x);
	//	coord_value_t max_y = MIN(figure_size.y, field_size.y - ins_pos.y);
	//	
	//	coord_value_t z = 0;
	//	for (coord_value_t x=0; x<max_x; x++ )
	//		for (coord_value_t y=0; y<max_y; y++ )
	//			if (	solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] && 
	//						figure.has_solid_line(BASIC_COORD(x,y,z),axis_x) )
	//				return false;
	//}
	//
	//
	return true;
}

void figure_placement_heuristics_t::on_figure_placement(
															const figure_t& figure, const BASIC_COORD ins_pos)
{
	//BASIC_COORD field_size = field.get_size();
	//BASIC_COORD figure_size = figure.get_size();

	//if(ins_pos.x <= 0 && figure_size.x + ins_pos.x >= field_size.x)
	//{
	//	coord_value_t max_y = MIN(figure_size.y, field_size.y - ins_pos.y);
	//	coord_value_t max_z = MIN(figure_size.z, field_size.z - ins_pos.z);
	//	
	//	coord_value_t x = 0;
	//	for (coord_value_t y=0; y<max_y; y++ )
	//		for (coord_value_t z=0; z<max_z; z++ )
	//			if (figure.has_solid_line(BASIC_COORD(x,y,z),axis_x))
	//				solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] ^= 
	//																													1 << figure.get_filler();
	//}
	//
	//if(ins_pos.y <= 0 && figure_size.y + ins_pos.y >= field_size.y)
	//{
	//	coord_value_t max_x = MIN(figure_size.x, field_size.x - ins_pos.x);
	//	coord_value_t max_z = MIN(figure_size.z, field_size.z - ins_pos.z);
	//	
	//	coord_value_t y = 0;
	//	for (coord_value_t x=0; x<max_x; x++ )
	//		for (coord_value_t z=0; z<max_z; z++ )
	//			if (figure.has_solid_line(BASIC_COORD(x,y,z),axis_x))
	//				solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] ^= 
	//																													1 << figure.get_filler();
	//}
	//
	//if(ins_pos.z <= 0 && figure_size.z + ins_pos.z >= field_size.z)
	//{
	//	coord_value_t max_x = MIN(figure_size.x, field_size.x - ins_pos.x);
	//	coord_value_t max_y = MIN(figure_size.y, field_size.y - ins_pos.y);
	//	
	//	coord_value_t z = 0;
	//	for (coord_value_t x=0; x<max_x; x++ )
	//		for (coord_value_t y=0; y<max_y; y++ )
	//			if (figure.has_solid_line(BASIC_COORD(x,y,z),axis_x))
	//				solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] ^= 
	//																													1 << figure.get_filler();
	//}
}


void figure_placement_heuristics_t::on_figure_removal(
															const figure_t& figure, const BASIC_COORD ins_pos)
{
	//BASIC_COORD field_size = field.get_size();
	//BASIC_COORD figure_size = figure.get_size();

	//if(ins_pos.x <= 0 && figure_size.x + ins_pos.x >= field_size.x)
	//{
	//	coord_value_t max_y = MIN(figure_size.y, field_size.y - ins_pos.y);
	//	coord_value_t max_z = MIN(figure_size.z, field_size.z - ins_pos.z);
	//	
	//	coord_value_t x = 0;
	//	for (coord_value_t y=0; y<max_y; y++ )
	//		for (coord_value_t z=0; z<max_z; z++ )
	//			if (figure.has_solid_line(BASIC_COORD(x,y,z),axis_x))
	//				solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] ^= 
	//																													1 << figure.get_filler();
	//}
	//
	//if(ins_pos.y <= 0 && figure_size.y + ins_pos.y >= field_size.y)
	//{
	//	coord_value_t max_x = MIN(figure_size.x, field_size.x - ins_pos.x);
	//	coord_value_t max_z = MIN(figure_size.z, field_size.z - ins_pos.z);
	//	
	//	coord_value_t y = 0;
	//	for (coord_value_t x=0; x<max_x; x++ )
	//		for (coord_value_t z=0; z<max_z; z++ )
	//			if (figure.has_solid_line(BASIC_COORD(x,y,z),axis_x))
	//				solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] ^= 
	//																													1 << figure.get_filler();
	//}
	//
	//if(ins_pos.z <= 0 && figure_size.z + ins_pos.z >= field_size.z)
	//{
	//	coord_value_t max_x = MIN(figure_size.x, field_size.x - ins_pos.x);
	//	coord_value_t max_y = MIN(figure_size.y, field_size.y - ins_pos.y);
	//	
	//	coord_value_t z = 0;
	//	for (coord_value_t x=0; x<max_x; x++ )
	//		for (coord_value_t y=0; y<max_y; y++ )
	//			if (figure.has_solid_line(BASIC_COORD(x,y,z),axis_x))
	//				solid_lines[ins_pos.x + x][ins_pos.y + y][ins_pos.z + z] ^= 
	//																													1 << figure.get_filler();
	//}
}

