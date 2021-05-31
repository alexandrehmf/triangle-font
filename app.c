#include <stdio.h>
#include <GL\gl.h>

int windowWidth = 512;
int windowHeight = 512;

//#include "desenho.h"
#include "seta.h"
#include "mark.h"
#include "letter.h"

enum Key {f1,f2,f3,f5,f6,kq,kw,ke,ka,kd,space};
typedef enum Key Key;

enum Mode {marking,selecting,letterSelecting};
enum Mode mode;

struct seta s;
mark m;
float offset;
letter letra[255];
int selectedLetter;
vertex * selectedVertex;

triangle_selection tri_sel;
vert_slot slot;

float bufx = 0; 
float bufy = 0;
float xini, yini;

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
	
	for (int i = 0; i < 255; i++)
	{
		letra[i] = create_letter();
	}
	selectedLetter = 97;
	tri_sel = create_tri_selection();
	
	selectedVertex = NULL;
}

void onDraw()
{
	drawSeta(s);
	drawMark(m,offset,0.05);
	drawTriSel(&tri_sel,0.05,offset);
	drawVerts(letra[selectedLetter]);
	drawTris(letra[selectedLetter]);
}

void onMouseMove(float x,float y)
{
	bufx = 2*(x/512)-1.0f;
	bufy = 2*(-y/512)+1.0f;
	s.pontos[1][0] = bufx;
	s.pontos[1][1] = bufy;
	m.pos.x=bufx;
	m.pos.y=bufy;
	
	if (selectedVertex)
	{
		selectedVertex->mrk.pos.x = bufx + xini;
		selectedVertex->mrk.pos.y = bufy + yini;
	}
}

void onLMBD(float x,float y)//left mouse button
{
	float normscrnx = 2*(x/512)-1.0f;
	float normscrny = 2*(-y/512)+1.0f;
	
	switch(mode)
	{
		case marking:
		{
			selectedVertex = choose(normscrnx,normscrny,&(letra[selectedLetter]));
			if (selectedVertex == NULL)
			{
				selectedVertex = add_vert(&(letra[selectedLetter]), normscrnx, normscrny);
			}
			xini = selectedVertex->mrk.pos.x-normscrnx;
			yini = selectedVertex->mrk.pos.y-normscrny;
			
		}break;
		case selecting:
		{
			vertex * v = choose(normscrnx,normscrny,&(letra[selectedLetter]));
			if(v != NULL)
			{
				select_vert(&tri_sel,slot,v);
			}
		}break;
	}
	printf("left button down x:%d\n",x);
	printf("left button down y:%d\n",y);
}

void onLMBU(float x,float y)
{
	selectedVertex = NULL;
}

void onKeyDown(Key key)
{
	switch(mode)
	{
		case marking:
		{
			switch(key)
			{
				case f2:
				{
					mode = selecting;
				}break;
				case f3:
				{
					mode = letterSelecting;
				}break;
				case f5:
				{
					save_font(letra);
				}break;
				case f6:
				{
					load_font(letra);
				}break;
			}
		}break;
		case selecting:
		{
			switch(key)
			{
				case f1:
				{
					mode = marking;
				}break;
				case f3:
				{
					mode = letterSelecting;
				}break;
				case f5:
				{
					save_font(letra);
				}break;
				case f6:
				{
					load_font(letra);
				}break;
				case ka:
				{
					add_tri(&(letra[selectedLetter]), &tri_sel);
				}break;
				case kd:
				{
					remove_tri(&(letra[selectedLetter]), &tri_sel);
				}break;
				case kq:
				{
					slot = a;
				}break;
				case kw:
				{
					slot = b;
				}break;
				case ke:
				{
					slot = c;
				}break;
			}
		}break;
		case letterSelecting:
		{
			switch(key)
			{
				case f1:
				{
					mode = marking;
				}break;
				case f2:
				{
					mode = selecting;
				}break;
				case f5:
				{
					save_font(letra);
				}break;
				case f6:
				{
					load_font(letra);
				}break;
			}
		}break;
		default:
		{
			;
		}break;
	}
}

void onChar(char c)
{
	if (mode == letterSelecting)
	{
		selectedLetter = c;
		tri_sel.a = NULL;
		tri_sel.b = NULL;
		tri_sel.c = NULL;
	}
}

void onUpdate()
{
	offset += 0.005;
}

#include "janela.c"