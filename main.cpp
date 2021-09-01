#include <iostream>

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

struct Args {
    
    CLI::App app;
    uint width = 20;
    uint height = 50;
    uint fps = 15;
    
    Args(int argc, char** argv) {
        app.add_option("-w, --width", width, "The width of the data matrix (default is 20)");
        
        app.add_option("-h, --height", height, "The height of the data matrix (default is 50)");

        app.add_option("--fps", fps, "The rate of transmission (frames per second - default is 15fps)");

        CLI11_PARSE(app, argc, argv);
    }

}

int main(int argc, char** argv) {
    Args args{argc, argv};

    std::clog << "Received: (width, height, fps): (" << args.width << ", " << args.height << ", " << args.fps << ")\n";
    return 0;
}