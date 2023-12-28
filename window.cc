#include "window.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

Xwindow::Xwindow(int width, int height) : width {width}, height {height}, needsRedraw {true} {
    d = XOpenDisplay(NULL);

    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }

    s = DefaultScreen(d);

    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    buffer = XCreatePixmap(d, w, width, height, DefaultDepth(d, s));
    gc = XCreateGC(d, buffer, 0, (XGCValues *)0);

    // Set up colours
    XColor xcolour;
    Colormap cmap = DefaultColormap(d, DefaultScreen(d));;
    char color_vals[11][10] = {"white", "black", "red", "green", "blue", "gray", "yellow", "cyan", "magenta", "orange", "purple"};

    for (int i = 0; i < 11; ++i) {
        XParseColor(d, cmap, color_vals[i], &xcolour);
        XAllocColor(d, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

    XSetForeground(d, gc, colours[Black]);

    // Make window non-resizeable
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d, True);
    usleep(1000);

    // Setup
    XSetForeground(d, gc, colours[White]);
    XFillRectangle(d, buffer, gc, 0, 0, width, height);
}

Xwindow::~Xwindow() {
    XFreePixmap(d, buffer);
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, buffer, gc, x, y, width, height);
    needsRedraw = true;
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XDrawString(d, buffer, gc, x, y, msg.c_str(), msg.length());
    needsRedraw = true;
}

void Xwindow::drawLine(int x1, int y1, int x2, int y2) {
    XSetForeground(d, gc, colours[Black]);
    XDrawLine(d, buffer, gc, x1, y1, x2, y2);
    needsRedraw = true;
}

void Xwindow::swapBuffers() {
    if (needsRedraw) {
        XCopyArea(d, buffer, w, gc, 0, 0, width, height, 0, 0);
        XFlush(d);
        needsRedraw = false;
    }
}

void Xwindow::setFont(const string &fontName) {
    Font font = XLoadFont(d, fontName.c_str());
    if (font == 0) {
        cerr << "Unable to load font " << fontName << endl;
        return;
    }
    XSetFont(d, gc, font);
}

void Xwindow::setTextColor(unsigned long color) {
    XSetForeground(d, gc, color);
}
