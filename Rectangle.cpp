#include "Rectangle.h"

Rectangle::Rectangle(float pos_x, float pos_y, int width, int height) : vbo(nullptr, 0), ebo(nullptr, 0)
{
    vertices = {
        pos_x, pos_y, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // Bottom-left
        pos_x, pos_y + height, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Top-left
        pos_x + width, pos_y + height, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Top-right
        pos_x + width, pos_y, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // Bottom-right
    };

    GLuint indices[] = {
        0, 2, 1,
        0, 3, 2,
    };

    vao.Bind(); // Bind VAO before setting up buffers

    vbo = VBO(vertices.data(), vertices.size() * sizeof(GLfloat));  
    ebo = EBO(indices, sizeof(indices));  

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}


Rectangle::~Rectangle()
{
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
}

void Rectangle::Move(int direction)
{
}

void Rectangle::BindVAO()
{
	vao.Bind();
}
