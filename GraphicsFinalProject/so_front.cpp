#include "so_front.h"



SoFront::SoFront()
{
}

void SoFront::init() {
	_tire.init();
	_handle.init();
}
void SoFront::build() {
	_tire.build();
	_handle.build();
}
void SoFront::draw(const GsMat& tr, const GsMat& pr, const GsLight& _light, float ang) {
	GsMat tireM, totalTire, hand;

	totalTire.translation(0.3f, 0.2f, 0.0f);
	tireM.rotz(ang);
	_tire.draw(tr * totalTire * tireM, pr, _light);
	//_tire1.draw(stransf* projection * totalTire * tireT * turn * tireM, sproj, _light);

	//handle
	//turn.roty(_handleA);
	//hand.translation(0.2f, 0.59f, 0.0f);
	//_handle.draw(tr * hand, pr, _light);
	//handle.draw(stransf * projection * handle * tireT * turn, sproj, _light); *
}