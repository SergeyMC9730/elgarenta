#include <elgarenta.hpp>

void elgarenta::onError(int error, const char *description){
    printf("GLFW Error %d: %s\n", error, description);
}
elgarenta::Instance elgarenta::create_instance(int w, int h, const char *title){
    elgarenta::Instance instance;

    instance.w = w;
    instance.h = h;
    instance.title = title;

    instance.start();
    
    return instance;
}