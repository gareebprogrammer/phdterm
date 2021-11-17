#include <glad/glad.h>
#include "term_window.h"
#include "debug_print.h"

#ifdef __cplusplus
    extern "C" { 
#endif

#if _DEBUG
inline static void PrintGLInfo()
{
    const unsigned char *version = glGetString(GL_VERSION);
    const unsigned char *vendor = glGetString(GL_VENDOR);
    const unsigned char *renderer = glGetString(GL_RENDERER);
    debug_print("GL version: %s\nGL vendor: %s\nGL Renderer: %s\n",version,vendor,renderer);
}
#else
inline static void PrintGLInfo();
#endif

inline static int glfw_gl_surface_create(GLFWwindow *window,uint32_t width,uint32_t height)
{
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        return 0;
    }
    glViewport(0,0,width,height);
    return 1;
}

int CreateTermWindow(struct TermWindow *window,uint32_t width,uint32_t height,const char *window_title,enum TermWindowHint hint)
{   
    if(!glfwInit()){
        debug_print("File:%s:%d glfw init failed\n",__FILE__,__LINE__);
        return 0;
    }
    window->m_window = glfwCreateWindow(width,height,window_title,NULL,NULL);
    if(!window->m_window){
        debug_print("File:%s:%d glfw window creation failed\n",__FILE__,__LINE__);
        glfwTerminate();
        return 0;
    }
    window->width = width;
    window->height = height;
    switch (hint)
    {
        case TERM_GL_WINDOW :{
            if(!glfw_gl_surface_create(window->m_window,width,height)){
                debug_print("File:%s:%d OpenGL context creation failed\n",__FILE__,__LINE__);
                glfwDestroyWindow(window->m_window);
                glfwTerminate();
                return 0;
            }
            PrintGLInfo();            
        }break;
        case TERM_VULKAN_WINDOW :{
            //TODO: create vulkan window
            debug_print("File:%s:%d Vulkan context creation still not implemented!\n",__FILE__,__LINE__);
            glfwDestroyWindow(window->m_window);
            glfwTerminate();
            return 0;
        }break;
        case TERM_NO_API :{
            //TODO: create no api window
            debug_print("File:%s:%d No api context creation still not implemented!\n",__FILE__,__LINE__);
            glfwDestroyWindow(window->m_window);
            glfwTerminate();
            return 0;
        }break;
        default:{
            // NOTE: for now opengl window is default surface;
             if(!glfw_gl_surface_create(window->m_window,width,height)){
                debug_print("File:%s:%d OpenGL context creation failed\n",__FILE__,__LINE__);
                glfwDestroyWindow(window->m_window);
                glfwTerminate();
            }
            PrintGLInfo();
        }
    }
    return 1;
}
void WindowPollEvents()
{
    glfwPollEvents();
}

void WindowWaitEvents()
{
    glfwWaitEvents();
}

int DestroyWindow(struct TermWindow *window)
{   
    glfwDestroyWindow(window->m_window);
    glfwTerminate();
    return 0;
}

#ifdef __cplusplus
    } 
#endif