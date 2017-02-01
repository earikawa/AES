
# include "so_cylinder.h"
# include <math.h>

# define M_PI           3.14159265358979323846

SoCylinder::SoCylinder()
{
	_numelements = 0;
	_flat = false;
	color = GsColor::red;
}

// init programs here, this will be done only once:
void SoCylinder::init()
{
	// Build program:
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_gouraud.glsl");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_mcol_gouraud.glsl");
	_proggouraud.init_and_link(_vshgou, _fshgou);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use at least 1 vertex array
	gen_buffers(3);       // will use at least 1 buffer
						  //_prog.uniform_locations ( .. ); // declare here uniforms
						  //_prog.uniform_location ( 0, "vTransf" ); // each name must appear in the shader
						  //_prog.uniform_location ( 1, "vProj" );
	_proggouraud.uniform_locations(9); // will send 9 variables
	_proggouraud.uniform_location(0, "vTransf");
	_proggouraud.uniform_location(1, "vProj");
	_proggouraud.uniform_location(2, "lPos");
	_proggouraud.uniform_location(3, "la");
	_proggouraud.uniform_location(4, "ld");
	_proggouraud.uniform_location(5, "ls");
	_proggouraud.uniform_location(6, "ka");
	_proggouraud.uniform_location(7, "ks");
	_proggouraud.uniform_location(8, "sh");
}



