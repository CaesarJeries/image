#include <iostream>

#include "image.hpp"

using namespace caesar;


void test_crop() {
    Image img(1920, 1080);

    for (int i = 0; i < 1920; ++i) {
        for (int j = 0; j < 1080; ++j) {
            img.set(i, j, (byte_t)((i*j) & 0xFF));
        }
    }

    Image sub_image = img.crop(300, 300, 500, 500);
}


int main () {

    test_crop();

    return 0;
}