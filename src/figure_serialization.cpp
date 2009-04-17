#include "figure.h"
#include "obj_writer.h"

#include "figure_serialization.h"


void write_figure_into_obj_file(const char* filename, const figure_t& figure)
{
	char figure_as_text[BIG_BUFFER] = "";
	figure.sprint(figure_as_text, "Figure", "#  ");
	
	int q;
	point_group_t* groups = figure.get_coords_of_all_subfigures(q);
	if(groups)
	{
		write_group_of_blocks_info_obj_file(filename, figure_as_text, groups, q);
		
		for(int i=0; i<q; i++)
			if(groups[i].coords)
			  delete groups[i].coords;
		delete[] groups;
	}
}
