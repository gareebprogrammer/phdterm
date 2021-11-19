#include "term_window.h"
#include "debug_print.h"
#include "gl_utils.h"

#ifdef __cplusplus
    extern "C" { 
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

int CreateTermWindow(struct TermWindow *window,uint32_t width,uint32_t height,const char *window_title,enum TermWindowType hint)
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
    window->window_type = hint;
    switch (hint)
    {
        case TERM_GL_WINDOW :{
            if(!glfw_gl_surface_create(window->m_window,width,height)){
                debug_print("File:%s:%d OpenGL context creation failed\n",__FILE__,__LINE__);
                glfwDestroyWindow(window->m_window);
                glfwTerminate();
                return 0;
            }
            if(GLVersion.major < 3 && GLVersion.minor < 3){
                debug_print("File:%s:%d Minimum opengl version 3.3 required\n",__FILE__,__LINE__);
            }
#if _DEBUG
        PrintGLInfo();
#endif
        }break;
        case TERM_VULKAN_WINDOW :{
            //TODO: create vulkan surface
            debug_print("File:%s:%d Vulkan context creation still not implemented!\n",__FILE__,__LINE__);
            glfwDestroyWindow(window->m_window);
            glfwTerminate();
            return 0;
        }break;
        case TERM_NO_API :{
            //TODO: create no api surface
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

void WindowSwapBuffers(struct TermWindow *window)
{
    glfwSwapBuffers(window->m_window);
}

int IsWindowOpen(struct TermWindow *window)
{
    if(!glfwWindowShouldClose(window->m_window)){
        return 1;
    }
    return 0;
}

void CloseWindow(struct TermWindow *window)
{
    glfwSetWindowShouldClose(window->m_window,1);
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