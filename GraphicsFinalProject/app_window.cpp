
# include <iostream>
# include <gsim/gs.h>
# include "app_window.h"
# include <math.h>

# define M_PI           3.14159265358979323846

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );

   _viewaxis = true;
   _fovy = GS_TORAD(60.0f);
   _rotx = gspi/8.0f;
   _roty = gspi/4.0f;
   _w = w;
   _h = h;

   _lasttime = gs_time();
   _animateinc = 0.1f;
   _animate = true;

   _angleF = _tireM = _angleR = _pAngle = _handleA = _angleB = 0;
   v = GsVec(_tireM, 0.0f, 0.0f);

   _eye = GsVec(0, 0, 2);
   _up = GsVec(0, 1, 0);
   _center = GsVec(0, 0, 0);

   _mov.open("mov2.txt");
   _mov2.open("movement.txt");
   _mov3.open("mov3.txt");
   _curv.open("cuv.txt");
   _c1.open("curve.txt");
   _mov4.open("mov4.txt");
   _mov5.open("mov5.txt");
   fillArray(_curv, _v);
   fillArray(_c1, _v1);
   initPrograms ();
   k = 0;
   _mov1 = _2move = _curve = _curve1 = _move3 = _move4 = _move5 = false;
   ang = false;
   turn2 = _angX = _angZ = 0;
 }

void AppWindow::initPrograms ()
 {
   // We are not directly initializing glsl programs here, instead, each scene object
   // initializes its own program(s). This makes sharing more difficult but is probably easier
   // to manage.

   // Init my scene objects:
   _axis.init ();
   _floor.init();

   _tire1.init();
   _tire2.init();
   _hand.init();
   _front.init();

   _tree.init();
   _treeS.init();

   _body.init();
   _ramp.init();

   _1.init(_mov);
   _2.init(_mov2);
   _3.init(_mov3);
   _4.init(_mov4);
   _5.init(_mov5);

   // set light:
   _light.set ( GsVec(10,0, 10), GsColor(90,90,90,255), GsColor::white, GsColor::white );
 }

// mouse events are in window coordinates, but your 2D scene is in [0,1]x[0,1],
// so make here the conversion when needed
GsVec2 AppWindow::windowToScene ( const GsVec2& v )
 {
   // GsVec2 is a lighteweight class suitable to return by value:
   return GsVec2 ( (2.0f*(v.x/float(_w))) - 1.0f,
                    1.0f - (2.0f*(v.y/float(_h))) );
 }

// Called every time there is a window event
void AppWindow::glutKeyboard ( unsigned char key, int x, int y )
 {
   float inc=0.025f;
   const float angle = M_PI / 180;
   const float incr = GS_TORAD(2.5f);
   switch ( key )
    { case 27 : exit(1); // Esc was pressed
	case ' ': resetBike(); break;
	  case 'a':      _roty-=incr; break;
	  case 'd':     _roty+=incr; break;
	  case 'w':        _rotx += incr; break;
	  case 's':      _rotx -= incr; break;
	 // case 'o': _angleF -= angle; _angleB -= angle; v += (totalAngle * GsVec(1, 0, 0)) * .005;
	  case 'u': _angX += angle; redraw(); break;
	  case 'j': _angX -= angle; redraw(); break;
	  case 'y': _angZ += angle; redraw(); break;
	  case 'h': _angZ -= angle; redraw(); break;
	  case 'v': turn2 += angle;  _angleR += angle; redraw(); break;
	  case 'b': turn2 -= angle;  _angleR -= angle; redraw(); break;
	  //case 'q': _rampOn = !_rampOn; redraw(); break;
	  //For writing points to a file for later interpolation
	  //case '1': _mov5 << _angX << " " << _angleR << " " <<  _angZ << " " << turn2 << " " << v << "\n" ; break;
	  //case '2': _mov5.close(); break; //fillArray(); break;
	  case '0':  _curve = true; k = 2; resetBike(); break;
	  case '1': _curve1 = true; k = 2; resetBike(); break;
	  case '9': _2move = true; resetBike(); break;
	  case '8': _mov1 = true; resetBike(); break;
	  case '7': _move3 = true; resetBike(); break;
	  case '6': _move4 = true; resetBike(); break;
	  case '5': _move5 = true; resetBike(); break;

		 // std::cout << v << std::endl;
      default : return;
	}
    redraw(); 
 }

