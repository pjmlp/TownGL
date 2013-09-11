/* townwnd.cpp - OpenGL OS glue for Windows.
* Copyright (C) 2012 Paulo Pinto
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
*/

#define STRICT
#include <windows.h>
#include <windowsx.h>

#include "glos.h"
#include <GL/glew.h>


#include "town.h"


/*** Variáveis globais ***/
static HWND  ghWnd;
HDC   ghDC;
static HGLRC ghRC;


// window class name
static LPCWSTR CLASS_NAME = L"TownClass";

// window name
static LPCWSTR CAPTION_NAME = L"TownGL";


/*** Protótipos das funções privadas ***/
static LRESULT CALLBACK Town_WndProc (HWND hwnd, UINT uMsg,WPARAM wParam, LPARAM lParam);
static BOOL Town_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
static void Town_OnSize(HWND hwnd, UINT state, int cx, int cy);
static void Town_OnPaint(HWND hwnd);
static void Town_OnDestroy (HWND hwnd);
static void Town_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
static void Town_OnChar(HWND hwnd, TCHAR ch, int cRepeat);
static BOOL SetupPixelFormat (HDC hdc);



/*
 * Função de tratamento da janela
 */
LRESULT CALLBACK Town_WndProc (HWND hwnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
  switch(uMsg) {
    HANDLE_MSG (hwnd, WM_CREATE, Town_OnCreate);

    HANDLE_MSG (hwnd, WM_SIZE, Town_OnSize);

    HANDLE_MSG (hwnd, WM_PAINT, Town_OnPaint);

    HANDLE_MSG (hwnd, WM_DESTROY, Town_OnDestroy);

    HANDLE_MSG (hwnd, WM_KEYDOWN, Town_OnKey);

    HANDLE_MSG (hwnd, WM_CHAR, Town_OnChar);

    default:
      return DefWindowProc(hwnd,uMsg,wParam,lParam);
  }
}

/*** Funções privadas ***/

/*
 * Processa a mensagem de criação da janela.
 */
static BOOL Town_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
  RECT rect;

  ghDC = GetDC(hwnd);
  if (!SetupPixelFormat(ghDC))
    PostQuitMessage (0);

   ghRC = wglCreateContext(ghDC);
   wglMakeCurrent(ghDC, ghRC);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
      return FALSE;
  }

   GetClientRect(hwnd, &rect);
   initializeGL ();

   return TRUE;
}

/*
 * Actualiza a janela de dimensão
 */
static void Town_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
  OnResize (cx, cy);
}


/*
 * Processa as mensagens de pintura.
 */
static void Town_OnPaint(HWND hwnd)
{
  PAINTSTRUCT ps;
  
  BeginPaint (hwnd, &ps);
  EndPaint (hwnd, &ps);
}

/*
 * Processa a mensagem WM_DESTROY
 */
static void Town_OnDestroy (HWND hwnd)
{
  if (ghRC)
    wglDeleteContext(ghRC);
  
  if (ghDC)
    ReleaseDC(hwnd, ghDC);

  PostQuitMessage (0);
}



/*
 * Processa a mensagem WM_CHAR
 * Permite rodar a imagem.
 */
static void Town_OnChar(HWND hwnd, TCHAR ch, int cRepeat)
{
  switch (ch) {
    case 'p' : OnPKey ();
               break;

    case 'v' : OnVKey ();
               break;

    case 'l' : OnLKey ();
               break;

    case 'a' : OnIncKey ();
               break;

    case 'z' : OnDecKey ();
               break;
  }
}

/*
 * Processa a mensagem WM_WMKEYDOWN
 * Permite rodar a imagem.
 */
static void Town_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
  switch (vk) {
    case VK_UP : OnUpKey ();
                 break;

    case VK_DOWN : OnDownKey ();
                   break;

  }
}



/*
 * Escolhe o formato dos pixeis
 */
static BOOL SetupPixelFormat (HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd, *ppfd;
  int pixelformat;

  ppfd = &pfd;

  ZeroMemory (ppfd, sizeof(PIXELFORMATDESCRIPTOR));
  ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
  ppfd->nVersion = 1;
  ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | 
						      PFD_DOUBLEBUFFER;
  ppfd->dwLayerMask = PFD_MAIN_PLANE;
  ppfd->iPixelType = PFD_TYPE_RGBA;
  ppfd->cColorBits = 8;
  ppfd->cDepthBits = 16;
  ppfd->cAccumBits = 0;
  ppfd->cStencilBits = 0;

  pixelformat = ChoosePixelFormat(hdc, ppfd);

  if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 ) {
    MessageBox(NULL, L"ChoosePixelFormat failed", L"Error", MB_OK);
    return FALSE;
  }

  if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) {
    MessageBox(NULL, L"SetPixelFormat failed", L"Error", MB_OK);
    return FALSE;
  }

  return TRUE;
}



/*
 * Initializes the application by registering the window class
 * for the given instance.
 */

static BOOL InitApplication(HINSTANCE hInstance)
{
   WNDCLASS wc;
   
   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = (WNDPROC) Town_WndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = 0;
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
   wc.lpszMenuName = NULL;
   wc.lpszClassName = CLASS_NAME;

   return RegisterClass(&wc);
}


/*
 * Starts this window instance.
 */
static BOOL InitInstance(HINSTANCE hInstance, int CmdShow)
{
  HWND hWnd;

  hWnd = CreateWindow(CLASS_NAME,
                      CAPTION_NAME,
                      WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                      CW_USEDEFAULT,
                      CW_USEDEFAULT,
                      CW_USEDEFAULT,
                      CW_USEDEFAULT,
                      NULL,
                      NULL,
                      hInstance,
                      NULL);
  if(!hWnd)
    return FALSE;


  ShowWindow(hWnd, CmdShow);
  UpdateWindow(hWnd);

  return TRUE;

}




/*
 * Windows entry point
 */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrev, LPSTR CmdLine, int CmdShow)
{
  MSG msg;

  if(!InitApplication (hInstance))
    return FALSE;
  
  if(!InitInstance (hInstance, CmdShow))
    return FALSE;

  while (TRUE) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) {
      if (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      else
        return TRUE;
    }
    else {
      MainLoop ();
      SwapBuffers (ghDC);
    }
  }
  
  return msg.wParam;
}


    




  

 
