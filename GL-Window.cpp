/*                                             *
 * file: GL-Window.cpp                         *
 * author: Erik Hennig                         *
 * date: 24.12.2016                            *
 * abstract: implementation of GL-window class *
 *                                             */
 
#include "GL-Window.h"
#include <SDL2/SDL_opengl.h>
#include <iostream>

GL_window::GL_window(int w, int h, inpmouse in, int x, int y) :
         _height    ( h ),
         _width     ( w ),
         _positionx ( x ),
         _positiony ( y ),
	 _window( nullptr ),
         _inputfunction ( in ),
         _mleft ( false ),
         _mright ( false ),
         _mx ( 0 ),
         _my ( 0 )
{

}

GL_window::~GL_window()
{
  destroy();
}

bool GL_window::create(double left, double right, double bottom, double top)
{
  //Try to intialize SDL video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "Fehler: Init" << std::endl << SDL_GetError() << std::endl;
    return false;
  }
  
  //if no window already exists create a new one
  if (_window != nullptr) return false;
  _window = SDL_CreateWindow(_caption.c_str(), _positionx, _positiony, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (_window == nullptr) 
  {
    std::cerr << "Fehler: CreateWindow" << std::endl << SDL_GetError() << std::endl;
    return false;
  }
  //Create rendering context
  if (_glc != nullptr) return false;
  _glc = SDL_GL_CreateContext(_window);
  if (_glc == nullptr) 
  {
    std::cerr << "Fehler: CreateGLContext" << std::endl << SDL_GetError() << std::endl;
    return false;
  }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(left, right, bottom, top, -1, 1);
  return true;
}

bool GL_window::destroy()
{
  if (_window)
    SDL_DestroyWindow(_window);
  if (_glc)
    SDL_GL_DeleteContext(_glc);
  if (SDL_WasInit(SDL_INIT_VIDEO))
    SDL_Quit();
  return true;
}

void GL_window::setResolution(const int w, const int h)
{
  _width = w;
  _height = h;
  if (_window)
    SDL_SetWindowSize(_window, _width, _height);
}

void GL_window::setCaption(const std::string caption)
{
  _caption = caption;
  if (_window)
    SDL_SetWindowTitle(_window, _caption.c_str());
}

void GL_window::refresh_window()
{
  SDL_GL_SwapWindow(_window);
}

void GL_window::clear_window()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
}

bool GL_window::check_msgs()
{ //TODO während drücken aktiv lassen
  SDL_Event event;
  bool moved = false, pressed = false;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        return false;
        break;
      case SDL_MOUSEMOTION:
        _mx = event.button.x;
        _my = event.button.y;
        moved = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        _mleft = event.button.button == SDL_BUTTON_LEFT;
        _mright = event.button.button == SDL_BUTTON_RIGHT;
        pressed = event.button.state == SDL_PRESSED;
        break;
      default:
        break;
    }
  }
  if (_mleft) { if (!pressed) {_mleft = false;}}
  if (_mright) { if (!pressed) {_mright = false;}}
  if ( _mleft || _mright || moved )
    _inputfunction(_mleft, _mright, _mx, _my);
  return true;
}
