#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <GL/glew.h>
#include "Shader.h"
#include "File.h"

class GraphicObject
{
private:
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;

	GLfloat * vertices;
	GLfloat * textureCoord;
	Shader shader;

public:
	GraphicObject();
	~GraphicObject();

	void setTexture(GLfloat* textureCoord, GLint count);
	void setVertices(GLfloat* vertices, GLint count);
	void setShader(Shader shader);
	void draw();

};

#endif // !GRAPHICOBJECT_H