void AppWindow::glutSpecial ( int key, int x, int y )
 {
   bool rd=true;
   const float incr=GS_TORAD(2.5f);
   const float incf=0.05f;
   const float angle = M_PI / 180;
   switch ( key )
    {
	  case GLUT_KEY_LEFT:      _angleR += angle; _handleA += angle; ang = true; break;
      case GLUT_KEY_RIGHT:     _angleR -= angle; _handleA -= angle; ang = true; break;
	  case GLUT_KEY_UP:        _angleF -= angle; _angleB -= angle; v += (totalAngle * GsVec(cos(_angZ), sin(_angZ), 0)) * .005;
							   //v.x -= -.005 * cos(_angleR); v.z -= .005 * sin(_angleR); 
							  if (ang) {
								  //if (turn2 < (.5 * _angleR))
								  if (turn2 < ( _angleR))
									  turn2 +=  (angle*.5);
								  else if (turn2 > _angleR)
									  turn2 -= (angle*.5);
								  if (fabs(turn2 - _angleR) < 0.1f)
									ang = false;
							  }break;
	  case GLUT_KEY_DOWN:      _angleF += angle; _angleB += angle; v += (totalAngle * GsVec(-cos(_angZ), -sin(_angZ), 0)) * .005;
								//v.x -= .005 * cos(_angleR); v.z -= -.005 * sin(_angleR); 
								if (ang) {
									if (turn2 < _angleR)
										turn2 += (angle*.5);
									else if (turn2 > _angleR)
										turn2 -= (angle*.5);
									if (turn2 == _angleR)
										ang = false;
								}break;
      case GLUT_KEY_PAGE_UP:   _fovy-=incf; break;
      case GLUT_KEY_PAGE_DOWN: _fovy+=incf; break;
      default: return; // return without rendering

	}
   if (rd) redraw(); // ask the window to be rendered when possible
 }

void AppWindow::glutMouse ( int b, int s, int x, int y )
 {
   // The mouse is not used in this example.
   // Recall that a mouse click in the screen corresponds
   // to a whole line traversing the 3D scene.
 }

void AppWindow::glutMotion ( int x, int y )
 {
 }

void AppWindow::glutMenu ( int m )
 {
   std::cout<<"Menu Event: "<<m<<std::endl;
 }

void AppWindow::glutReshape ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

