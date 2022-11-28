#include "./elgarenta.hpp"
#include "./bmp.h"

elgarenta::instance_t inst;

int main(){
    // elgarenta::Instance &i = elgarenta::create_instance(1280, 720, "Elgarenta Example");
    inst.w = 1280;
    inst.h = 720;
    inst.title = "Elgarenta Example";
    inst.renderh = 100;
    inst.renderw = 100;
    elgarenta::start(&inst);

    elgarenta::job_t j; elgarenta::job_t j2;
    j.color[0] = 0; j.color[1] = 0; j.color[2] = 255;
    j.priority = 1; j2.priority = 2;
    j.sx = 50; j2.sx = 32;
    j.sy = 50; j2.sy = 32;
    j.x = 8; j2.x = 16;
    j.y = 8; j2.y = 16;
    j.job = JOB_RECTANGLE; j2.job = JOB_FBPIPE;
    j2.arg0 = (void *)(openBMP("example_img.bmp")->data);
    elgarenta::job_t *r = elgarenta::create_job(j, &inst); 
    elgarenta::job_t *l = elgarenta::create_job(j2, &inst); 

    while(inst.status[0] != 2) {
        r->x++;
	l->x += 2;
        r->y++;
	l->y += 2;
        r->color[0]++;
	r->color[0] += 2;

	if(l->x == 50) l->x = 0;
	if(l->y == 50) l->y = 0;

        if(r->x == 50) r->x = 0;
        if(r->y == 50) r->y = 0;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    printf("Main closing\n");
    return 0;
}
