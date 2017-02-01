
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_light.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"
# include "so_axis.h"
# include "so_lines.h"
# include "so_superquadric.h"
# include "so_myobject.h"
# include "so_cylinder.h"
# include "so_floor.h"
# include "so_tree.h"
# include "so_tire.h"
# include "so_handle.h"
# include "so_body.h"
# include "so_ramp.h"
# include "so_front.h"
# include "so_animation.h"

# include <iostream>
# include <fstream>
# include <sstream>

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :

    // My scene objects:
    SoAxis _axis;
    SoLines _lines; // used to draw the object normals
	SoFloor _floor, _walls;
	SoTree _tree, _treeS;
	SoTire _tire1, _tire2;
	SoHandle _hand;
	SoBody _body;
	SoRamp _ramp;
	SoFront _front;

	std::fstream _mov, _mov2, _curv, _mov3, _mov4, _mov5, _c1;
	SoAnimation _1, _2, _3, _4, _5;
	bool _mov1, _2move, ang, _curve, _curve1, _move3, _move4, _move5, _rampOn;

	GsArray<GsVec> _v, _v1;
	//GsArray<float>_t, _x, _y, _z;
	float k, turn2;
	GsVec jump;

    // Scene data:
    bool  _viewaxis;
    GsLight _light;
    
    // App data:
    enum MenuEv { evOption0, evOption1 };
	GsVec _eye, _up, v, _center;
	GsMat totalAngle;
	bool _view;
	float _rotx, _roty, _fovy, _angleF, _angleB, _eyeY;
	float _tireM, _angleR, _pAngle, _handleA, _angX, _angZ;
    int _w, _h, _nfaces;
    double _lasttime; // last time update during animation
    float _animateinc, _lz;
    bool _animate;
    bool _normals;
    bool _flatn;
    bool _phong;
	float _rt, _rb;

	GsVec eval_bezier(float t, const GsArray<GsVec>& ctrlpnts);
	float eval_bezier(float t, const GsArray<float>& ctrlpnts);
	float N(int i, int k, float u);
	GsVec eval_bspline(float t, int k, const GsArray<GsVec>& pnts);
	void fillArray(std::fstream &_movement, GsArray<GsVec> &c);
	long factorial(int n) {
		int temp = 1;
		if (n <= 1)
			return 1;
		while (n > 1) {
			temp *= n;
			n--;
		}
		//std::cout << temp << std::endl;
		return temp;
	}
	void resetBike() {
		v = GsVec(0, 0, 0); _angX = _angleR = _angZ = turn2 = 0; redraw();
	}

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void initPrograms ();
    GsVec2 windowToScene ( const GsVec2& v );

   private : // functions derived from the base class
    virtual void glutMenu ( int m );
    virtual void glutKeyboard ( unsigned char key, int x, int y );
    virtual void glutSpecial ( int key, int x, int y );
    virtual void glutMouse ( int b, int s, int x, int y );
    virtual void glutMotion ( int x, int y );
    virtual void glutIdle ();
    virtual void glutDisplay ();
    virtual void glutReshape ( int w, int h );
 };

#endif // APP_WINDOW_H
