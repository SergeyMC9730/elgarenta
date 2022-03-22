#include <elgarenta.hpp>

uint8_t elgarenta::coltable[256][3] = {{0, 0, 0}, {128, 0, 0}, {0, 128, 0}, {128, 128, 0}, {0, 0, 128}, {128, 0, 128}, {0, 128, 128}, {192, 192, 192}, {128, 128, 128}, {255, 0, 0}, {0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 255}, {0, 255, 255}, {255, 255, 255}, {0, 0, 0}, {0, 0, 95}, {0, 0, 135}, {0, 0, 175}, {0, 0, 215}, {0, 0, 255}, {0, 95, 0}, {0, 95, 95}, {0, 95, 135}, {0, 95, 175}, {0, 95, 215}, {0, 95, 255}, {0, 135, 0}, {0, 135, 95}, {0, 135, 135}, {0, 135, 175}, {0, 135, 215}, {0, 135, 255}, {0, 175, 0}, {0, 175, 95}, {0, 175, 135}, {0, 175, 175}, {0, 175, 215}, {0, 175, 255}, {0, 215, 0}, {0, 215, 95}, {0, 215, 135}, {0, 215, 175}, {0, 215, 215}, {0, 215, 255}, {0, 255, 0}, {0, 255, 95}, {0, 255, 135}, {0, 255, 175}, {0, 255, 215}, {0, 255, 255}, {95, 0, 0}, {95, 0, 95}, {95, 0, 135}, {95, 0, 175}, {95, 0, 215}, {95, 0, 255}, {95, 95, 0}, {95, 95, 95}, {95, 95, 135}, {95, 95, 175}, {95, 95, 215}, {95, 95, 255}, {95, 135, 0}, {95, 135, 95}, {95, 135, 135}, {95, 135, 175}, {95, 135, 215}, {95, 135, 255}, {95, 175, 0}, {95, 175, 95}, {95, 175, 135}, {95, 175, 175}, {95, 175, 215}, {95, 175, 255}, {95, 215, 0}, {95, 215, 95}, {95, 215, 135}, {95, 215, 175}, {95, 215, 215}, {95, 215, 255}, {95, 255, 0}, {95, 255, 95}, {95, 255, 135}, {95, 255, 175}, {95, 255, 215}, {95, 255, 255}, {135, 0, 0}, {135, 0, 95}, {135, 0, 135}, {135, 0, 175}, {135, 0, 215}, {135, 0, 255}, {135, 95, 0}, {135, 95, 95}, {135, 95, 135}, {135, 95, 175}, {135, 95, 215}, {135, 95, 255}, {135, 135, 0}, {135, 135, 95}, {135, 135, 135}, {135, 135, 175}, {135, 135, 215}, {135, 135, 255}, {135, 175, 0}, {135, 175, 95}, {135, 175, 135}, {135, 175, 175}, {135, 175, 215}, {135, 175, 255}, {135, 215, 0}, {135, 215, 95}, {135, 215, 135}, {135, 215, 175}, {135, 215, 215}, {135, 215, 255}, {135, 255, 0}, {135, 255, 95}, {135, 255, 135}, {135, 255, 175}, {135, 255, 215}, {135, 255, 255}, {175, 0, 0}, {175, 0, 95}, {175, 0, 135}, {175, 0, 175}, {175, 0, 215}, {175, 0, 255}, {175, 95, 0}, {175, 95, 95}, {175, 95, 135}, {175, 95, 175}, {175, 95, 215}, {175, 95, 255}, {175, 135, 0}, {175, 135, 95}, {175, 135, 135}, {175, 135, 175}, {175, 135, 215}, {175, 135, 255}, {175, 175, 0}, {175, 175, 95}, {175, 175, 135}, {175, 175, 175}, {175, 175, 215}, {175, 175, 255}, {175, 215, 0}, {175, 215, 95}, {175, 215, 135}, {175, 215, 175}, {175, 215, 215}, {175, 215, 255}, {175, 255, 0}, {175, 255, 95}, {175, 255, 135}, {175, 255, 175}, {175, 255, 215}, {175, 255, 255}, {215, 0, 0}, {215, 0, 95}, {215, 0, 135}, {215, 0, 175}, {215, 0, 215}, {215, 0, 255}, {215, 95, 0}, {215, 95, 95}, {215, 95, 135}, {215, 95, 175}, {215, 95, 215}, {215, 95, 255}, {215, 135, 0}, {215, 135, 95}, {215, 135, 135}, {215, 135, 175}, {215, 135, 215}, {215, 135, 255}, {215, 175, 0}, {215, 175, 95}, {215, 175, 135}, {215, 175, 175}, {215, 175, 215}, {215, 175, 255}, {215, 215, 0}, {215, 215, 95}, {215, 215, 135}, {215, 215, 175}, {215, 215, 215}, {215, 215, 255}, {215, 255, 0}, {215, 255, 95}, {215, 255, 135}, {215, 255, 175}, {215, 255, 215}, {215, 255, 255}, {255, 0, 0}, {255, 0, 95}, {255, 0, 135}, {255, 0, 175}, {255, 0, 215}, {255, 0, 255}, {255, 95, 0}, {255, 95, 95}, {255, 95, 135}, {255, 95, 175}, {255, 95, 215}, {255, 95, 255}, {255, 135, 0}, {255, 135, 95}, {255, 135, 135}, {255, 135, 175}, {255, 135, 215}, {255, 135, 255}, {255, 175, 0}, {255, 175, 95}, {255, 175, 135}, {255, 175, 175}, {255, 175, 215}, {255, 175, 255}, {255, 215, 0}, {255, 215, 95}, {255, 215, 135}, {255, 215, 175}, {255, 215, 215}, {255, 215, 255}, {255, 255, 0}, {255, 255, 95}, {255, 255, 135}, {255, 255, 175}, {255, 255, 215}, {255, 255, 255}, {8, 8, 8}, {18, 18, 18}, {28, 28, 28}, {38, 38, 38}, {48, 48, 48}, {58, 58, 58}, {68, 68, 68}, {78, 78, 78}, {88, 88, 88}, {98, 98, 98}, {108, 108, 108}, {118, 118, 118}, {128, 128, 128}, {138, 138, 138}, {148, 148, 148}, {158, 158, 158}, {168, 168, 168}, {178, 178, 178}, {188, 188, 188}, {198, 198, 198}, {208, 208, 208}, {218, 218, 218}, {228, 228, 228}, {238, 238, 238}};
// elgarenta::Instance instance;

