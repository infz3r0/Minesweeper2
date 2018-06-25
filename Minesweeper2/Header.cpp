#include "Header.h"

button smile = { 0,0,0,0 };

void drawBox(int cx_bot_left, int cy_bot_left, int cx_top_right, int cy_top_right, rgb border, rgb fill)
{
	//Box

	glBegin(GL_QUADS);
	glColor3f(fill.r, fill.g, fill.b);  // Blue

	glVertex2f(cx_bot_left, cy_bot_left);       // Center of circle
	glVertex2f(cx_bot_left, cy_top_right);
	glVertex2f(cx_top_right, cy_top_right);
	glVertex2f(cx_top_right, cy_bot_left);

	glEnd();


	//Box border

	glBegin(GL_LINES);
	glColor3f(border.r, border.g, border.b);  // Blue

	glVertex2f(cx_bot_left, cy_bot_left);      // Center of circle
	glVertex2f(cx_bot_left, cy_top_right);

	glVertex2f(cx_bot_left, cy_top_right);
	glVertex2f(cx_top_right, cy_top_right);

	glVertex2f(cx_top_right, cy_top_right);
	glVertex2f(cx_top_right, cy_bot_left);

	glVertex2f(cx_top_right, cy_bot_left);
	glVertex2f(cx_bot_left, cy_bot_left);

	glEnd();

	glFlush();
}

void drawSmile(int cx, int cy, float r)
{
	glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
	glLoadIdentity();              // Reset model-view matrix

								   //smile
	int numSegments = 100;
	GLfloat angle;

	glPushMatrix();

	glTranslatef(cx, cy, 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 0.0f);  // Blue
	glVertex2f(0.0f, 0.0f);       // Center of circle

	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * r, sin(angle) * r);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(cx, cy, 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);  // Blue

	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * r, sin(angle) * r);
	}
	glEnd();

	glPopMatrix();

	float eye = 0.1;

	//Left eye
	glPushMatrix();

	glTranslatef(cx - (r * 0.3), cy + (r * 0.3), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 0.0f);  // Blue
	glVertex2f(0.0f, 0.0f);       // Center of circle
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * r * eye, sin(angle) * r * eye);
	}
	glEnd();

	glPopMatrix();

	//Right eye
	glPushMatrix();

	glTranslatef(cx + (r * 0.3), cy + (r * 0.3), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 0.0f);  // Blue
	glVertex2f(0.0f, 0.0f);       // Center of circle
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * r * eye, sin(angle) * r * eye);
	}
	glEnd();

	glPopMatrix();

	//Mouth
	glPushMatrix();

	glTranslatef(cx, cy - (r * 0.5), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);  // Blue

	glVertex2f(-10, 0);       // Center of circle
	glVertex2f(10, 0);

	glEnd();

	glPopMatrix();


	glFlush();
}

void buttonHover(button btn)
{					  
	if (btn.isHover)
	{
		rgb border = { 0.7f, 0.7f, 0.7f };
		rgb fill = { 0.9f, 0.9f, 0.9f };

		drawBox(btn.cx_bot_left, btn.cy_bot_left, btn.cx_top_right, btn.cy_top_right, border, fill);

		int cx = (btn.cx_bot_left + btn.cx_top_right) / 2;
		int cy = (btn.cy_bot_left + btn.cy_top_right) / 2;

		drawSmile(cx, cy, 25);
	}
	else
	{
		rgb border = { 0.7f, 0.7f, 0.7f };
		rgb fill = { 0.85f, 0.85f, 0.85f };

		drawBox(btn.cx_bot_left, btn.cy_bot_left, btn.cx_top_right, btn.cy_top_right, border, fill);

		int cx = (btn.cx_bot_left + btn.cx_top_right) / 2;
		int cy = (btn.cy_bot_left + btn.cy_top_right) / 2;

		drawSmile(cx, cy, 25);
	}
	
}

void buttonPressing(button btn)
{
	rgb border = { 0.7f, 0.7f, 0.7f };
	rgb fill = { 0.0f, 0.5f, 0.0f };

	drawBox(btn.cx_bot_left, btn.cy_bot_left, btn.cx_top_right, btn.cy_top_right, border, fill);

	int cx = (btn.cx_bot_left + btn.cx_top_right) / 2;
	int cy = (btn.cy_bot_left + btn.cy_top_right) / 2;

	drawSmile(cx, cy, 25);
}

button drawButtonSmile(float cx, float cy, float r)
{
	int padding = 5;

	smile = {
		cx - r - padding,
		cy - r - padding,
		cx + r + padding,
		cy + r + padding
	};

	rgb border = { 0.7f, 0.7f, 0.7f };
	rgb fill = { 0.85f, 0.85f, 0.85f };

	drawBox(smile.cx_bot_left, smile.cy_bot_left, smile.cx_top_right, smile.cy_top_right, border, fill);

	drawSmile(cx, cy, r);	

	return smile;
}

