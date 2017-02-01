#pragma once
# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include <gsim/gs_light.h>
# include <gsim/gs_material.h>
# include <gsim/gs_image.h>
# include "ogl_tools.h"
class SoRamp : public GlObjects
{
private:
	GlShader _vshgou, _fshgou;
	GlProgram _proggouraud;

	GsArray<GsVec>   P; // coordinates
	GsArray<GsVec>   N; // normals
	GsArray<GsColor>   C;
	GsMaterial _mtl;
	int _numelements;
public:
	SoRamp();
	void init();
	void build();
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& l);
};

