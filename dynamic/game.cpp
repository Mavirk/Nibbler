#include "game.hpp"

Game::Game(char** argv){
   
    if (static_cast<std::string>(argv[1]) == "1"){
        handle = dlopen("sdl.so", RTLD_LAZY );
    }
    else if (static_cast<std::string>(argv[1]) == "2"){
        handle = dlopen("sfml.so", RTLD_LAZY );
    }
    if (!handle){
        std::cout << "bad handle" << std::endl;
        return ;
    }
  
    /* on Linux, use "./myclass.so" */

   	if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL) { 
        std::cerr << "creat_object : "<< dlerror() << std::endl;
        return ;
    }
    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");
    lib = create();
    return ;
}

Game::~Game(){
    destroy(lib);
}

void 
Game::run(){
    std::cout << "running" << std::endl;
    lib->printSquare();
    loadLib(2);
    lib->printSquare();
    loadLib(1);
    lib->printSquare();
}

void
Game::loadLib(int i){
    const char* filename;
    switch (i) {
        case 1 :
            filename = "sdl.so";
            break;
        case 2 :
            filename = "sfml.so";
            break;
    }
    handle = dlopen(filename, RTLD_LAZY );
    destroy(lib);
    if (!handle){
        std::cout << "bad handle" << std::endl;
        return;
    }else if ((create = reinterpret_cast<IGraphics* (*)()>(dlsym(handle, "create_object"))) == NULL){ 
        std::cerr << "create_object : "<< dlerror() << std::endl;
        return ;
    }
    destroy = (void (*)(IGraphics*))dlsym(handle, "destroy_object");
    lib = create();
}