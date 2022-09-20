#include "gamefield.h"



void ScreenToOpenGL(HWND hwnd, int x, int y, float* ox, float* oy) { 
	RECT rct;
	GetClientRect(hwnd, &rct);
	*ox = x / (float)rct.right * gamefield.getW();
	*oy = gamefield.getH() - y / (float)rct.bottom * gamefield.getH();
}

bool IsCellInMap(int x, int y) { 
	return (x >= 0) && (y >= 0) && (x <= gamefield.getH()) && (y <= gamefield.getW());

}

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	float theta = 0.0f;


	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = (LPCWSTR)"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;


	hwnd = CreateWindowEx(0,
		(LPCWSTR)"GLSample",
		TEXT("GEMS"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		512,
		512,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);





	EnableOpenGL(hwnd, &hDC, &hRC);


	while (!bQuit)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{


			glClearColor(0.0f, 0.7f, 1.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			gamefield.drawField(); 
			gamefield.swapGems(); 
			gamefield.CheckCombinations(); 
			gamefield.BlowUP(); 
			gamefield.BonusReColor(); 

			SwapBuffers(hDC);

			Sleep(200);
		}
	}


	DisableOpenGL(hwnd, hDC, hRC);


	DestroyWindow(hwnd);

	return int(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;


	case WM_LBUTTONDOWN:
	{
		POINTFLOAT pf;
		ScreenToOpenGL(hwnd, LOWORD(lParam), HIWORD(lParam), &pf.x, &pf.y);
		int x = int(pf.x);
		int y = int(pf.y);
		if (IsCellInMap(x, y)) {
			if (gamefield.getCell(x, y)->is[SELECT]) {
				gamefield.getCell(x, y)->is[SELECT] = false;
			}
			else {
				gamefield.getCell(x, y)->is[SELECT] = true;
			}
		}
	}


	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;


	*hDC = GetDC(hwnd);


	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);


	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}