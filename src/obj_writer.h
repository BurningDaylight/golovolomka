#ifndef OBJ_WRITER_H_INCLUDED
#define OBJ_WRITER_H_INCLUDED

struct point_group_t;

void write_group_of_blocks_info_obj_file(
																					const char*		  			filename,
																					const char*						header, 
																					const point_group_t*	groups, 
																					int										num				);

#endif // OBJ_WRITER_H_INCLUDED