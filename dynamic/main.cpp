#include <dlfcn.h>
#include <iostream>
#include "IGraphics.hpp"

using namespace std;

int main(int argc, char **argv)
{
    void* handle;
    if (argc != 2){
        std::cout << "please try again" << std::endl;
        return 0;
    }
    if (argv[2] == "1")
        handle = dlopen("./sdl.so", RTLD_LAZY | RTLD_LOCAL);
    else if (argv[2] == "2")
        handle = dlopen("./sfml.so", RTLD_LAZY | RTLD_LOCAL);
    if (!handle){
        std::cout << "bad handle" << std::endl;
        return 0;
    }
    IGraphics* (*create)();
    void (*destroy)(IGraphics*);
  
    /* on Linux, use "./myclass.so" */

    std::cout << "help me" << std::endl;
   	if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL) { 
        std::cerr << "open_lib: dlopen : "<< dlerror() << std::endl;
        return 0;
    }
    std::cout << "help me" << std::endl;

    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");


    IGraphics* myClass = create();
    myClass->printSquare();
    destroy(myClass);
    std::cout << "please" << std::endl;
    return 0;
}