#include "so_floor.h"



SoFloor::SoFloor()
{
	col = .75;
}
void SoFloor::init() {
	// Build program:
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_gouraud.glsl");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_mcol_gouraud.glsl");
	_proggouraud.init_and_link(_vshgou, _fshgou);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use at least 1 vertex array
	gen_buffers(3);       // will use at least 1 buffer
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
void SoFloor::build() {
	//floor
	P.push() = GsVec(-10, 0, -10); P.push() = GsVec(10, 0, -10); P.push() = GsVec(10, 0, 10);
	P.push() = GsVec(10, 0, 10); P.push() = GsVec(-10, 0, 10); P.push() = GsVec(-10, 0, -10);

	N.push() = GsVec(0, 1, 0); N.push() = GsVec(0, 1, 0); N.push() = GsVec(0, 1, 0);
	N.push() = GsVec(0, 1, 0); N.push() = GsVec(0, 1, 0); N.push() = GsVec(0, 1, 0);

	//T.push() = GsVec2(0, 1); T.push() = GsVec2(1, 1); T.push() = GsVec2(1, 0);
	//T.push() = GsVec2(0, 1); T.push() = GsVec2(0, 0); T.push() = GsVec2(1, 0);

	//walls
	//P.push() = GsVec(-2, -2, 0); P.push() = GsVec(2, -2, 0); P.push() = GsVec(2, 2, 0);
	//P.push() = GsVec(2, 2, 0); P.push() = GsVec(-2, 2, 0); P.push() = GsVec(-2, -2, 0);


	C.size(P.size()); C.setall(GsColor::darkgreen);
	_mtl.specular.set(255, 255, 255);
	_mtl.shininess = 8; // increase specular effect

						// then send data to OpenGL buffers:
	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*P.size(), P.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*N.size(), N.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(gsbyte)*C.size(), C.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);

	/*glBindBuffer(GL_ARRAY_BUFFER, buf[3]);
	glBufferData(GL_ARRAY_BUFFER, T.size() * 2 * sizeof(float), T.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0); // false means no normalization */

	glBindVertexArray(0); // break the existing vertex array object binding.

						  // save size so that we can free our buffers and later draw the OpenGL arrays:
	_numelements = P.size();

	// free non-needed memory:
	P.capacity(0); C.capacity(0); N.capacity(0);
}
void SoFloor::draw(const GsMat& tr, const GsMat& pr, const GsLight& l) {
	float f[4];
	float sh = (float)_mtl.shininess;
	if (sh<0.001f) sh = 64;

	glBindVertexArray(va[0]);
	//glBindTexture(GL_TEXTURE_2D, _id);

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
	//glUniform1fv(_proggouraud.uniloc[9], 1, &col);
	// Draw:

	glDrawArrays(GL_TRIANGLES, 0, _numelements);
	glBindVertexArray(0); // break the existing vertex array object binding.
}