#include "Line.h"
#include "ResourceManager.h"


Line::Line()
{
}

Line::Line(glm::vec3 start, glm::vec3 end)
{
	startPosition = start;
	endPosition = end;
	shader = ResourceManager::getInstance()->GetShader("basic");
}

Line::Line(glm::vec4 start, glm::vec4 end)
{
	startPosition = start;
	endPosition = end;
	shader = ResourceManager::getInstance()->GetShader("basic");
}
Line::Line(glm::vec3 start, glm::vec3 end,float thickness)
{
	lineThickness = thickness;
	startPosition = start;
	endPosition = end;
	shader = ResourceManager::getInstance()->GetShader("basic");
}

Line::Line(glm::vec4 start, glm::vec4 end,float thickness)
{
	lineThickness = thickness;
	startPosition = start;
	endPosition = end;
	shader = ResourceManager::getInstance()->GetShader("basic");
}


Line::~Line()
{
}

void Line::Update(float dt)
{

}

void Line::Render(Camera *cam)
{
	shader.Use();
	view = cam->GetViewMatrix();
	projection = glm::perspective(45.0f, (GLfloat)1280 / (GLfloat)720, 0.1f, 10000.0f);
	// Get their uniform location
	GLint modelLoc = glGetUniformLocation(shader.ID, "model");
	GLint viewLoc = glGetUniformLocation(shader.ID, "view");
	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	GLint colorLoc = glGetUniformLocation(shader.ID, "color");
	// Pass them to the shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glProgramUniform4fv(shader.ID, colorLoc, 1, m_lineColor);
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	glVertex3f(startPosition.x, startPosition.y, startPosition.z);
	glVertex3f(endPosition.x, endPosition.y, endPosition.z);
	glEnd();
	glDrawArrays(GL_LINE, 0, 2);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
}

void Line::SetLineColor(glm::vec4 color)
{
	m_lineColor[0] = color.x;
	m_lineColor[1] = color.y;
	m_lineColor[2] = color.z;
	m_lineColor[3] = color.w;
}
