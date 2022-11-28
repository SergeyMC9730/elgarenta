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

    elgarenta::job_t j; elgarenta::job_t j2; elgarenta::job_t j3; elgarenta::job_t j4;
    j.color[0] = 0; j.color[1] = 0; j.color[2] = 255; j2.color[0] = 255; j2.color[1] = 0; j2.color[2] = 0;
    j3.priority = 0; j.priority = 1; j2.priority = 2;
    j.sx = 50; j2.sx = 50; j3.sx = 50; j4.sx = 100;
    j.sy = 50; j2.sy = 50; j3.sy = 100; j4.sy = 100;
    j.x = 8; j2.x = 16; j3.x = 0;
    j.y = 8; j2.y = 16; j3.y = 0;
    j.job = JOB_RECTANGLE; j2.job = JOB_RECTANGLE; j3.job = JOB_RECTANGLE; j4.job = JOB_RECTANGLE;
    j.blend = true;
    j2.blend = false;
    j3.blend = true;
    j4.blend = true;
    j3.color[0] = 32; j3.color[1] = 32; j3.color[2] = 32;

    elgarenta::job_t *a = elgarenta::create_job(j4, &inst);
    elgarenta::job_t *b = elgarenta::create_job(j3, &inst);
    elgarenta::job_t *r = elgarenta::create_job(j, &inst); 
    elgarenta::job_t *l = elgarenta::create_job(j2, &inst); 

    while(inst.status[0] != 2) {
        r->x++;
	b->x++;
	l->x += 2;
        r->y++;
	l->y += 2;
	l->color[0] = rand() % 64;
	l->color[1] = l->color[0];
	l->color[2] = l->color[0];
        r->color[0]++;
	r->color[0] += 2;
	a->color[0] = rand() % 32;
	a->color[1] = rand() % 32;
	a->color[2] = rand() % 32;

	if(l->x == 50) l->x = 0;
	if(l->y == 50) l->y = 0;

        if(r->x == 50) r->x = 0;
        if(r->y == 50) r->y = 0;

	if(b->x == 50) b->x = 0;

	printf("x:%d\n", b->x);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    printf("Main closing\n");
    return 0;
}
