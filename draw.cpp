#include <SDL2/SDL.h>

#include "image.hpp"

using namespace caesar;

void draw_image(const Image& img) {
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
                                              SDL_PIXELFORMAT_ARGB8888,
                                              SDL_TEXTUREACCESS_STATIC,
                                              img.get_height(), img.get_width());


    Uint32 * pixels = new Uint32[img.get_height() * img.get_width()];
    int pixels_itr = 0;
    for (int i = 0; i < img.get_height(); ++i) {
        for (int j = 0; j < img.get_width(); ++j) {
            pixels[pixels_itr] = img.get(i, j);
        }
    }

    SDL_UpdateTexture(texture, NULL, pixels, img.get_height() * sizeof(Uint32));

    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
 
    delete[] pixels; pixels = nullptr;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main() {
    Image img(1920, 1080);

    for (int i = 0; i < img.get_height(); ++i) {
        for (int j = 0; j < img.get_width(); ++j) {
            img.set(i, j, (byte_t)(i*j) & 0xFF);
        }
    }

    draw_image(img);

    return 0;
}
