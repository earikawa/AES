#include "so_tree.h"



SoTree::SoTree(){
	shadow = false;
}

void SoTree::init() {
	_leaves.init();
	_root.init();
}

void SoTree::build() {
	_leaves.build(0.75f, 0.0f, 0.3f, 100);
	_root.build(0.2f, 0.1f, 0.1f, 12);

	if (shadow) {
		_leaves.color = GsColor::black;
		_root.color = GsColor::black;
	}
	else {
		_leaves.color = GsColor::green;
		_root.color = GsColor::brown;
	}
}
void SoTree::draw(const GsMat& tr, const GsMat& pr, const GsLight& l) {
	GsMat leavesT;

	leavesT.translation(0.0f, 0.2f, 0.0f);

	_leaves.draw(tr * leavesT, pr, l);
	_root.draw(tr, pr, l);
}
