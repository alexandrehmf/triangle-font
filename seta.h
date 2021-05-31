struct seta
{
	float pontos[2][2];
};

void drawSeta(struct seta s)
{
	float delta[2];
	delta[0] = s.pontos[1][0]-s.pontos[0][0];
	delta[1] = s.pontos[1][1]-s.pontos[0][1];
	
	float cross[2];
	cross[0] = delta[1]*0.03;
	cross[1] = -delta[0]*0.03;
	
	glColor3f(.1f,.8f,.8f);
	glBegin(GL_TRIANGLES);
	glVertex2f(s.pontos[0][0]-cross[0]             ,s.pontos[0][1]-cross[1]             );
	glVertex2f(s.pontos[0][0]+cross[0]             ,s.pontos[0][1]+cross[1]             );
	glVertex2f(s.pontos[1][0]                      ,s.pontos[1][1]                      );
	glVertex2f(s.pontos[0][0]-cross[0]+delta[0]*.92,s.pontos[0][1]-cross[1]+delta[1]*.92);
	glVertex2f(s.pontos[0][0]+cross[0]+delta[0]*.92,s.pontos[0][1]+cross[1]+delta[1]*.92);
	glVertex2f(s.pontos[1][0]                      ,s.pontos[1][1]                      );
	glEnd();
}