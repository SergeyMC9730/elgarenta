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
#define JOB_RECTANGLE 1

#pragma pack(push, 1)
namespace elgarenta {
    //lookup table for 8bit pixel -> 24bit pixel
    extern uint8_t coltable[256][3];
    typedef struct {
        uint32_t w, h;
        char *buffer;
        uint32_t texture;
        uint32_t size;
    } image_t;
    typedef struct {
        //1 - rectangle
        uint8_t job;
        uint16_t priority;
        uint32_t x, y;
        uint32_t sx, sy;
        uint8_t color[3];
        bool used = false;
        int id;
    } job_t;
    void onError(int error, const char *description);
    class Instance {
            bool firstr = true;
            bool updating = false;
            bool onJob = false;
            bool noJob = false;
            void render() {
                if(!firstr) glDeleteTextures(1, &render_instance.texture);

                //render
                char render_matrix[renderw][renderh][3];
                char *render_buffer = (char *)render_matrix;
                int ii = 0;
                while(ii < (renderw * renderh * 3)) render_buffer[ii++] = 0;
                if(!render_buffer) return;

                render_matrix[0][0][0] = 255;

                int i = 0;
                while(i < MAX_JOBS){
                    while(updating) {
                        i = 0;
                        ii = 0;
                        while(ii < (renderw * renderh * 3)) render_buffer[ii++] = 0;
                    }
                    if(render_jobs[i].used) {
                        onJob = true;
                        switch(render_jobs[i].job) {
                            case 1: { //rectangle
                                int i1 = render_jobs[i].x, i2 = render_jobs[i].y;
                                while(i1 < (render_jobs[i].x + render_jobs[i].sx)) {
                                    if(i1 < renderw) {
                                        while(i2 < (render_jobs[i].y + render_jobs[i].sy)) {
                                            if(i2 < renderh){
                                                render_matrix[i1][i2][0] = render_jobs[i].color[0];
                                                render_matrix[i1][i2][1] = render_jobs[i].color[1];
                                                render_matrix[i1][i2][2] = render_jobs[i].color[2];
                                            }
                                            i2++;
                                        }
                                    }
                                    i1++;
                                    i2 = render_jobs[i].y;
                                }
                            }
                        }
                        onJob = false;
                    }
                    i++;
                }
                render_instance = create_image(render_buffer, renderw, renderh);
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
            job_t render_jobs[MAX_JOBS];
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
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

                IM_ASSERT(true);

                return img;
            }
            job_t &get_job(int id) {
                int ii = 0;
                while(ii < MAX_JOBS){
                    if(render_jobs[ii].id = id) {
                        return render_jobs[ii];
                    }
                    ii++;
                }
                job_t g;
                return g;
            }
            job_t &create_job(job_t j) {
                while(onJob);
                updating = true;
                int ii = 0;
                while(ii < MAX_JOBS){
                    if(!render_jobs[ii].used) {
                        render_jobs[ii] = j;
                        int iid = rand() % (MAX_JOBS * 8);
                        render_jobs[ii].id = iid;
                        render_jobs[ii].used = true;
                        std::sort(render_jobs, render_jobs + MAX_JOBS, [](job_t const &l, job_t const &r) {return l.priority < r.priority;});
                        updating = false;
                        return get_job(iid);
                    }
                    ii++;
                }
                updating = false;
                job_t g;
                return g;
            }
            void update_job(int id, job_t j){
                while(onJob);
                updating = true;
                int ii = 0;
                while(ii < MAX_JOBS) {
                    if(render_jobs[ii].id = id){
                        int tmpi = render_jobs[ii].id; 
                        render_jobs[ii] = j;
                        render_jobs[ii].used = true;
                        render_jobs[ii].id = tmpi;
                        std::sort(render_jobs, render_jobs + MAX_JOBS, [](job_t const &l, job_t const &r) {return l.priority < r.priority;});
                        updating = false;
                        return;
                    }
                    ii++;
                }
                updating = false;
                return;
            }
            void start(){
                srand(8);
                std::thread thr(&Instance::runner, this);
                thr.detach();
            }
    };

    Instance &create_instance(int w, int h, const char *title);
}
#pragma pack(pop)