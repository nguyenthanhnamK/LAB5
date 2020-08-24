#ifndef __SHADER_H__
#define __SHADER_H__

#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/glut.h"
typedef struct {
	union {
		struct { float x, y, z; }; 
		struct { float r, g, b; }; 
		float data[3];
	};
} vec3;
typedef enum glslShader { VERTEX_SHADER, FRAGMENT_SHADER } GLSL_SHADER;
typedef struct glslProgram {
	GLuint program;
	GLboolean linked;
} GLSL_PROGRAM;
GLSL_PROGRAM* glslCreate();
void glslDestroy(GLSL_PROGRAM* p);
GLboolean glslCompileFile(GLSL_PROGRAM* p, GLSL_SHADER type,
	const GLchar* fileName);
GLboolean glslCompileString(GLSL_PROGRAM* p, GLSL_SHADER type,
	const GLchar* source);
GLboolean glslLink(GLSL_PROGRAM* p);
GLboolean glslActivate(GLSL_PROGRAM* p);
void glslDeactivate(GLSL_PROGRAM* p);
GLint glslGetUniform(GLSL_PROGRAM* p, const GLchar* name);
GLboolean glslSetUniform1f(GLSL_PROGRAM* p, const GLchar* name, GLfloat v);
GLboolean glslSetUniform3f(GLSL_PROGRAM* p, const GLchar* name,
	GLfloat x, GLfloat y, GLfloat z);
GLboolean glslSetUniform3fv(GLSL_PROGRAM* p, const GLchar* name, const vec3 v);
#endif