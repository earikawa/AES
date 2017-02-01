#include "so_handle.h"
# include <math.h>

# define M_PI           3.14159265358979323846


SoHandle::SoHandle()
{
}

void SoHandle::init() {
	_main.init();
}
void SoHandle::build() {
	_main.build(.2f, .01f, .01f, 12);
	_main.color = GsColor::darkblue;
}
void SoHandle::draw(const GsMat& tr, const GsMat& pr, const GsLight& l) {
	GsMat rot;
	GsMat handle, half, handle1, pedals;
	rot.rotx(M_PI / 2);

	handle.translation(0.0f, 0.0f, -0.1f);
	half.scale(1.0f, 0.5f, 1.0f);
	handle1.translation(0.2f, 0.55f, 0.1f);

	handle1.translation(0.0f, -0.1f, 0.1f);
	_main.draw(tr * handle * rot, pr, l);

	_main.draw(tr * half * handle1, pr, l);

	handle1.translation(0.0f, -0.1f, -0.1f);
	_main.draw(tr * half * handle1, pr, l);
}