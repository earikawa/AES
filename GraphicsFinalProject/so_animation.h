#pragma once
# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_light.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"

# include <iostream>
# include <fstream>
# include <sstream>

class SoAnimation : public GlObjects
{
public:
	GsArray<GsVec> _v;
	GsArray<float>_t, _x, _y, _z;
	SoAnimation();
	void init(std::fstream &_movement);
};

