#include "so_tire.h"
# include <math.h>

# define M_PI           3.14159265358979323846


SoTire::SoTire()
{
}


void SoTire::init() {
	_tire.init();
	_spokes.init();
}
void SoTire::build() {
	_tire.build(0.05f, 0.2f, 0.2f, 12);
	_spokes.build(.2f, .01f, .01f, 12);

	_spokes.color = GsColor::lightgray;
}
void SoTire::draw(const GsMat& tr, const GsMat& pr, const GsLight& l) {
	float i;
	float angle = M_PI / 6;
	GsMat rx, ry, stransf, rot, rotbar1, tireP, totalTire, totalTire2, tireM, tireMy, tireT, genTire, turn;

	rot.rotx(M_PI / 2);
	tireP.translation(0.0f, -0.025f, 0.0f);

	_tire.draw(tr * rot * tireP, pr, l, 1);
	for (i = 0; i < 2 * M_PI; i += (angle)) {
		rotbar1.rotz(i);
		_spokes.draw(tr * rotbar1, pr, l);
	}
}
