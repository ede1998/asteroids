/*                                         *
 * file: GL-Window.h                       *
 * author: Erik Hennig                     *
 * date: 24.12.2016                        *
 * abstract: definition of GL-window class *
 *                                         */

#pragma once

#include <SDL2/SDL.h>
#include <string>

typedef void (*inpmouse)(bool, bool, int, int);

class GL_window
{
public:
  GL_window(int w, int h, inpmouse in, int x = 0, int y = 0);
  virtual ~GL_window();
  bool create(double left, double right, double bottom, double top);
  bool destroy();
  void setResolution(const int w, const int h);
  void setCaption(const std::string caption);
  void refresh_window();
  bool check_msgs();
  void clear_window();
  SDL_GLContext getContext();
  

private:
  int _height;
  int _width;
  int _positionx;
  int _positiony;
  SDL_Window * _window;
  SDL_GLContext _glc;
  std::string _caption;
  inpmouse _inputfunction;
  bool _mleft;
  bool _mright;
  int _mx, _my;
  
};
