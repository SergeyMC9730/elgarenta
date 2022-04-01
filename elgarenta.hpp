#pragma once

#include "./imgui/imgui.h"
#include "./imgui/backends/imgui_impl_glfw.h"
#include "./imgui/backends/imgui_impl_opengl3.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>

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
        uint8_t job;
        uint16_t priority;
        uint32_t x, y;
        uint32_t sx, sy;
        uint8_t color[3];
        bool blend = false;
        bool used = false;
        int id;
    } job_t;
    typedef struct {
        bool firstr = true;
        bool updating = false;
        bool onJob = false;
        bool noJob = false;
        image_t rendered_image;
        job_t render_jobs[MAX_JOBS];
        int w, h;
        int renderw, renderh;
        const char *title;
        GLFWwindow *window;
        //code will run
        uint16_t wait_time;
        int status[3];
    } instance_t;
    void onError(int error, const char *description);
    void render(instance_t *inst);
    void runner(instance_t *inst);
    job_t *get_job(int id, instance_t *inst);
    job_t *create_job(job_t j, instance_t *inst);
    void update_job(int id, job_t j, instance_t *inst);
    image_t create_image(char *buffer, int w, int h);
    void start(instance_t *inst);
}
#pragma pack(pop)