void AppWindow::glutIdle ()
 {
	 const float angle = M_PI / 180;
	 GsVec temp, temp2;
	 if (_mov1) {
		 _angX = eval_bezier(k, _1._x);
		 _angleR = eval_bezier(k, _1._y);
		 _angZ = eval_bezier(k, _1._z);
		 turn2 = eval_bezier(k, _1._t);
		 //v += (totalAngle * GsVec(cos(_angZ), sin(_angZ), 0)) * .005;
		 v = eval_bezier(k, _1._v);
		 _angleF -= angle; _angleB -= angle;
		 k += .003f;
		 if (k >= 1) {
			 k = 0;
			 v.y = 0;
			 _mov1 = false;
		 }
	 }
	if (_2move) {
		_angX = eval_bezier(k, _2._x);
		_angleR = eval_bezier(k, _2._y);
		_angZ = eval_bezier(k, _2._z);
		turn2 = eval_bezier(k, _2._t);
		//v += (totalAngle * GsVec(cos(_angZ), sin(_angZ), 0)) * .005;
		v = eval_bezier(k, _2._v);
		_angleF -= angle; _angleB -= angle;
		k += .003f;
		if (k >= 1) {
			k = 0;
			v.y = 0;
			_2move = false;
		}
		//std::cout << _2._v.size() << std::endl;
	}
	if (_move3) {
		_angX = eval_bezier(k, _3._x);
		_angleR = eval_bezier(k, _3._y);
		_angZ = eval_bezier(k, _3._z);
		turn2 = eval_bezier(k, _3._t);
		//v += (totalAngle * GsVec(cos(_angZ), sin(_angZ), 0)) * .005;
		v = eval_bezier(k, _3._v);
		_angleF -= angle; _angleB -= angle;
		k += .003f;
		if (k >= 1) {
			k = 0;
			v.y = 0;
			_move3 = false;
		}
	}
	if (_move4) {
		_angX = eval_bezier(k, _4._x);
		_angleR = eval_bezier(k, _4._y);
		_angZ = eval_bezier(k, _4._z);
		turn2 = eval_bezier(k, _4._t);
		//v += (totalAngle * GsVec(cos(_angZ), sin(_angZ), 0)) * .005;
		v = eval_bezier(k, _4._v);
		_angleF -= angle; _angleB -= angle;
		k += .005f;
		if (k >= 1) {
			k = 0;
			v.y = 0;
			_move4 = false;
		}
	}
	if (_move5) {
		_angX = eval_bezier(k, _5._x);
		_angleR = eval_bezier(k, _5._y);
		_angZ = eval_bezier(k, _5._z);
		turn2 = eval_bezier(k, _5._t);
		//v += (totalAngle * GsVec(cos(_angZ), sin(_angZ), 0)) * .005;
		v = eval_bezier(k, _5._v);
		_angleF -= angle; _angleB -= angle;
		k += .005f;
		if (k >= 1) {
			k = 0;
			v.y = 0;
			_move5 = false;
		}
	}
	if (_curve) {
		//std::cout << _v(25) << std::endl;
		v = eval_bspline(k, 3, _v);
		k += .0075f;
		temp = (eval_bspline(k, 3, _v) - v) / .0075;
		temp2 = (eval_bspline(k+.0075f, 3, _v) - eval_bspline(k, 3, _v)) / .0075;
		temp.normalize(); temp2.normalize();
		_angleF -= angle; _angleB -= angle;
		if (temp2.x < temp.x) {
			if (_angleR < 1.09)
				_angleR += angle;
			if (turn2 < 1.09)
				turn2 += (angle/2);
		}
		else if (temp2.x > temp.x) {
			if (_angleR > -1.09)
				_angleR -= angle;
			if (turn2 > -1.09)
				turn2 -= (angle/2);
		}
		else {
			_angleR = 0;
			turn2 = 0;
		}
		if (k >= _v.size()) {
			k = 0;
			v.y = 0;
			_curve = false;
		}
		
	}
	if (_curve1) {
		v = eval_bspline(k, 3, _v1);
		k += .025f;
		temp = (eval_bspline(k, 3, _v1) - v) / .025;
		temp2 = (eval_bspline(k + .025f, 3, _v1) - eval_bspline(k, 3, _v1)) / .025;
		temp.normalize(); temp2.normalize();
		_angleF -= angle; _angleB -= angle;
		//std::cout << (temp).norm() << std::endl;
		if (temp2.x < temp.x) {
			if (_angleR < atan(v.z/v.x))
				_angleR += 2 * angle;
			if (turn2 < atan(v.z / v.x))
				turn2 += (angle);
		}
		else if (temp2.x > temp.x) {
			if (_angleR > -atan(v.z / v.x))
				_angleR -= 2 * angle;
			if (turn2 > -atan(v.z / v.x))
				turn2 -= (angle);
		}
		else {
			_angleR = 0;
			turn2 = 0;
		}
		if (k >= _v1.size()) {
			k = 0;
			v.y = 0;
			_curve1 = false;
		}
	}
	redraw();
	 
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::glutDisplay ()
 {
   // Clear the rendering window
   glClearColor(0.1f,0.1f,0.2f,1); // change the background a little bit
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   _eye = v;
   _eye.z = 2;
   //_eye = GsVec(0, 2, 0);
   _up = GsVec(0, 1, 0);
   _center = v;
   //_center = GsVec(0, v.y, 0);*/

   _treeS.shadow = true;

   _ramp.build();
	_floor.build();

   _tire1.build();
   _hand.build();
   _tree.build();
   _treeS.build();
   _body.build();
   _front.build();

   // Define our scene transformation:
   GsMat rx, ry, stransf, totalTire, totalTire2,tireM, tireT, _turnBody, barT, turn;
   GsMat handle, half, handle1, pedals, _jump;
   GsMat treeT, _rampMov, angX, angZ;
   rx.rotx ( _rotx );
   ry.roty ( _roty );
   stransf = rx*ry; // set the scene transformation matrix
   
   // Define our projection transformation:
   // (see demo program in gltutors-projection.7z, we are replicating the same behavior here)
   GsMat camview, persp, sproj;
   camview.lookat ( _eye, _center, _up ); // set our 4x4 "camera" matrix

   float aspect=1.0f, znear=0.1f, zfar=50.0f;
   persp.perspective ( _fovy, aspect, znear, zfar ); // set our 4x4 perspective matrix

   // Our matrices are in "line-major" format, so vertices should be multiplied on the 
   // right side of a matrix multiplication, therefore in the expression below camview will
   // affect the vertex before persp, because v' = (persp*camview)*v = (persp)*(camview*v).
   sproj = persp * camview; // set final scene projection

   GsVec p = GsVec(0.0f, 1.0f, 0.0f);
   GsVec n = GsVec(0.0f, 1.0f, 0.0f);
   float l = dot(p, n);
   GsVec a = dot(GsVec(0, 0, 0), n) * p;

   GsMat projection = GsMat(l, -1.0f, 0.0f, a.x,
						   0.0f, l-1.0f, 0.0, a.y,
						   0.0f, -1.0f, l, a.z,
						   0.0f, 0.0f, 0.0f, l);

   //  Note however that when the shader receives a matrix it will store it in column-major 
   //  format, what will cause our values to be transposed, and we will then have in our 
   //  shaders vectors on the left side of a multiplication to a matrix.

   totalTire.translation(0.3f, 0.2f, 0.0f);
   totalTire2.translation(-0.3f, 0.2f, 0.0f);
   tireT.translation(v);

   turn.roty(_angleR);
   angX.rotx(_angX);
   angZ.rotz(_angZ);
   totalAngle = angX * turn * totalTire2 * angZ * totalTire2.inverse();

   //floor
   _floor.draw(stransf, sproj, _light);
   /*if (_rampOn) {
	   _rampMov.translation(1.0, 0.0, -.25);
	   half.scale(1.f, 1.f, 2);
	   _ramp.draw(stransf * half * _rampMov, sproj, _light);
	   _rampMov.translation(1.0, 0.0, .25);
	   barT.roty(M_PI);
	   _ramp.draw(stransf * half * _rampMov * barT, sproj, _light);
   }*/

   //trees
   treeT.translation(0.5f, 0.0f, -4.0f);
   _tree.draw(stransf * treeT, sproj, _light);
   _treeS.draw(stransf * treeT * projection, sproj, _light);

   treeT.translation(1.0f, 0.0f, -5.0f);
   _tree.draw(stransf * treeT, sproj, _light);
   _treeS.draw(stransf * treeT * projection, sproj, _light);

   treeT.translation(4.0f, 0.0f, .5f);
   _tree.draw(stransf * treeT, sproj, _light);
   _treeS.draw(stransf * treeT * projection, sproj, _light);

   _front.draw(stransf * tireT *totalTire * totalAngle * totalTire.inverse(), sproj, _light, _angleF);
   _front.draw(stransf * projection * tireT*totalTire * totalAngle * totalTire.inverse(), sproj, _light, _angleF);

   //frame
   _turnBody.roty(turn2);
   //totalAngle = angX * _turnBody * angZ;
   totalAngle = angX * _turnBody * totalTire2 * angZ * totalTire2.inverse();
   _body.draw(stransf * tireT * totalTire * totalAngle * totalTire.inverse(), sproj, _light, _angleB, _angleR, turn2);
   _body.draw(stransf * projection * tireT * totalTire * totalAngle * totalTire.inverse(), sproj, _light, _angleB, _angleR, turn2);

   //totalAngle = angX * turn * angZ;
   totalAngle = angX * turn * totalTire2 * angZ * totalTire2.inverse();
   // Swap buffers and draw:
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

void AppWindow::fillArray(std::fstream &_movement, GsArray<GsVec> &c) {
	std::string line, x1, y1, z1, t1;
	GsVec temp;
	c.size(0); c.reserve(100);
	while (std::getline(_movement, line)) {
		std::getline(_movement, x1, ' ');
		std::getline(_movement, y1, ' ');
		std::getline(_movement, z1, ' ');

		c.push(GsVec(stof(x1), stof(y1), stof(z1)));
	}
	//k = 0;*/
}

float AppWindow::N(int i, int k, float u) {
	float ui = float(i);
	if (k == 1) {
		return ui <= u && u < ui + 1 ? 1.0f : 0;
	}
	else
		return ((u - ui) / (k - 1)) * N(i, k - 1, u) + ((ui + k - u) / (k - 1)) * N(i + 1, k - 1, u);
}
GsVec AppWindow::eval_bspline(float t, int k, const GsArray<GsVec>& pnts) {
	//t in [2, n+1], u = t -i
	int i;
	int n = pnts.size();
	GsVec o = GsVec(0, 0, 0);
	for (i = 0; i < n; i++) {
		o += pnts[i] * N(i, k, t);
	}
	return o;
}

GsVec AppWindow::eval_bezier(float t, const GsArray<GsVec>& ctrlpnts) {
	int i, j;
	float temp = 1.0f;
	int n = ctrlpnts.size() - 1;
	GsVec o = GsVec(0.0f, 0.0f, 0.0f);
	for (i = 0; i <= n; i++) {
		temp = ((factorial(n)) / (factorial(i) * factorial(n - i)));
		temp *= (pow(t, i))*pow((1 - t), (n - i));
		o += (ctrlpnts(i) * temp);
	}
	return o;
}

float AppWindow::eval_bezier(float t, const GsArray<float>& ctrlpnts) {
	int i, j;
	float temp = 1.0f, o = 0;
	int n = ctrlpnts.size() - 1;
	for (i = 0; i <= n; i++) {
		temp = ((factorial(n)) / (factorial(i) * factorial(n - i)));
		temp *= (pow(t, i))*pow((1 - t), (n - i));
		o += (ctrlpnts(i) * temp);
	}
	return o;
}

