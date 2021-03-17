struct Desenho
{
	float pontos[20][3][2];
};

int target;
struct Desenho desenho;

void desenhoInit()
{
	target = 0;
}

void desenhoAddPoint(float x, float y)
{
	desenho.pontos[target/3][target%3][0]=2*(x/512)-1.0f;
	desenho.pontos[target/3][target%3][1]=2*(-y/512)+1.0f;
	target++;
	if(target == 60)
		target = 0;
}

void desenhoDraw()
{
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < (60 ); i++)
	{
		glVertex2f(desenho.pontos[i/3][i%3][0],desenho.pontos[i/3][i%3][1]);
	}
	glEnd();
}