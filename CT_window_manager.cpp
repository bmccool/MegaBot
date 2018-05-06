#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "CT_window_manager.hpp"


#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"

// The Keycode to be sent.
// A full list of available codes can be found in /usr/inclucde/X11/keysymdef.h

using namespace std;

XKeyEvent createKeyEvent(Display *display,
                        Window &win,
                        Window &winRoot,
                        bool press,
                        int keycode,
                        int modifiers)
{
    XKeyEvent event;

    event.display     = display;
    event.window      = win;
    event.root        = winRoot;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = true;
    event.state       = modifiers;

    if (press)
    {
        event.type = KeyPress;
    }
    else
    {
        event.type = KeyRelease;
    }
    return event;
}
int catcher( Display *disp, XErrorEvent *xe )
{
        printf( "Something had happened, bruh.\n" );
        return 0;
}

Window *list(Display *disp, unsigned long *len)
{
    Atom prop = XInternAtom(disp, "_NET_CLIENT_LIST", False), type;
    int form;
    unsigned long remain;
    unsigned char *list;

    XGetWindowProperty(disp, XDefaultRootWindow(disp), prop, 0, 1024, False, XA_WINDOW,
                            &type, &form, len, &remain, &list);
    return (Window *)list;
}
char *name(Display *disp, Window window)
{
    Atom prop = XInternAtom(disp, "WM_NAME", False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;

    XGetWindowProperty(disp, window, prop, 0, 1024, False, AnyPropertyType,
                            &type, &form, &len, &remain, &list);
    return (char*)list;
}

unsigned long int get_nes_window(void)
{
    LOG_SCOPE_FUNCTION(INFO);

    Display *disp;
    Window *wlist;
    unsigned long len;
    char *wname;
    bool found = false;

    LOG_S(INFO) << "Opening display"; 
    disp = XOpenDisplay(NULL);
    wlist = (Window*)list(disp, &len);

    LOG_S(INFO) << "Setting error handler";
    XSetErrorHandler( catcher ); // <-- inserted to set error handler

    int i;
    unsigned long int nes_index;
    LOG_S(INFO) << "Looking for handler";
    for(i = 0; i < (int)len; i++){
        VLOG_SCOPE_F(1, "Iteration %d", i);
        wname = name(disp, wlist[i]);
        LOG_S(INFO) << "wname: " << wname;
        if (wname[0] == 'F')
        {
            LOG_S(INFO) << "Found handler: " << wname << " index: " << i;
            nes_index = i;
            found = true;
        }
        free(wname);
    }
    LOG_S(INFO) << "Checked all windows, window was found: " << found;

    XSetErrorHandler( NULL ); // <-- restore the default error handler
    if (found == true)
        return wlist[nes_index];
    return 0; // TODO Need better return strategy here.  Maybe return handle by ref and an error code by val
}

int send_key(const char* keycode, key_action_t action, unsigned long int window_id)
{
    char buffer[50];
    
    // Grab focus of the window
    sprintf(buffer, "xdotool windowfocus --sync %lu", window_id);
    system(buffer);
    
    // Send the key action
    switch (action) 
    {
        case KEY_PRESS:
            sprintf(buffer, "xdotool keydown %s", keycode);
            break;
        case KEY_RELEASE:
            sprintf(buffer, "xdotool keyup %s", keycode);
            break;
        case KEY_PRESS_RELEASE:
            sprintf(buffer, "xdotool key %s", keycode);
            break;
        default:
            return CT_ERROR;  // The command was not sent a valid key action!
    }

    system(buffer);
    
    return 0;
}

