float cursorX, cursorY;

float verts[3][2];

void cursorInit()
{
	cursorX = 0;
	cursorY = 0;
	
	verts[0][0] = 0;
	verts[0][1] = 0.057f;
	verts[1][0] = 0.05f;
	verts[1][1] = -0.028f;
	verts[2][0] = -0.05f;
	verts[2][1] = -0.028f;
}

void cursorUpdate(float x, float y)
{
	//cursorX = 2*(x/windowWidth)-1.0f;
	//cursorY = 2*(-y/windowHeight)+1.0f;
	cursorX = 2*(x/512)-1.0f;
	cursorY = 2*(-y/512)+1.0f;
}

void cursorDraw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(.8f,.8f,.1f);
	glVertex2f(cursorX+verts[0][0],cursorY+verts[0][1]);
	glVertex2f(cursorX+verts[1][0],cursorY+verts[1][1]);
	glVertex2f(cursorX+verts[2][0],cursorY+verts[2][1]);
	glEnd();
}