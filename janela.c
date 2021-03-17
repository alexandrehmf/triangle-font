#include <windows.h>
//#include <GL\gl.h>

int running;

LRESULT CALLBACK MyWindowProc(
HWND hwnd,
UINT uMsg,
WPARAM wParam,
LPARAM lParam)
{
	switch(uMsg)
	{
		/*case WM_CREATE:
		{
			
		}break;
		case WM_PAINT:
		{
			
		}break;
		case WM_SIZE:
		{
			
		}break;
		*/
		case WM_MBUTTONDOWN:
		{
			printf("middle button down x:%d\n",LOWORD(lParam));
			printf("middle button down y:%d\n",HIWORD(lParam));
		}break;
		case WM_LBUTTONDOWN:
		{
			float X = LOWORD(lParam);
			float Y = HIWORD(lParam);
			onLMBD(X,Y);
		}break;
		case WM_MOUSEMOVE:
		{
			float X = LOWORD(lParam);
			float Y = HIWORD(lParam);
			onMouseMove(X,Y);
			printf("mouse x:%d",LOWORD(lParam));
			printf("mouse y:%d\n",HIWORD(lParam));
		}break;
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_SPACE:
				{
					onKeyDown(space);
				}break;
				case 0x57://w
				{
				}break;
				case 0x41://a
				{
					onKeyDown(ak);
				}break;
				case 0x53://s
				{
				}break;
				case 0x44://d
				{
				}break;
				case 0x58: //x
				{
				}break;
				case 0x5A: //z
				{
				}break;
				case 0x70://f1
				{
					onKeyDown(f1);
				}break;
				case 0x71: //f2
				{
					onKeyDown(f2);
				}break;
				case 0x72: //f3
				{
					onKeyDown(f3);
				}break;
			}
		
		printf("wparam:%d\n",wParam);
		printf("lparam:%x\n",lParam);
		}break;
		case WM_KEYUP:
		{
			switch(wParam)
			{
				case VK_SPACE:
				{
				}break;
				case 0x57://w
				{
				}break;
				case 0x41: //a
				{
				}break;
				case 0x53: //s
				{
				}break;
				case 0x44: //d
				{
				}break;
				case 0x58: //x
				{
				}break;
				case 0x5A: //z
				{
				}break;
			}
		}break;
		case WM_DESTROY:
		{
			running = 0;
		}break;
		default:
		{
			//printf("???");
			DefWindowProc(hwnd,uMsg,wParam,lParam);
		}break;
	}
}

int WinMain
(HINSTANCE hInstance,
 HINSTANCE hPrevInstance,
 LPSTR     lpCmdLine,
 int       nShowCmd)
{
	WNDCLASSEX myWindowClass = {};
	myWindowClass.cbSize = sizeof(WNDCLASSEX);
	myWindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	myWindowClass.hInstance = hInstance;
	myWindowClass.lpfnWndProc = MyWindowProc;
	LPCSTR classname = "windowclass";
	myWindowClass.lpszClassName = classname;
	
	RegisterClassEx(&myWindowClass);
	
	LPCSTR windowname = "janela";
	
	RECT windowRect;
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = windowWidth;
	windowRect.bottom = windowHeight;
	
	//DWORD  dwStyle = WS_BORDER|WS_VISIBLE|WS_THICKFRAME;
	DWORD  dwStyle = WS_VISIBLE|WS_OVERLAPPEDWINDOW;
	
	AdjustWindowRectEx(
	  &windowRect,
	  dwStyle,
	  0,//false
	  WS_EX_OVERLAPPEDWINDOW
	);
	
	printf("%d - left \n", windowRect.left);
	printf("%d - top \n", windowRect.top);
	printf("%d - right \n", windowRect.right);
	printf("%d - bottom \n", windowRect.bottom);
	
	HWND hwnd = CreateWindowEx(
	  WS_EX_OVERLAPPEDWINDOW,
	  classname,
	  windowname,
	  dwStyle,
	  1,
	  1,
	  windowRect.right - windowRect.left,
	  windowRect.bottom - windowRect.top,
	  NULL,
	  NULL,
	  hInstance,
	  NULL
	);
	
	RECT clRct;
	GetClientRect(hwnd,&clRct);
	printf("window client area origin and extent:\n%d\n%d\n%d\n%d\n",
	clRct.left,clRct.top,clRct.right,clRct.bottom);
	
	PIXELFORMATDESCRIPTOR pfd = { 
    sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
    1,                     // version number  
    PFD_DRAW_TO_WINDOW |   // support window  
    PFD_SUPPORT_OPENGL |   // support OpenGL  
    PFD_DOUBLEBUFFER,      // double buffered  
    PFD_TYPE_RGBA,         // RGBA type  
    24,                    // 24-bit color depth  
    0, 0, 0, 0, 0, 0,      // color bits ignored  
    0,                     // no alpha buffer  
    0,                     // shift bit ignored  
    0,                     // no accumulation buffer  
    0, 0, 0, 0,            // accum bits ignored  
    32,                    // 32-bit z-buffer  
    0,                     // no stencil buffer  
    0,                     // no auxiliary buffer  
    PFD_MAIN_PLANE,        // main layer  
    0,                     // reserved  
    0, 0, 0                // layer masks ignored  
	};
	
	HDC hdc = GetDC(hwnd);

	int  iPixelFormat;
	
	iPixelFormat = ChoosePixelFormat(hdc, &pfd);
	
	SetPixelFormat(hdc, iPixelFormat, &pfd);
	
	HGLRC context = wglCreateContext(hdc);
	
	int contextCurrent = wglMakeCurrent(hdc,context);
	
	GLint vp[4];
	glGetIntegerv( GL_VIEWPORT, vp );
	printf("viewport origin and extent:\n%d\n%d\n%d\n%d\n",vp[0],vp[1],vp[2],vp[3]);
	
	glClearColor(0.0f,0.4f,0.0f,1.0f);
	
	onInit();
	
	running = 1;
	MSG message;
	
	while(running)
	{		
        onUpdate();

		glClear(GL_COLOR_BUFFER_BIT);
		
		onDraw();
		
		SwapBuffers(hdc);
		
		while(PeekMessageA(&message,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		
	}
	
	wglMakeCurrent(NULL, NULL);
	ReleaseDC (hwnd, hdc);
	wglDeleteContext(context);
}