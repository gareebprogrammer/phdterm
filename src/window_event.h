#ifndef TERM_WINDOW_EVENT
#define TERM_WINDOW_EVENT

#include <GLFW/glfw3.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    TERM_NONE,
    TERM_WINDOW_MOVED,
    TERM_WINDOW_RESIZED,
    TERM_WINDOW_CLOSED,
    TERM_WINDOW_REFRESH,
    TERM_WINDOW_FOCUSED,
    TERM_WINDOW_DEFOCUSED,
    TERM_WINDOW_ICONIFIED,
    TERM_WINDOW_UNICONIFIED,
    TERM_FRAMEBUFFER_RESIZED,
    TERM_BUTTON_PRESSED,
    TERM_BUTTON_RELEASED,
    TERM_CURSOR_MOVED,
    TERM_CURSOR_ENTERED,
    TERM_CURSOR_LEFT,
    TERM_SCROLLED,
    TERM_KEY_PRESSED,
    TERM_KEY_REPEATED,
    TERM_KEY_RELEASED,
    TERM_CODEPOINT_INPUT,
    TERM_MONITOR_CONNECTED,
    TERM_MONITOR_DISCONNECTED,
#if GLFW_VERSION_MINOR >= 1
    TERM_FILE_DROPPED,
#endif
#if GLFW_VERSION_MINOR >= 2
    TERM_JOYSTICK_CONNECTED,
    TERM_JOYSTICK_DISCONNECTED,
#endif
#if GLFW_VERSION_MINOR >= 3
    TERM_WINDOW_MAXIMIZED,
    TERM_WINDOW_UNMAXIMIZED,
    TERM_WINDOW_SCALE_CHANGED,
#endif
} TermEventType;


typedef struct TermEvent
{
    TermEventType type;
    union {
        GLFWwindow* window;
        GLFWmonitor* monitor;
        int joystick;
    }glfw_data;
    union {
        struct {
            int x;
            int y;
        } pos;
        struct {
            int width;
            int height;
        } size;
        struct {
            double x;
            double y;
        } scroll;
        struct {
            int key;
            int scancode;
            int mods;
        } keyboard;
        struct {
            int button;
            int mods;
        } mouse;
        unsigned int codepoint;
#if GLFW_VERSION_MINOR >= 1
        struct {
            char** paths;
            int count;
        } file;
#endif
#if GLFW_VERSION_MINOR >= 3
        struct {
            float x;
            float y;
        } scale;
#endif
    }data;
} TermEvent;


void TermEventInit();
void TermTrackWindow(GLFWwindow *window);
int TermNextEvent(TermEvent *evnt);
void TermFreeEvent(TermEvent *evnt);


#ifdef __cplusplus
    } 
#endif

#endif
