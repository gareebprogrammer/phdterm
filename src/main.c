#include "term_window.h"
#include "window_event.h"
#include "debug_print.h"

int main(int argc,char *argv[]){
    struct TermWindow window;
    if(!CreateTermWindow(&window,700,700,"phdterm",TERM_GL_WINDOW)){
        return -1;
    }
    TermTrackWindow(window.m_window);
    TermEvent evnt;
    while(IsWindowOpen(&window)){
        glClear(GL_COLOR_BUFFER_BIT);
        WindowSwapBuffers(&window);
        glClearColor(1.0f, 0.0f, 0.0f,0.0f);
        WindowPollEvents();
        while(TermNextEvent(&evnt)){
            switch(evnt.type)
            {
               case TERM_WINDOW_MOVED : {
                   debug_print("Window moved\n");
               }break;
               case TERM_WINDOW_MAXIMIZED : {
                   debug_print("Window maximized\n");
               }break;
               case TERM_WINDOW_UNMAXIMIZED : {
                   debug_print("Window unmaximized\n");
               }break;
               case TERM_WINDOW_CLOSED : {
                   debug_print("Window close request\n");
                   CloseWindow(&window);
               }
            }
        }
    }
    DestroyWindow(&window);
    return 0;
}