#include "GLee.h"
#include "LegacySelectionRenderer.h"

using namespace Crystal::Shader;

namespace {

	int SelectHits(GLuint hits, GLuint *buf) {
		GLuint hit_name[4] = { -1, -1, -1, -1 };
		float depth_min = 10.0f;
		float depth_1 = 1.0f;
		float depth_2 = 1.0f;
		GLuint depth_name;
		GLuint *ptr;

		if (hits <= 0) {
			return -1;
		}
		ptr = (GLuint*)buf;

		for (unsigned int i = 0; i < hits; i++) {
			depth_name = *ptr;

			ptr++;
			depth_1 = (float)*ptr / 0x7fffffff;

			ptr++;
			depth_2 = (float)*ptr / 0x7fffffff;

			ptr++;

			if (depth_min > depth_1) {
				depth_min = depth_1;
				for (int j = 0; j < depth_name; j++) {
					hit_name[j] = *ptr;
					ptr++;
				}
			}
			else {
				for (GLuint j = 0; j < depth_name; j++) {
					ptr++;
				}
			}
		}

		return 1;
	}

	void DrawRects(GLenum mode) {
		if (mode == GL_SELECT) {
			glLoadName(1);
		}
		glBegin(GL_QUADS);
		glColor3f(0, 1, 0);
		glVertex3i(1, 2, 0);
		glVertex3i(1, 0, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 2, 0);
		glEnd();
		if (mode == GL_SELECT) {
			glLoadName(2);
		}
	}

	void gluPickMatrix(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLint viewport[4])
	{


		float sx, sy;
		float tx, ty;

		//	from OGL_Sample code library

		//    /* Translate and scale the picked region to the entire window */
		//     glTranslatef((viewport[2] - 2 * (x - viewport[0])) / deltax,
		// 	    (viewport[3] - 2 * (y - viewport[1])) / deltay, 0);
		//     glScalef(viewport[2] / deltax, viewport[3] / deltay, 1.0);

		sx = viewport[2] / width;
		sy = viewport[3] / height;
		tx = (viewport[2] + 2.0f * (viewport[0] - x)) / width;
		ty = (viewport[3] + 2.0f * (viewport[1] - y)) / height;


		/*
		mp[0][0] = sx;

		mp[0][3] = tx;

		mp[1][1] = sy;

		mp[1][3] = ty;


		glMultMatrixf((GLfloat*)&mp);
		*/

	}
}

void LegacySelectionRenderer::pick(int x, int y)
{
	constexpr int BUFSIZE = 1;
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	float current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(BUFSIZE, selectBuf);
	(void)glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(x, viewport[3] - y, 5.0f, 5.0f, viewport);
	current_aspect = (float)viewport[2] / (float)viewport[3];
	//gluPerspective(60.0, current_aspect, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	DrawRects(GL_SELECT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);
	SelectHits(hits, selectBuf);

}


void LegacySelectionRenderer::render()
{

}