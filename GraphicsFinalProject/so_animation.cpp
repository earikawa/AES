#include "so_animation.h"



SoAnimation::SoAnimation()
{
	
}

void SoAnimation::init(std::fstream &_movement) {
	std::string line, x1, y1, z1, t1, sx, sy, sz;
	GsVec temp;
	_x.size(0); _y.size(0); _z.size(0); _t.size(0); _v.size(0);
	while (std::getline(_movement, line)) {
		std::getline(_movement, x1, ' ');
		std::getline(_movement, y1, ' ');
		std::getline(_movement, z1, ' ');
		std::getline(_movement, t1, ' ');

		std::getline(_movement, sx, ' ');
		std::getline(_movement, sy, ' ');
		std::getline(_movement, sz, ' ');

		_x.push(stof(x1));
		_y.push(stof(y1));
		_z.push(stof(z1));
		_t.push(stof(t1));

		_v.push(GsVec(stof(sx), stof(sy), stof(sz)));
	}
	//std::cout << _v.size() << std::endl;
}

