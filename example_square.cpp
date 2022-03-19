#include "./elgarenta.hpp"

int main(){
    elgarenta::Instance i = elgarenta::create_instance(1280, 720, "Elgarenta Example");
    printf("Instance created\n");
    elgarenta::job_t j;
    j.color = 2;
    j.priority = 0;
    j.sx = 50;
    j.sy = 50;
    j.x = 8;
    j.y = 8;
    j.job = 1;
    int r = i.create_job(j);
    while(i.status[0] != 2) {
        if(r != -1){
            j.color++;
            i.update_job(r, j);
        }
    }
    printf("Main closing\n");
    return 0;
}