// fill your arrays here, may be called each time the object has to change:
void SoCylinder::build(float len, float rt, float rb, float nfaces)
{
	float angle = M_PI / (nfaces / 2.0f);
	float k, i;
	GsVec a, b, c, d, n1, n2, n3;
	GsPnt f1c;
	const float ns = 0.1f;

	P.size(0); N.size(0); NL.size(0); C.size(0); // set size to zero, just in case
	P.reserve(100); // reserve space to avoid re-allocations from the calls below

	for (k = 0; k <= (4 * M_PI); k += (angle)) {
		if (_flat) {
			a = GsVec(rt * cos(k), len, rt * sin(k));
			b = GsVec(rt * cos(angle + k), len, rt * sin(k + angle));
			c = GsVec(0, len, 0);
			d = normal(a, c, b);

			P.push(a); P.push(b); P.push(c);
			N.push(d); N.push(d); N.push(d);
			f1c = (a + c + b) / 3.0f; NL.push() = f1c; NL.push() = f1c + (d*ns);

			a = GsVec(rt * cos(k), len, rt * sin(k));
			b = GsVec(rb * cos(k), 0, rb * sin(k));
			c = GsVec(rb * cos(k + angle), 0, rb * sin(k + angle));
			d = normal(a, c, b);

			P.push(a); P.push(b); P.push(c);
			N.push(d); N.push(d); N.push(d);
			f1c = (a + c + b) / 3.0f; NL.push() = f1c; NL.push() = f1c + (d*ns);

			a = GsVec(rt * cos(k + angle), len, rt * sin(k + angle));
			b = GsVec(rb * cos(k), len, rb * sin(k));
			c = GsVec(rb * cos(k + angle), 0, rb * sin(k + angle));
			d = normal(a, c, b);

			P.push(a); P.push(b); P.push(c);
			N.push(d); N.push(d); N.push(d);
			f1c = (a + c + b) / 3.0f; NL.push() = f1c; NL.push() = f1c + (d*ns);

			a = GsVec(rt * cos(k), 0, rt * sin(k));
			b = GsVec(rb * cos(angle + k), 0, rb * sin(k + angle));
			c = GsVec(0, 0, 0);
			d = normal(a, b, c);
			f1c = (a + c + b) / 3.0f; NL.push() = f1c; NL.push() = f1c + (d*ns);

			P.push(a); P.push(b); P.push(c);
			N.push(d); N.push(d); N.push(d);
		}
		else {
			/*a = GsVec(rt * cos(k), len, rt * sin(k));
			b = GsVec(rt * cos(angle + k), len, rt * sin(k + angle));
			c = GsVec(0, len, 0);
			n1 = GsVec(0, 1, 0);
			n2 = GsVec(0, 1, 0);
			n3 = GsVec(0, 1, 0);

			P.push(a); P.push(b); P.push(c);
			N.push(n1); N.push(n2); N.push(n3);
			NL.push() = a; NL.push() = a + (n1*ns); NL.push() = b; NL.push() = b + (n2*ns); NL.push() = c; NL.push() = c + (n3*ns);*/

			a = GsVec(rt * cos(k), len, rt * sin(k));
			b = GsVec(rb * cos(k), 0, rb * sin(k));
			c = GsVec(rb * cos(k + angle), 0, rb * sin(k + angle));
			n1 = GsVec(cos(k), 0, sin(k));
			n2 = GsVec(cos(k), 0, sin(k));
			n3 = GsVec(cos(k + angle), 0, sin(k + angle));

			P.push(a); P.push(b); P.push(c);
			N.push(n1); N.push(n2); N.push(n3);
			NL.push() = a; NL.push() = a + (n1*ns); NL.push() = b; NL.push() = b + (n2*ns); NL.push() = c; NL.push() = c + (n3*ns);

			a = GsVec(rt * cos(k + angle), len, rt * sin(k + angle));
			b = GsVec(rt * cos(k), len, rt * sin(k));
			c = GsVec(rb * cos(k + angle), 0, rb * sin(k + angle));
			n1 = GsVec(cos(k + angle), 0, sin(k + angle));
			n2 = GsVec(cos(k), 0, sin(k));
			n3 = GsVec(cos(k + angle), 0, sin(k + angle));

			P.push(a); P.push(b); P.push(c);
			N.push(n1); N.push(n2); N.push(n3);
			NL.push() = a; NL.push() = a + (n1*ns); NL.push() = b; NL.push() = b + (n2*ns); NL.push() = c; NL.push() = c + (n3*ns);

			/*a = GsVec(rt * cos(k), 0, rt * sin(k));
			b = GsVec(rb * cos(angle + k), 0, rb * sin(k + angle));
			c = GsVec(0, 0, 0);
			d = normal(a, b, c);
			n1 = GsVec(0, -1, 0);
			n2 = GsVec(0, -1, 0);
			n3 = GsVec(0, -1, 0);

			P.push(a); P.push(b); P.push(c);
			N.push(n1); N.push(n2); N.push(n3);
			NL.push() = a; NL.push() = a + (n1*ns); NL.push() = b; NL.push() = b + (n2*ns); NL.push() = c; NL.push() = c + (n3*ns);*/
		}

	}

	C.size(P.size()); C.setall(color);
	_mtl.specular.set(255, 255, 255);
	_mtl.shininess = 8; // increase specular effect

						// then send data to OpenGL buffers:
	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*P.size(), P.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*N.size(), N.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(gsbyte)*C.size(), C.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);

	glBindVertexArray(0); // break the existing vertex array object binding.

						  // save size so that we can free our buffers and later draw the OpenGL arrays:
	_numelements = P.size();

	// free non-needed memory:
	P.capacity(0); C.capacity(0); N.capacity(0);

}

// call this everytome you need to draw:
void SoCylinder::draw(const GsMat& tr, const GsMat& pr, const GsLight& l)
{
	float f[4];
	float sh = (float)_mtl.shininess;
	if (sh<0.001f) sh = 64;
	// Prepare program:
	glUseProgram(_proggouraud.id);
	// set unifrm values here
	glUseProgram(_proggouraud.id);
	glUniformMatrix4fv(_proggouraud.uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(_proggouraud.uniloc[1], 1, GL_FALSE, pr.e);
	glUniform3fv(_proggouraud.uniloc[2], 1, l.pos.e);
	glUniform4fv(_proggouraud.uniloc[3], 1, l.amb.get(f));
	glUniform4fv(_proggouraud.uniloc[4], 1, l.dif.get(f));
	glUniform4fv(_proggouraud.uniloc[5], 1, l.spe.get(f));
	glUniform4fv(_proggouraud.uniloc[6], 1, _mtl.ambient.get(f));
	glUniform4fv(_proggouraud.uniloc[7], 1, _mtl.specular.get(f));
	glUniform1fv(_proggouraud.uniloc[8], 1, &sh);
	// Draw:
	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numelements);
	glBindVertexArray(0); // break the existing vertex array object binding.
}

