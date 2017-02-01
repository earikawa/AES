
// Ensure the header file is included only once in multi-file projects
# pragma once

// Include needed header files
# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include <gsim/gs_light.h>
# include <gsim/gs_material.h>
# include <gsim/gs_image.h>
# include "ogl_tools.h"

// Scene objects should be implemented in their own classes; and
// here is an example of how to organize a scene object in a class.
// Note that each "Scene Object" derives GlObjects, which is our
// utility class to manipulate OpenGL buffers, etc.
// Scene object axis:
class SoMyObject : public GlObjects
 { private :
	GlShader _vshgou, _fshgou, _vshphong, _fshphong;
	GlProgram _proggouraud, _progphong;
    GsArray<GsVec>   P; // coordinates
	GsArray<GsVec>   N; // normals
	GsArray<GsColor>   C;
	GsArray<GsVec2> T;
	GsMaterial _mtl;
    int _numelements;
    // add all needed class members here
    // etc

 public:
	 GsArray<GsVec> NL; // normals
	 bool _flat;
	 gsuint _texid;
	 float col;

   public :

    // We build our scene objects with at least 3 methods: init(), build(), and draw().
    // We follow the concept that init() is called only once to initialize
    // the object. You could pass to init parameters such as shaders and programs
    // so that your main class can share them among objects, but for simplicity, here
    // we have our object to contain its own shader and program.
    // Method build() is to be called each time the object has to change; and draw()
    // will just set uniforms and call OpenGl buffers to draw the object. Method draw()
    // has to be kept as lightweight as possible because it may be called many times per second.

    SoMyObject ();
    void init ();
    void build (float len, float rt, float rb, float nfaces);
    void draw (const GsMat& tr, const GsMat& pr, const GsLight& l, int id);
 };

