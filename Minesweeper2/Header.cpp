#include "Header.h"

button smile = { 0,0,0,0 };

const char s0[18] = "Beginner";
const char s1[18] = "Normal";
const char s2[18] = "Advanced";

rgb border_array[3] = {
	{ 0, 0.75f, 0 },
	{ 1.0f, 0.8f, 0.1f },
	{ 1, 0, 0 },
};

rgb fill_array[3] = {
	{ 1, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 1 }
};

rgb hover_array[3] = {
	{ 0.55f, 1, 0.55f },
	{ 1, 1, 0.55f },
	{ 1, 0.8f, 0.55f }
};

rgb color_array[3] = {
	{ 0, 0.5f, 0 },
	{ 1.0f, 0.45f, 0.0f },
	{ 0.95f, 0, 0 },
};

button modeBtn[3] = {
	{ 1, screenH - 25, screenW / 3, screenH - 1 },
	{ screenW / 3 + 1, screenH - 25, screenW * 2 / 3 + 1, screenH - 1 },
	{ screenW * 2 / 3 + 2, screenH - 25, screenW, screenH - 1 }
};

int pad_left[3] = {
	(modeBtn[0].cx_top_right - modeBtn[0].cx_bot_left - 63) / 2,
	(modeBtn[1].cx_top_right - modeBtn[1].cx_bot_left - 45) / 2,
	(modeBtn[2].cx_top_right - modeBtn[2].cx_bot_left - 64) / 2
};

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

void buttonHover(button btn, rgb border, rgb fill, rgb text, const char *s, int pad_left)
{
	if (btn.isHover)
	{
		drawBox(btn.cx_bot_left, btn.cy_bot_left, btn.cx_top_right, btn.cy_top_right, border, fill);

		int cx = (btn.cx_bot_left + btn.cx_top_right) / 2;
		int cy = (btn.cy_bot_left + btn.cy_top_right) / 2;

		drawString(s, btn.cx_bot_left, btn.cy_bot_left, text, pad_left);
	}
	else
	{
		fill = { 1.0f, 1.0f, 1.0f };

		drawBox(btn.cx_bot_left, btn.cy_bot_left, btn.cx_top_right, btn.cy_top_right, border, fill);

		int cx = (btn.cx_bot_left + btn.cx_top_right) / 2;
		int cy = (btn.cy_bot_left + btn.cy_top_right) / 2;

		drawString(s, btn.cx_bot_left, btn.cy_bot_left, text, pad_left);
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

void drawString(const char *s, int cx, int cy, rgb color, int padding_left)
{
	int len = (int)strlen(s);

	int padding_bot = 7;

	glColor3f(color.r, color.g, color.b);
	glRasterPos2i(cx + padding_left, cy + padding_bot);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);

		if (isDevMode)
			printf("%c", s[i]);

	}

	glFlush();
}

void drawModeBtn()
{

	for (int i = 0; i < 3; i++)
	{
		drawBox(modeBtn[i].cx_bot_left, modeBtn[i].cy_bot_left, modeBtn[i].cx_top_right, modeBtn[i].cy_top_right, border_array[i], fill_array[i]);
	}
	
	drawString(s0, modeBtn[0].cx_bot_left, modeBtn[0].cy_bot_left, color_array[0], pad_left[0]);

	drawString(s1, modeBtn[1].cx_bot_left, modeBtn[1].cy_bot_left, color_array[1], pad_left[1]);

	drawString(s2, modeBtn[2].cx_bot_left, modeBtn[2].cy_bot_left, color_array[2], pad_left[2]);

}