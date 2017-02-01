#include "so_body.h"
# include <math.h>

# define M_PI           3.14159265358979323846


SoBody::SoBody()
{
}


void SoBody::init() {
	_bar2.init();
	_object.init();
	_seat.init();
	tire.init();
	_handle.init();
}
void SoBody::build() {
	_bar2.build(.4f, .01f, .01f, 12);
	_bar2.color = GsColor::blue;
	_seat.build(0.2f, 0.01f, 0.1f, 12);
	_seat.color = GsColor::black;
	tire.build();
	_handle.build();
}

//ang refers to the angle of the tire
//ang2 refers to the angle that the handle is turning
void SoBody::draw(const GsMat& tr, const GsMat& pr, const GsLight& _light, float _ang, float ang2, float ang3) {
	GsMat rotbar1, barT, rotB, rot, handle1, half, totalTire, seatM, totalTire2, tireM, turn, handle;

	turn.roty(ang2-ang3);
	handle.translation(0.2f, 0.59f, 0.0f);
	_handle.draw(tr * handle * turn, pr, _light);
	//handle.draw(stransf * projection * handle * tireT * turn, sproj, _light);

	totalTire2.translation(-0.3f, 0.2f, 0.0f);
	tireM.rotz(_ang);
	tire.draw(tr * totalTire2 * tireM, pr, _light);

	rotbar1.rotz(-M_PI / 8);
	barT.translation(-0.325f, 0.125f, 0.0f);
	_bar2.draw(tr * barT * rotbar1, pr, _light);

	rotB.rotz(M_PI / 12);
	totalTire.translation(0.34f, 0.125f, 0.0f);
	_bar2.draw(tr * rotB  * totalTire, pr, _light);

	rotB.rotz(M_PI / 2);
	handle1.translation(0.5f, -0.225f, 0.0f);
	_bar2.draw(tr * rotB * handle1, pr, _light);

	rot.rotz(M_PI / 8);
	handle1.translation(0.03f, 0.2f, 0.0f);
	_bar2.draw(tr * rot * handle1, pr, _light);

	rot.rotz(-M_PI / 4);
	handle1.translation(-0.05f, 0.2f, 0.0f);
	_bar2.draw(tr *handle1* rot, pr, _light);

	rot.rotx(M_PI / 2);
	half.scale(0.25f, 0.5f, 0.25f);
	handle1.translation(-0.05f, 0.2f, -0.02f);
	_object.draw(tr * handle1 * rot * half, pr, _light, 1);

	rot.rotz(-M_PI / 2);
	half.scale(0.1f, 1.0f, 1.0f);
	handle1.translation(-0.25f, 0.575f, 0.0f);
	_seat.draw(tr *handle1 * rot * half * seatM, pr, _light);

}