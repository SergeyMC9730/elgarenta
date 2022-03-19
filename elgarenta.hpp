#pragma once

#include "./imgui/imgui.h"
#include "./imgui/backends/imgui_impl_glfw.h"
#include "./imgui/backends/imgui_impl_opengl3.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <stdio.h>

namespace elgarenta {
    void onError(int error, const char *description);
    class Instance {
            void runner() {
                if(!glfwInit()) {
                    status[0] = 2;
                    return;
                }
                glfwSetErrorCallback(onError);
                #if defined(IMGUI_IMPL_OPENGL_ES2)
                    // GL ES 2.0 + GLSL 100
                    const char* glsl_version = "#version 100";
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
                #elif defined(__APPLE__)
                    // GL 3.2 + GLSL 150
                    const char* glsl_version = "#version 150";
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
                #else
                    // GL 3.0 + GLSL 130
                    const char* glsl_version = "#version 130";
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
                    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
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
                    ImGui::Text("Example example");
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
            const char *title;
            GLFWwindow *window;
            int status[3];
            void start(){
                std::thread thr(&Instance::runner, this);
                thr.detach();
            }
    };

    // typedef struct {
    //     static GLFWwindow *window;
    //     static struct mt {
    //         static int w;
    //         static int h;
    //         static const char *title;
    //     } metadata;
    //     static int status[3];
    //     static void onError(int error, const char *description){
    //         printf("GLFW Error %d: %s\n", error, description);
    //     }
    //     static void runner(void) {
    //         glfwSetErrorCallback(onError);
    //         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0);
    //         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    //         window = glfwCreateWindow(metadata.w, metadata.h, metadata.title, NULL, NULL);
    //         if(!window) {
    //             status[0] = -1;
    //             return;
    //         }
    //         glfwMakeContextCurrent(window);
    //         glfwSwapInterval(1);
    //         IMGUI_CHECKVERSION();
    //         ImGui::CreateContext();
    //         ImGuiIO& io = ImGui::GetIO(); (void)io;
    //         io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //         ImGui::StyleColorsClassic();
    //         ImGui_ImplGlfw_InitForOpenGL(window, true);
    //         ImGui_ImplOpenGL3_Init("#version 130");

    //         ImVec4 cc = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //         while(!glfwWindowShouldClose(window)){
    //             glfwPollEvents();
    //             ImGui_ImplOpenGL3_NewFrame();
    //             ImGui_ImplGlfw_NewFrame();
    //             ImGui::NewFrame();

    //             ImGui::Begin("Elgarenta Window", nullptr);
    //             ImGui::Text("Example example");
    //             ImGui::End();

    //             ImGui::Render();
    //             glViewport(0, 0, metadata.w, metadata.h);
    //             glClearColor(cc.x * cc.w, cc.y * cc.w, cc.z * cc.w, cc.w);
    //             glClear(GL_COLOR_BUFFER_BIT);
    //             ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //             glfwSwapBuffers(window);
    //         }
    //         printf("Closing\n");
    //         ImGui_ImplOpenGL3_Shutdown();
    //         ImGui_ImplGlfw_Shutdown();
    //         ImGui::DestroyContext();

    //         glfwDestroyWindow(window);
    //         glfwTerminate();

    //         status[0] = 2;
    //         return;
    //     }
    // } instance_t;

    Instance create_instance(int w, int h, const char *title);

}