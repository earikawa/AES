# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include <gsim/gs_light.h>
# include <gsim/gs_material.h>
# include <gsim/gs_image.h>
# include "ogl_tools.h"
# include "so_myobject.h"
# include "so_cylinder.h"
# include "so_tire.h"
# include "so_handle.h"

class SoBody : public GlObjects
{
private:
	SoCylinder _bar2, _seat;
	SoMyObject _object;
	SoTire tire;
	SoHandle _handle;
public:
	SoBody();
	void init();
	void build();
	void draw(const GsMat& tr, const GsMat& pr, const GsLight& _light, float ang, float ang2, float ang3);
};
