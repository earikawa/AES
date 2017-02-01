#ifndef SO_FLOOR_H
#define SO_FLOOR_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include <gsim/gs_light.h>
# include <gsim/gs_material.h>
# include <gsim/gs_image.h>
# include "ogl_tools.h"

class SoFloor : public GlObjects
{
private:
	GlShader _vshgou, _fshgou;
	GlProgram _proggouraud;

	GsArray<GsVec>   P; // coordinates
	GsArray<GsVec>   N; // normals
	GsArray<GsColor>   C;
	GsArray<GsVec2> T;
	GsMaterial _mtl;
	int _numelements;

public:
	gsuint _id;
	float col;

	SoFloor();
	void init();
	void build();
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l);
};

#endif