void elgarenta::onError(int error, const char *description){
    printf("GLFW Error %d: %s\n", error, description);
}
// elgarenta::Instance &elgarenta::create_instance(int w, int h, const char *title){
//     instance.w = w;
//     instance.h = h;
//     instance.renderh = 100;
//     instance.renderw = 100;
//     instance.title = title;

//     instance.start();
    
//     return instance;
// }
void elgarenta::render(elgarenta::instance_t *inst){
    if(!inst->firstr) glDeleteTextures(1, &inst->rendered_image.texture);

    char render_matrix[inst->renderw][inst->renderh][3];
    char *render_buffer = (char *)render_matrix;
    int ii = 0, i = 0;
    while(ii < (inst->renderw * inst->renderh * 3)) render_buffer[ii++] = 0;
    
    while(i < MAX_JOBS) {
        while(inst->updating){
            i = ii = 0;
            while(ii < (inst->renderw * inst->renderh * 3)) render_buffer[ii++] = 0;
        }
        if(inst->render_jobs[i].used){
            inst->onJob = true;
            switch(inst->render_jobs[i].job){
                case JOB_RECTANGLE: {
                    int i1 = inst->render_jobs[i].x, i2 = inst->render_jobs[i].y;
                    while((i1 < (inst->render_jobs[i].x + inst->render_jobs[i].sx)) && (inst->render_jobs[i].x < inst->renderw) && (inst->render_jobs[i].y < inst->renderh)) {
                        if(i1 < inst->renderw){
                            while(i2 < (inst->render_jobs[i].y + inst->render_jobs[i].sy)) {
                                if(i2 < inst->renderh) memcpy(&render_matrix[i1][i2], &inst->render_jobs[i].color, 3);
                                i2++;
                            }
                        }
                        i1++;
                        i2 = inst->render_jobs[i].y;
                    }
                }
            }
            inst->onJob = false;
        }
        i++;
    }
    inst->rendered_image = elgarenta::create_image(render_buffer, inst->renderw, inst->renderh);
    inst->firstr = false;
}
void elgarenta::runner(elgarenta::instance_t *inst){
    if(!glfwInit()) {
        inst->status[0] = 2;
        return;
    }
    glfwSetErrorCallback(elgarenta::onError);
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
    inst->window = glfwCreateWindow(inst->w, inst->h, inst->title, nullptr, nullptr);
    if(!inst->window) {
        inst->status[0] = 2;
        return;
    }
    glfwMakeContextCurrent(inst->window);
    glfwSwapInterval(1);
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsClassic();
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(inst->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 cc = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while(!glfwWindowShouldClose(inst->window)){
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Elgarenta Window", nullptr);
        render(inst);
        ImGui::Image((void *)(intptr_t)inst->rendered_image.texture, ImVec2(inst->rendered_image.w * inst->rendered_image.size, inst->rendered_image.h * inst->rendered_image.size));
        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, inst->w, inst->h);
        glClearColor(cc.x * cc.w, cc.y * cc.w, cc.z * cc.w, cc.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(inst->window);
    }
    printf("Closing\n");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(inst->window);
    glfwTerminate();

    inst->status[0] = 2;
    return;
}
elgarenta::image_t elgarenta::create_image(char *buffer, int w, int h){
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
elgarenta::job_t *elgarenta::get_job(int id, elgarenta::instance_t *inst) {
    int ii = 0;
    while(ii < MAX_JOBS){
        if(inst->render_jobs[ii].id == id) return &inst->render_jobs[ii];
        ii++;
    }
    return nullptr;
}
elgarenta::job_t *elgarenta::create_job(elgarenta::job_t j, elgarenta::instance_t *inst){
    while(inst->onJob);
    inst->updating = true;
    int ii = 0;
    while(ii < MAX_JOBS){
        if(!inst->render_jobs[ii].used) {
            inst->render_jobs[ii] = j;
            int id = rand() % (MAX_JOBS * 8);
            inst->render_jobs[ii].id = id;
            inst->render_jobs[ii].used = true;
            std::sort(inst->render_jobs, inst->render_jobs + MAX_JOBS, [](job_t const &l, job_t const &r) {return l.priority > r.priority;});
            inst->updating = false;
            return get_job(id, inst);
        }
        ii++;
    }
    inst->updating = false;
    return nullptr;
}
void elgarenta::update_job(int id, elgarenta::job_t j, elgarenta::instance_t *inst){
    while(inst->onJob);
    inst->updating = true;
    int ii = 0;
    while(ii < MAX_JOBS){
        if(inst->render_jobs[ii].id == id) {
            int tmpid = inst->render_jobs[ii].id;
            inst->render_jobs[ii] = j;
            inst->render_jobs[ii].id = tmpid;
            std::sort(inst->render_jobs, inst->render_jobs + MAX_JOBS, [](job_t const &l, job_t const &r) {return l.priority > r.priority;});
            inst->updating = false;
            return;
        }
        ii++;
    }
    inst->updating = false;
    return;
}
void elgarenta::start(elgarenta::instance_t *inst){
    srand(8);
    std::thread thr(runner, inst);
    thr.detach();
    printf("[Elgarenta] Created Elgarenta instance\n");
}