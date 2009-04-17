#ifndef FIGURE_SERIALIZATION_H_INCLUDED
#define FIGURE_SERIALIZATION_H_INCLUDED

struct figure_t;

void write_figure_into_obj_file(const char* filename, const figure_t& figure);

#endif // FIGURE_SERIALIZATION_H_INCLUDED
