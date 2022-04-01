#include "./elgarenta.hpp"

elgarenta::instance_t inst;

int main(){
    // elgarenta::Instance &i = elgarenta::create_instance(1280, 720, "Elgarenta Example");
    inst.w = 1280;
    inst.h = 720;
    inst.title = "Elgarenta Example";
    inst.renderh = 100;
    inst.renderw = 100;
    inst.firstr = true;
    elgarenta::start(&inst);

    elgarenta::job_t j; elgarenta::job_t j2;
    j.color[0] = 0; j.color[1] = 0; j.color[2] = 255; j2.color[0] = 255; j2.color[1] = 0; j2.color[2] = 0;
    j.priority = 0; j2.priority = 1;
    j.sx = 50; j2.sx = 50;
    j.sy = 50; j2.sy = 50;
    j.x = 8; j2.x = 16;
    j.y = 8; j2.y = 16;
    j.job = JOB_RECTANGLE; j2.job = JOB_RECTANGLE;
    //j2.blend = true;
    j.blend = true;

    elgarenta::job_t *r = elgarenta::create_job(j, &inst); elgarenta::job_t *l = elgarenta::create_job(j2, &inst); 

    while(inst.status[0] != 2) {
        // r->x++;
        // r->sx++;
        // r->y++;
        // r->color[0]++;

        // if(r->x == 90) r->x = 0;
        // if(r->y == 90) r->y = 0;
        // if(r->sx == 60) r->sx = 50;
        std::this_thread::sleep_for(std::chrono::seconds(8));
    }
    printf("Main closing\n");
    return 0;
}