#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#define DEF_CUBE(name, max_size)	char name[(max_size)][(max_size)][(max_size)];

#define CUBE_ELEM(name, p)				(name)[(p).x][(p).y][(p).z]

#define FOR_EACH_CUBE_ELEM(p,size)	coord3D_t p;																\
																		for((p).z=0; (p).z<(size).z; (p).z++)			\
																			for((p).y=0; (p).y<(size).y; (p).y++)		\
																				for((p).x=0; (p).x<(size).x; (p).x++)	

#endif // CUBE_H_INCLUDED