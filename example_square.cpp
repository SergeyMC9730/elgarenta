#include "./elgarenta.hpp"

int main(){
    elgarenta::Instance i = elgarenta::create_instance(1280, 720, "Elgarenta Example");
    printf("Instance created\n");

    while(i.status[0] != 2);
    printf("Main closing\n");
    return 0;
}