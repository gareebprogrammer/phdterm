#include "window_event.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TERM_EVENT_QUEUE_SIZE 65535

struct TermQueue
{
    TermEvent events[TERM_EVENT_QUEUE_SIZE];
    size_t head;
    size_t tail;
};

static struct TermQueue term_queue = {0};


static char *TermStrDup(const char *str)
{
    const size_t len = strlen(str) + 1;
    char *result = (char *)malloc(len);
    memcpy(result,str,len);
    return result;
}

static TermEvent* term_new_event(void)
{
    TermEvent* event = term_queue.events + term_queue.head;
    term_queue.head = (term_queue.head + 1) % TERM_EVENT_QUEUE_SIZE;
    assert(term_queue.head != term_queue.tail);
    memset(event, 0, sizeof(TermEvent));
    return event;
}

static void term_window_pos_callback(GLFWwindow* window, int x, int y)
{
    TermEvent* event = term_new_event();
    event->type = TERM_WINDOW_MOVED;
    event->window = window;
    event->pos.x = x;
    event->pos.y = y;
}

static void term_window_size_callback(GLFWwindow* window, int width, int height)
{
    TermEvent* event = term_new_event();
    event->type = TERM_WINDOW_RESIZED;
    event->window = window;
    event->size.width = width;
    event->size.height = height;
}

static void term_window_close_callback(GLFWwindow* window)
{
    TermEvent* event = term_new_event();
    event->type = TERM_WINDOW_CLOSED;
    event->window = window;
}

static void term_window_refresh_callback(GLFWwindow* window)
{
    TermEvent* event = term_new_event();
    event->type = TERM_WINDOW_REFRESH;
    event->window = window;
}

static void term_window_focus_callback(GLFWwindow* window, int focused)
{
    TermEvent* event = term_new_event();
    event->window = window;

    if (focused)
        event->type = TERM_WINDOW_FOCUSED;
    else
        event->type = TERM_WINDOW_DEFOCUSED;
}

static void term_window_iconify_callback(GLFWwindow* window, int iconified)
{
    TermEvent* event = term_new_event();
    event->window = window;

    if (iconified)
        event->type = TERM_WINDOW_ICONIFIED;
    else
        event->type = TERM_WINDOW_UNICONIFIED;
}

static void term_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    TermEvent* event = term_new_event();
    event->type = TERM_FRAMEBUFFER_RESIZED;
    event->window = window;
    event->size.width = width;
    event->size.height = height;
}

static void term_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    TermEvent* event = term_new_event();
    event->window = window;
    event->mouse.button = button;
    event->mouse.mods = mods;

    if (action == GLFW_PRESS)
        event->type = TERM_BUTTON_PRESSED;
    else if (action == GLFW_RELEASE)
        event->type = TERM_BUTTON_RELEASED;
}

static void term_cursor_pos_callback(GLFWwindow* window, double x, double y)
{
    TermEvent* event = term_new_event();
    event->type = TERM_CURSOR_MOVED;
    event->window = window;
    event->pos.x = (int) x;
    event->pos.y = (int) y;
}

static void term_cursor_enter_callback(GLFWwindow* window, int entered)
{
    TermEvent* event = term_new_event();
    event->window = window;

    if (entered)
        event->type = TERM_CURSOR_ENTERED;
    else
        event->type = TERM_CURSOR_LEFT;
}

static void term_scroll_callback(GLFWwindow* window, double x, double y)
{
    TermEvent* event = term_new_event();
    event->type = TERM_SCROLLED;
    event->window = window;
    event->scroll.x = x;
    event->scroll.y = y;
}

static void term_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    TermEvent* event = term_new_event();
    event->window = window;
    event->keyboard.key = key;
    event->keyboard.scancode = scancode;
    event->keyboard.mods = mods;

    if (action == GLFW_PRESS)
        event->type = TERM_KEY_PRESSED;
    else if (action == GLFW_RELEASE)
        event->type = TERM_KEY_RELEASED;
    else if (action == GLFW_REPEAT)
        event->type = TERM_KEY_REPEATED;
}

static void term_char_callback(GLFWwindow* window, unsigned int codepoint)
{
    TermEvent* event = term_new_event();
    event->type = TERM_CODEPOINT_INPUT;
    event->window = window;
    event->codepoint = codepoint;
}

