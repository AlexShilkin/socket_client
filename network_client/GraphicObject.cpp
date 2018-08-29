#include "GraphicObject.h"



GraphicObject::GraphicObject()
{
	glGenVertexArrays(1, &this->vertexArrayObject);
	glGenBuffers(1, &this->vertexBufferObject);
	this->vertices = nullptr;
}


GraphicObject::~GraphicObject()
{
}

void GraphicObject::setTexture(GLfloat * textureCoord, GLint count)
{
	this->vertices = new GLfloat[count];
	memcpy(this->textureCoord, textureCoord, sizeof(GLfloat)*count);
}

void GraphicObject::setVertices(GLfloat * vertices, GLint count)
{
	this->vertices = new GLfloat[count];
	memcpy(this->vertices, vertices, sizeof(GLfloat)*count);

	glBindVertexArray(this->vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*count, (GLfloat*)this->vertices, GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void GraphicObject::setShader(Shader shader)
{
	this->shader = shader;
}

void GraphicObject::draw()
{
	shader.Use();
	glBindVertexArray(this->vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
