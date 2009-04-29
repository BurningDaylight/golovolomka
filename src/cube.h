#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED


#define DEF_CUBE_2D(name, max_size)	char name[(max_size)][(max_size)];

#define CUBE_2D_ELEM(name, p)				(name)[(p).x][(p).y]

#define FOR_EACH_CUBE_2D_ELEM(p,size)	coord2D_t p;														\
																			for((p).x=0; (p).x<(size).x; (p).x++)		\
																				for((p).y=0; (p).y<(size).y; (p).y++)	



#define DEF_CUBE_3D(name, max_size)	char name[(max_size)][(max_size)][(max_size)];

#define CUBE_3D_ELEM(name, p)				(name)[(p).x][(p).y][(p).z]

#define FOR_EACH_CUBE_3D_ELEM(p,size)	coord3D_t p;														\
																		for((p).x=0; (p).x<(size).x; (p).x++)			\
																			for((p).y=0; (p).y<(size).y; (p).y++)		\
																				for((p).z=0; (p).z<(size).z; (p).z++)

#endif // CUBE_H_INCLUDED