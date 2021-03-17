#include <stdio.h>
#include <GL\gl.h>

int windowWidth = 512;
int windowHeight = 512;

//#include "desenho.h"
#include "seta.h"
#include "mark.h"
#include "letter.h"

enum Key {f1,f2,f3,ak,space};
typedef enum Key Key;

enum Mode {marking,selecting};
enum Mode mode;

struct seta s;
mark m;
float offset;
letter letra;

triangle_selection tri_sel;
vert_slot slot;

float bufx = 0; 
float bufy = 0;

void onInit()
{
	mode = marking;
	slot = a;
	
	s.pontos[0][0] = 0;
	s.pontos[0][1] = 0;
	s.pontos[1][0] = 0;
	s.pontos[1][1] = 0;
	m.pos = mkvec(0,0);
	offset = 0.0;
	
	letra = create_letter();
	tri_sel = create_tri_selection();
}

void onDraw()
{
	drawSeta(s);
	drawMark(m,offset,0.05);
	drawVerts(letra);
	drawTris(letra);
}

void onMouseMove(float x,float y)
{
	bufx = 2*(x/512)-1.0f;
	bufy = 2*(-y/512)+1.0f;
	s.pontos[1][0] = bufx;
	s.pontos[1][1] = bufy;
	m.pos.x=bufx;
	m.pos.y=bufy;
}

void onLMBD(float x,float y)//left mouse button
{
	float normscrnx = 2*(x/512)-1.0f;
	float normscrny = 2*(-y/512)+1.0f;
	
	switch(mode)
	{
		case marking:
		{
			add_vert(&letra, normscrnx, normscrny);
		}break;
		case selecting:
		{
			vertex * v = choose(normscrnx,normscrny,&letra);
			if(v != NULL)
			{
				select_vert(&tri_sel,slot,v);
			}
		}break;
	}
	printf("left button down x:%d\n",x);
	printf("left button down y:%d\n",y);
}

void onKeyDown(Key key)
{
	switch(mode)
	{
		case marking:
		{
			switch(key)
			{
				case space:
				{
					mode = selecting;
				}break;
			}
		}break;
		case selecting:
		{
			switch(key)
			{
				case space:
				{
					mode = marking;
				}break;
				case ak:
				{
					add_tri(&letra, &tri_sel);
				}break;
				case f1:
				{
					slot = a;
				}break;
				case f2:
				{
					slot = b;
				}break;
				case f3:
				{
					slot = c;
				}break;
			}
		}break;
	}
}

void onUpdate()
{
	offset += 0.005;
}

#include "janela.c"