static void term_monitor_callback(GLFWmonitor* monitor, int action)
{
    TermEvent* event = term_new_event();
    event->monitor = monitor;

    if (action == GLFW_CONNECTED)
        event->type = TERM_MONITOR_CONNECTED;
    else if (action == GLFW_DISCONNECTED)
        event->type = TERM_MONITOR_DISCONNECTED;
}

#if GLFW_VERSION_MINOR >= 1
static void term_file_drop_callback(GLFWwindow* window, int count, const char** paths)
{
    TermEvent* event = term_new_event();
    event->type = TERM_FILE_DROPPED;
    event->window = window;
    event->file.paths = (char**) malloc(count * sizeof(char*));
    event->file.count = count;

    while (count--)
        event->file.paths[count] = TermStrDup(paths[count]);
}
#endif

#if GLFW_VERSION_MINOR >= 2
static void term_joystick_callback(int jid, int action)
{
    TermEvent* event = term_new_event();
    event->joystick = jid;

    if (action == GLFW_CONNECTED)
        event->type = TERM_JOYSTICK_CONNECTED;
    else if (action == GLFW_DISCONNECTED)
        event->type = TERM_JOYSTICK_DISCONNECTED;
}
#endif

#if GLFW_VERSION_MINOR >= 3
static void term_window_maximize_callback(GLFWwindow* window, int maximized)
{
    TermEvent* event = term_new_event();
    event->window = window;

    if (maximized)
        event->type = TERM_WINDOW_MAXIMIZED;
    else
        event->type = TERM_WINDOW_UNMAXIMIZED;
}

static void term_window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
    TermEvent* event = term_new_event();
    event->window = window;
    event->type = TERM_WINDOW_SCALE_CHANGED;
    event->scale.x = xscale;
    event->scale.y = yscale;
}
#endif

void TermInit(void)
{
    glfwSetMonitorCallback(term_monitor_callback);
#if GLFW_VERSION_MINOR >= 2
    glfwSetJoystickCallback(term_joystick_callback);
#endif
}

void TermTrackWindow(GLFWwindow* window)
{
    glfwSetWindowPosCallback(window, term_window_pos_callback);
    glfwSetWindowSizeCallback(window, term_window_size_callback);
    glfwSetWindowCloseCallback(window, term_window_close_callback);
    glfwSetWindowRefreshCallback(window, term_window_refresh_callback);
    glfwSetWindowFocusCallback(window, term_window_focus_callback);
    glfwSetWindowIconifyCallback(window, term_window_iconify_callback);
    glfwSetFramebufferSizeCallback(window, term_framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, term_mouse_button_callback);
    glfwSetCursorPosCallback(window, term_cursor_pos_callback);
    glfwSetCursorEnterCallback(window, term_cursor_enter_callback);
    glfwSetScrollCallback(window, term_scroll_callback);
    glfwSetKeyCallback(window, term_key_callback);
    glfwSetCharCallback(window, term_char_callback);
#if GLFW_VERSION_MINOR >= 1
    glfwSetDropCallback(window, term_file_drop_callback);
#endif
#if GLFW_VERSION_MINOR >= 3
    glfwSetWindowMaximizeCallback(window, term_window_maximize_callback);
    glfwSetWindowContentScaleCallback(window, term_window_content_scale_callback);
#endif
}

int TermNextEvent(TermEvent* event)
{
    memset(event, 0, sizeof(TermEvent));

    if (term_queue.head != term_queue.tail)
    {
        *event = term_queue.events[term_queue.tail];
        term_queue.tail = (term_queue.tail + 1) % TERM_EVENT_QUEUE_SIZE;
    }
    return event->type != TERM_NONE;
}

void TermFreeEvent(TermEvent* event)
{
#if GLFW_VERSION_MINOR >= 1
    if (event->type == TERM_FILE_DROPPED)
    {
        while (event->file.count--)
            free(event->file.paths[event->file.count]);

        free(event->file.paths);
    }
#endif
    memset(event, 0, sizeof(TermEvent));
}

#ifdef __cplusplus
    } 
#endif