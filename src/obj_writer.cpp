#include <stdio.h>
#include <string.h>

#include "typedef.h"
#include "figure.h"
#include "obj_writer.h"


const float size = 0.1f;

void write_vertex(char* vs, float x, float y, float z)
{
	sprintf(vs + strlen(vs), "v  %.1lf  %.1lf  %.1lf\n", x, y, z);
}

void write_coord3D(char* vs, const coord3D_t& coords)
{
	const coord3D_t c = coords;
	
	const float DX = -size * 3;
	const float DY = -size * 1;
	const float DZ = -size * 1;
	
	const float x = c.x * size + DX;
	const float y = c.y * size + DY;
	const float z = c.z * size + DZ;
	
	write_vertex(vs, x, y, z);
	write_vertex(vs, x, y, z + size);
	write_vertex(vs, x, y + size, z);
	write_vertex(vs, x, y + size, z + size);
	write_vertex(vs, x + size, y, z);
	write_vertex(vs, x + size, y, z + size);
	write_vertex(vs, x + size, y + size, z);
	write_vertex(vs, x + size, y + size, z + size);
}


void write_blocks_info_obj_file(
																	char*						filename, 
																	const char*			header, 
																	const coord3D_t*	coords, 
																	int							num
																)
{
	FILE* fp = fopen(filename, "wt+");
	if(!fp)
		return;
		
	//write header
	
	if(header)
		fprintf(fp, "%s", header);
		
	fprintf(fp, "mtllib face_1.mtl\n");
	fprintf(fp, "# object shape\n");
	fprintf(fp, "g shape\n");
	fprintf(fp, "\n");
	
	//write vertices
	
	char vertices[BIG_BUFFER] = "";
	for(int i=0; i<num; i++)
		write_coord3D(vertices, coords[i]);
	fprintf(fp, "%s", vertices);
	
	//write normals

	fprintf(fp, "\n");
	fprintf(fp, "vn  0.0  0.0  1.0\n");
	fprintf(fp, "vn  0.0  0.0 -1.0\n");
	fprintf(fp, "vn  0.0  1.0  0.0\n");
	fprintf(fp, "vn  0.0 -1.0  0.0\n");
	fprintf(fp, "vn  1.0  0.0  0.0\n");
	fprintf(fp, "vn -1.0  0.0  0.0\n");
	fprintf(fp, "\n");
	
	//write normal for each vertex
	
	fprintf(fp, "usemtl outside\n\n");
	
	for(int i=0; i<num; i++)
	{
		fprintf(fp, "f  %d//2  %d//2  %d//2\n", i*8+1,  i*8+7,  i*8+5 );
		fprintf(fp, "f  %d//2  %d//2  %d//2\n", i*8+1,  i*8+3,  i*8+7 );
		fprintf(fp, "f  %d//6  %d//6  %d//6\n", i*8+1,  i*8+4,  i*8+3 ); 
		fprintf(fp, "f  %d//6  %d//6  %d//6\n", i*8+1,  i*8+2,  i*8+4 ); 
		fprintf(fp, "f  %d//3  %d//3  %d//3\n", i*8+3,  i*8+8,  i*8+7 ); 
		fprintf(fp, "f  %d//3  %d//3  %d//3\n", i*8+3,  i*8+4,  i*8+8 ); 
		fprintf(fp, "f  %d//5  %d//5  %d//5\n", i*8+5,  i*8+7,  i*8+8 ); 
		fprintf(fp, "f  %d//5  %d//5  %d//5\n", i*8+5,  i*8+8,  i*8+6 ); 
		fprintf(fp, "f  %d//4  %d//4  %d//4\n", i*8+1,  i*8+5,  i*8+6 ); 
		fprintf(fp, "f  %d//4  %d//4  %d//4\n", i*8+1,  i*8+6,  i*8+2 ); 
		fprintf(fp, "f  %d//1  %d//1  %d//1\n", i*8+2,  i*8+6,  i*8+8 ); 
		fprintf(fp, "f  %d//1  %d//1  %d//1\n", i*8+2,  i*8+8,  i*8+4 ); 
}
	
	fclose(fp);
}

void write_group_of_blocks_info_obj_file(
																					const char*						filename,
																					const char*						header, 
																					const point_group3D_t*	groups, 
																					int										num
																				)
{
	FILE* fp = fopen(filename, "wt+");
	if(!fp)
		return;
		
	//write header
	
	if(header)
		fprintf(fp, "%s", header);
		
	fprintf(fp, "mtllib example.mtl\n");
	
	//write normals

	fprintf(fp, "vn  0.0  0.0  1.0\n");
	fprintf(fp, "vn  0.0  0.0 -1.0\n");
	fprintf(fp, "vn  0.0  1.0  0.0\n");
	fprintf(fp, "vn  0.0 -1.0  0.0\n");
	fprintf(fp, "vn  1.0  0.0  0.0\n");
	fprintf(fp, "vn -1.0  0.0  0.0\n");
	fprintf(fp, "\n");

	int n = 0;
	
	for(int g=0; g<num; g++)
	{
		fprintf(fp, "# object shape\n");
		fprintf(fp, "g shape_%d\n", g+1);
		
		//write vertices
		
		char vertices[BIG_BUFFER] = "";
		for(int i=0; i<groups[g].quantity; i++) 
			write_coord3D(vertices, groups[g].coords[i]);
		fprintf(fp, "%s", vertices);
		
		//write faces
		
		fprintf(fp, "usemtl face_%d\n\n", g+1);
		for(int i=0; i<groups[g].quantity; i++)
		{
			fprintf(fp, "f  %d//2  %d//2  %d//2\n", n*8+1,  n*8+7,  n*8+5 );
			fprintf(fp, "f  %d//2  %d//2  %d//2\n", n*8+1,  n*8+3,  n*8+7 );
			fprintf(fp, "f  %d//6  %d//6  %d//6\n", n*8+1,  n*8+4,  n*8+3 ); 
			fprintf(fp, "f  %d//6  %d//6  %d//6\n", n*8+1,  n*8+2,  n*8+4 ); 
			fprintf(fp, "f  %d//3  %d//3  %d//3\n", n*8+3,  n*8+8,  n*8+7 ); 
			fprintf(fp, "f  %d//3  %d//3  %d//3\n", n*8+3,  n*8+4,  n*8+8 ); 
			fprintf(fp, "f  %d//5  %d//5  %d//5\n", n*8+5,  n*8+7,  n*8+8 ); 
			fprintf(fp, "f  %d//5  %d//5  %d//5\n", n*8+5,  n*8+8,  n*8+6 ); 
			fprintf(fp, "f  %d//4  %d//4  %d//4\n", n*8+1,  n*8+5,  n*8+6 ); 
			fprintf(fp, "f  %d//4  %d//4  %d//4\n", n*8+1,  n*8+6,  n*8+2 ); 
			fprintf(fp, "f  %d//1  %d//1  %d//1\n", n*8+2,  n*8+6,  n*8+8 ); 
			fprintf(fp, "f  %d//1  %d//1  %d//1\n", n*8+2,  n*8+8,  n*8+4 ); 
			n++;
		}
		
		fprintf(fp, "\n");
	}
	
	fclose(fp);
}

