#include <iostream>

#include "image.hpp"

using namespace caesar;

void draw() {
    Image img(1920, 1080);
    for (auto i = 0; i < img.get_height(); ++i) {
        for (auto j = 0; j < img.get_width(); ++j) {
            img.set(i, j, 127);
        }
    }
    
    std::cout << "Image created\n";

    img.draw();
}

int main () {
    draw();
    return 0;
}
