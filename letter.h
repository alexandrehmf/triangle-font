//#include "mark.h"

typedef struct vertex
{
	struct vertex * previous;
	struct vertex * next;
	mark mrk;
} vertex;

typedef struct tri
{
	vertex * a;
	vertex * b;
	vertex * c;
	
	struct tri * previous;
	struct tri * next;
} tri;

typedef struct
{
	int nv;
	vertex * firstv;
	vertex * lastv;
	
	int nt;
	tri * firstt;
	tri * lastt;
} letter;

typedef struct triangle_selection
{
	vertex * a;
	vertex * b;
	vertex * c;
}triangle_selection;

typedef enum {a,b,c} vert_slot;

letter create_letter()
{
  	letter inQuestion;
	
	inQuestion.nv = 0;
	inQuestion.firstv = NULL;
	inQuestion.lastv = NULL;
	
	inQuestion.nt = 0;
	inQuestion.firstt = NULL;
	inQuestion.lastt = NULL;
	
	return(inQuestion);
}

triangle_selection create_tri_selection()
{
	triangle_selection selection;
	selection.a=NULL;
	selection.b=NULL;
	selection.c=NULL;
	return(selection);
}

void add_vert(letter *toLetter,float x, float y)
{
	vertex * vertp = malloc(sizeof(vertex));
	vertp->mrk.pos.x = x;
	vertp->mrk.pos.y = y;
	if(toLetter->nv == 0)
	{
		vertp->previous = NULL;
		vertp->next = NULL;
		toLetter->firstv = vertp;
		toLetter->lastv = vertp;
	}
	else
	{
		vertp->previous = toLetter->lastv;
		vertp->next = NULL;
		toLetter->lastv->next = vertp;
		toLetter->lastv = vertp;
	}
	toLetter->nv++;
}

void drawVerts(letter L)
{
	vertex *vert = L.firstv;
	while(vert)
	{
		drawMark(vert->mrk,0,0.05);
		vert = vert->next;
	}
}

void select_vert(triangle_selection * selection, vert_slot slot, vertex * vert)
{
	switch(slot)
	{
		case a:
		{
			selection->a = vert;
		}break;
		case b:
		{
			selection->b = vert;
		}break;
		case c:
		{
			selection->c = vert;
		}break;
	}
}

void add_tri(letter * toLetter, triangle_selection * sel)
{
	tri * triptr = malloc(sizeof(tri));
	triptr->a = sel->a;
	triptr->b = sel->b;
	triptr->c = sel->c;
	
	if(toLetter->nt == 0)
	{
		triptr->previous = NULL;
		triptr->next = NULL;
		toLetter->firstt = triptr;
		toLetter->lastt = triptr;
		
		toLetter->nt++;
	}
	else
	{
		tri * ttp = toLetter->firstt;
		int repeated = 0;
		while(ttp != NULL)
		{
			if(  ( (ttp->a == sel->a) || (ttp->a == sel->b) || (ttp->a == sel->c) ) &&
			     ( (ttp->b == sel->a) || (ttp->b == sel->b) || (ttp->b == sel->c) ) &&
				 ( (ttp->c == sel->a) || (ttp->c == sel->b) || (ttp->c == sel->c) )  )
			{
				repeated = 1;
				break;
			}
			ttp = ttp->next; 
		}
		if(repeated == 0)
		{
			triptr->previous = toLetter->lastt;
			triptr->next = NULL;
			toLetter->lastt->next=triptr;
			toLetter->lastt=triptr;
			toLetter->nt++;
		}
	}
	
	return;
}

void drawTris(letter L)
{
	tri * ttp = L.firstt;
	while(ttp)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.15,0.15);
		glVertex2f(ttp->a->mrk.pos.x,ttp->a->mrk.pos.y);
		glVertex2f(ttp->b->mrk.pos.x,ttp->b->mrk.pos.y);
		glVertex2f(ttp->c->mrk.pos.x,ttp->c->mrk.pos.y);
		glEnd();
		ttp = ttp->next;
	}
}

vertex* choose(float x, float y, letter * l)
{
	vertex * v = l->firstv;
	while(v != NULL)
	{
		if(is_inside(x,y,v->mrk.pos,0.05))
		{
			return v;
		}
		v = v->next;
	}
	return NULL;
	
}

