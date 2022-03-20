#include "./elgarenta.hpp"

int main(){
    elgarenta::Instance &i = elgarenta::create_instance(1280, 720, "Elgarenta Example");
    printf("Instance created\n");

    elgarenta::job_t j; elgarenta::job_t j2;
    j.color[0] = 0; j.color[1] = 0; j.color[2] = 255; j2.color[0] = 255; j2.color[1] = 0; j2.color[2] = 0;
    j.priority = 0; j2.priority = 1;
    j.sx = 50; j2.sx = 50;
    j.sy = 50; j2.sy = 50;
    j.x = 8; j2.x = 16;
    j.y = 8; j2.y = 16;
    j.job = JOB_RECTANGLE; j2.job = JOB_RECTANGLE;

    elgarenta::job_t &r = i.create_job(j); elgarenta::job_t &l = i.create_job(j2);

    //find right struct
    int ii = 0, ii2 = 0;
    while(ii < MAX_JOBS) {
        if(i.render_jobs[ii].id = r.id) break;
        ii++;
    }
    while(ii2 < MAX_JOBS) {
        if(i.render_jobs[ii2].id = r.id) break;
        ii2++;
    }

    while(i.status[0] != 2) {
        i.render_jobs[ii].x++;
        i.render_jobs[ii].sx++;
        i.render_jobs[ii].y++;
        i.render_jobs[ii].color[0]++;

        if(i.render_jobs[ii].x == 90) i.render_jobs[ii].x = 0;
        if(i.render_jobs[ii].y == 90) i.render_jobs[ii].y = 0;
        if(i.render_jobs[ii].sx == 60) i.render_jobs[ii].sx = 50;
        
    }
    printf("Main closing\n");
    return 0;
}