#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

using namespace std;

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[11];

  // Additions
  int width;
  int height;
  Pixmap buffer;
  bool needsRedraw;

public:
  Xwindow(int width = 700, int height = 700);
  ~Xwindow();

  // Colours
 enum { White=0, Black, Red, Green, Blue, Gray, Yellow, Cyan, Magenta, Orange, Purple };

  void fillRectangle(int x, int y, int width, int height, int colour=Black);
  void drawString(int x, int y, string msg, int colour);
  void drawLine(int x1, int y1, int x2, int y2);
  void swapBuffers();
  void setFont(const string &fontName);
  void setTextColor(unsigned long color);
};

#endif
