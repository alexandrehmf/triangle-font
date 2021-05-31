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

void drawTriSel(triangle_selection * sel, float s0, float t)
{
	if(sel->a)
	{
		drawMark(sel->a->mrk,t,s0+((s0/3) * sin(15*t)));
	}
	if(sel->b)
	{
		drawMark(sel->b->mrk,t,s0+((s0/3) * sin(15*t)));
	}
	if(sel->c)
	{
		drawMark(sel->c->mrk,t,s0+((s0/3) * sin(15*t)));
	}
}

vertex * add_vert(letter *toLetter,float x, float y)
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
	return (vertp);
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
	if ((sel->a == NULL) |
	    (sel->b == NULL) |
		(sel->c == NULL) )
	{
		return;	
	}
	
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

void remove_tri(letter * fromLetter, triangle_selection * sel)
{
	if ((sel->a == NULL) |
	    (sel->b == NULL) |
		(sel->c == NULL) |
		(fromLetter->nt == 0))
	{
		return;	
	}
	
	tri * t = fromLetter->firstt;
	
	while (t)
	{
		if (    ( (t->a == sel->a) || (t->a == sel->b) || (t->a == sel->c) ) &&
			    ( (t->b == sel->a) || (t->b == sel->b) || (t->b == sel->c) ) &&
				( (t->c == sel->a) || (t->c == sel->b) || (t->c == sel->c) )  )
		{
			break;
		}
		t = t->next;
	}
	
	if (t)
	{
		if (t->previous)
		{
			t->previous->next = t->next;
		}
		else
		{
			fromLetter->firstt = t->next;
		}
		
		if (t->next)
		{
			t->next->previous = t->previous;
		}
		else
		{
			fromLetter->lastt = t->previous;
		}
		
		fromLetter->nt--;
		free(t);
	}
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

void writeLetter(letter * L, FILE * f, char name)
{
	fprintf(f,"a%ca\n", name);
	fprintf(f,"v\n");
	for(vertex* v = L->firstv ; v != NULL ; v = v->next)
	{
		fprintf(f,"%f %f\n",v->mrk.pos.x,v->mrk.pos.y);
	}
	fprintf(f,"t\n");
	for(tri * t = L->firstt; t != NULL; t=t->next)
	{
		int n = 1;
		for(vertex * v = t->a; v->previous != NULL; v = v->previous)
		{
			n++;
		}
		fprintf(f,"%d ",n);
		n = 1;
		for(vertex * v = t->b; v->previous != NULL; v = v->previous)
		{
			n++;
		}
		fprintf(f,"%d ",n);
		n = 1;
		for(vertex * v = t->c; v->previous != NULL; v = v->previous)
		{
			n++;
		}
		fprintf(f,"%d\n",n);
	}
}

void readLetter(letter * L, FILE * f)
{
	fscanf(f, "v");
	
	int r;
	float tx, ty;
	while((r = fscanf(f,"%f %f", &tx, &ty))!=0)
	{
		add_vert(L,tx,ty);
	}
	
	fscanf(f, "t");
	
	int a,b,c;
	triangle_selection selection = create_tri_selection();
	while((r = fscanf(f,"%d %d %d",&a,&b,&c)) > 0)
	{
		printf("r é %d\n",r);
		vertex * V = L->firstv;
		for(int n = a; n > 1; n--)
		{
			V=V->next;
		}
		selection.a = V;
		
		V = L->firstv;
		for(int n = b; n > 1; n--)
		{
			V=V->next;
		}
		selection.b = V;
		
		V = L->firstv;
		for(int n = c; n > 1; n--)
		{
			V=V->next;
		}
		selection.c = V;
		
		add_tri(L,&selection);
	}
	
}

void save_font(letter * font)
{
	FILE * f = fopen("default","w");
	
	for (int i = 0; i < 255; i++)
	{
		if(i == 26) continue;
		writeLetter(&(font[i]),f,i);
	}
	
	fclose(f);
}

void load_font(letter * font)
{
	FILE * f = fopen("default","r");
	
	int r,a,b,d;
	char c;
	getc(f);
	r=0;
	while( (c = (char)getc(f)) != -1 )
	{
		a=getc(f);
		b=getc(f);
		printf("%d reading letter %d - %c\n",(int)c,c,c);
		readLetter(&(font[c]),f);
		d=getc(f);
	}
	
	fclose(f);
}