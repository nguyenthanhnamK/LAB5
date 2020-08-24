#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/glut.h"
#include "Dependencies/freeglut/freeglut.h"
#include <stdio.h>
#include <stdlib.h>
#include "Shader.h"

#ifdef _MSC_VER
#	pragma comment(lib, "opengl32.lib")
#   pragma comment(lib, "glu32.lib")
#	pragma comment(lib, "glew32.lib")
#   pragma comment(lib, "freeglut.lib")
#endif 

#define WND_WIDTH 640
#define WND_HEIGHT 360
#define WND_TITLE   "demo01"
#define VS_FILE     "VERTEX.GLSL"
#define FS_FILE     "FRAGMENT.GLSL"

typedef enum objectMode { CUBE, SPHERE, TORUS, TEAPOT } OBJECT_MODE;

float xAngle = 0.0f;
float yAngle = 0.0f;
float zAngle = 0.0f;
int xMotion = 0;
int yMotion = 0;

GLSL_PROGRAM* prog = NULL;
OBJECT_MODE obj = TEAPOT;

void resize(int width, int height) {
	if (height == 0) height = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, (float)width / height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

	switch (obj) {
	case CUBE:
		glutSolidCube(1.5f); break;
	case SPHERE:
		glutSolidSphere(1.0f, 24, 24); break;
	case TORUS:
		glutSolidTorus(0.5, 1.0f, 24, 24); break;
	case TEAPOT:
		glutSolidTeapot(1.0f); break;
	}
	glutSwapBuffers();
}

void input(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0);
	case '1':
		obj = CUBE;   break;
	case '2':
		obj = SPHERE; break;
	case '3':
		obj = TORUS;  break;
	case '4':
		obj = TEAPOT; break;
	default:    break;
	}
}

void mouse(int button, int state, int x, int y) {
	if (state == 0 && button == 0) {
		xMotion = x;
		yMotion = y;
	}
}

void motion(int x, int y) {
	if (xMotion) {
		if (xMotion > x) yAngle -= 2.0f;
		if (xMotion < x) yAngle += 2.0f;
		xMotion = x;
	}
	if (yMotion) {
		if (yMotion > y) xAngle -= 1.0f;
		if (yMotion < y) xAngle += 1.0f;
		yMotion = y;
	}
}

void idle() {
	glutPostRedisplay();
}

GLboolean init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(WND_WIDTH, WND_HEIGHT);
	glutCreateWindow(WND_TITLE);
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutKeyboardFunc(input);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	if (GLEW_OK != glewInit()) return GL_FALSE;
	if (!(prog = glslCreate())) printf("No GLSL supported.\n");
	glslCompileFile(prog, VERTEX_SHADER, VS_FILE);
	glslCompileFile(prog, FRAGMENT_SHADER, FS_FILE);
	glslLink(prog);
	glslActivate(prog);
	glEnable(GL_DEPTH_TEST);
	return GL_TRUE;
}

void done() {
	glslDestroy(prog);
}

void run() {
	glutMainLoop();
}

int main(int argc, char** argv) {
	init(argc, argv);
	run();
	return 0;
}