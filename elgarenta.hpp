#pragma once

#include "./imgui/imgui.h"
#include "./imgui/backends/imgui_impl_glfw.h"
#include "./imgui/backends/imgui_impl_opengl3.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define MAX_JOBS 256

#pragma pack(push, 1)
namespace elgarenta {
    //lookup table for 8bit pixel -> 24bit pixel
    extern uint8_t coltable[256][3];
    typedef struct {
        int w, h;
        char *buffer;
        unsigned int texture;
        int size;
    } image_t;
    typedef struct {
        //1 - rectangle
        uint8_t job;
        uint16_t priority;
        int x, y;
        int sx, sy;
        uint8_t color;
        bool used = false;
    } job_t;
    void onError(int error, const char *description);
    class Instance {
            job_t render_jobs[MAX_JOBS];
            bool firstr = true;
            void render() {
                if(!firstr) glDeleteTextures(1, &render_instance.texture);

                //sort jobs by priority
                std::sort(render_jobs, render_jobs + MAX_JOBS, [](job_t const &l, job_t const &r) {return l.priority < r.priority;});

                //render
                char *render_buffer = (char *)malloc(renderw * renderh);
                int ii = 0;
                //while(ii < renderw * renderh) render_buffer[ii++] = 0;
                if(!render_buffer) return;

                int i = 0;
                while(i < MAX_JOBS){
                    if(render_jobs[i].used) {
                        printf("render job %d\n", render_jobs[i].job);
                        switch(render_jobs[i].job) {
                            case 0: { //square
                                int i1 = render_jobs[i1].x, i2 = render_jobs[i1].y;
                                while(i1 < (render_jobs[i1].x + render_jobs[i1].sx)) {
                                    while(i2 < (render_jobs[i1].y + render_jobs[i1].sy)) {
                                        int tmp = (render_jobs[i1].sx * ((render_jobs[i1].y + i2) - 1) + ((render_jobs[i1].x + i1) + 1) - 1);
                                        render_buffer[tmp] = render_jobs[i1].color;
                                        i2++;
                                    }
                                    i1++;
                                    i2 = render_jobs[i1].y;
                                }
                            }
                        }
                    }
                    i++;
                }
                render_instance = create_image(render_buffer, renderw, renderh);
                free(render_buffer);
                firstr = false;
            }
            void runner() {
                if(!glfwInit()) {
                    status[0] = 2;
                    return;
                }
                glfwSetErrorCallback(onError);
                #if defined(IMGUI_IMPL_OPENGL_ES2)
                    const char* glsl_version = "#version 100";
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
                #elif defined(__APPLE__)
                    const char* glsl_version = "#version 150";
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
                #else
                    const char* glsl_version = "#version 130";
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                #endif
                window = glfwCreateWindow(w, h, title, nullptr, nullptr);
                if(!window) {
                    status[0] = -1;
                    return;
                }
                glfwMakeContextCurrent(window);
                glfwSwapInterval(1);
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO(); (void)io;
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
                ImGui::StyleColorsClassic();
                ImGui_ImplGlfw_InitForOpenGL(window, true);
                ImGui_ImplOpenGL3_Init(glsl_version);

                ImVec4 cc = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

                while(!glfwWindowShouldClose(window)){
                    glfwPollEvents();
                    ImGui_ImplOpenGL3_NewFrame();
                    ImGui_ImplGlfw_NewFrame();
                    ImGui::NewFrame();

                    ImGui::Begin("Elgarenta Window", nullptr);
                    render();
                    ImGui::Image((void *)(intptr_t)render_instance.texture, ImVec2(render_instance.w * render_instance.size, render_instance.h * render_instance.size));
                    ImGui::End();

                    ImGui::Render();
                    glViewport(0, 0, w, h);
                    glClearColor(cc.x * cc.w, cc.y * cc.w, cc.z * cc.w, cc.w);
                    glClear(GL_COLOR_BUFFER_BIT);
                    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                    glfwSwapBuffers(window);
                }
                printf("Closing\n");
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();

                glfwDestroyWindow(window);
                glfwTerminate();

                status[0] = 2;
                return;
            }
        public:
            int w, h;
            int renderw, renderh;
            const char *title;
            GLFWwindow *window;
            int status[3];
            image_t render_instance;
            image_t create_image(char *buffer, int w, int h){
                image_t img;
                img.w = w;
                img.h = h;
                img.size = 6;
                img.buffer = buffer;
                glGenTextures(1, &img.texture);
                glBindTexture(GL_TEXTURE_2D, img.texture);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
                    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
                #endif
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB8, GL_UNSIGNED_BYTE, buffer);

                IM_ASSERT(true);

                return img;
            }
            int create_job(job_t j) {
                int ii = 0;
                while(ii < MAX_JOBS){
                    if(!render_jobs[ii].used) {
                        render_jobs[ii] = j;
                        render_jobs[ii].used = true;
                        return ii;
                    }
                    ii++;
                }
                return -1;
            }
            void update_job(int id, job_t j){
                render_jobs[id] = j;
                render_jobs[id].used = true;
            }
            void start(){
                std::thread thr(&Instance::runner, this);
                thr.detach();
            }
    };

    Instance create_instance(int w, int h, const char *title);
}
#pragma pack(pop)