#include "vec2d.h"
#include <math.h>

#define PI 3.14159265

typedef struct {
	vec2d pos;
} mark;

void feedVec2d(vec2d vec)
{
	glVertex2f(vec.x,vec.y);
}

void drawMark(mark m,float offset,float size)
{
	glBegin(GL_TRIANGLES);
	glColor3f(.8f,.8f,.1f);
	float dif = (30.0/360.0)*2.0*PI;
	for(int i = 0; i < 3; i++)
	{
		float theta = (float)i*(2.0*PI/3.0);
		theta += offset;
		
		vec2d point = mkvec(cos(theta - dif),sin(theta - dif));
		feedVec2d(vpv2d(m.pos,scaleVec(point,size)));
		
		point = mkvec(cos(theta),sin(theta));
		feedVec2d(vpv2d(m.pos,scaleVec(point,size)));
		
		point = mkvec(cos(theta + dif),sin(theta + dif));
		feedVec2d(vpv2d(m.pos,scaleVec(point,size)));
	}
	glEnd();
}

int is_inside(float x, float y, vec2d v, float r)
{
	float dx = v.x-x;
	float dy = v.y-y;
	float s = sqrt((dx*dx)+(dy*dy));
	if(s<=r)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}