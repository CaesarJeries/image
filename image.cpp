#include <iostream>
#include <utility>
#include <memory>
#include <cstring> // memcpy

#include "image.hpp"



namespace caesar {


Image::Image(int w, int h):
m_width(w),
m_height(h),
m_data(nullptr) {
    m_data = new byte_t[w * h];
}


Image::~Image() {
    delete[] m_data;
}


byte_t* Image::copy_data() const {
    byte_t* copy = new byte_t[m_width * m_height];
    memcpy(copy, m_data, m_width * m_height);

    return copy;
}


Image::Image(const Image& other):
m_width(other.m_width),
m_height(other.m_height) {
    m_data = other.copy_data();
}


Image& Image::operator=(const Image& other) {
    if (this != &other) {
        byte_t* copy_address = nullptr;
        try {
            copy_address = new byte_t[other.m_width * other.m_height];

            delete[] m_data;
            m_data = copy_address;

            return *this;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Allocation failed: " << e.what() << std::endl;
        }
    }

    return *this;
}


Image::Image(Image&& other):
m_width(other.m_width),
m_height(other.m_height),
m_data(std::move(other.m_data)) {}


Image& Image::operator=(Image&& other) {
    if (this != &other) {
        delete[] m_data;
        m_data = std::move(other.m_data);

        m_width = other.m_width;
        m_height = other.m_height;
    }

    return *this;
}


int Image::get_index(int r, int c) const {
    return r * m_width + c;
}


byte_t Image::get(int r, int c) const {
    const int index = get_index(r, c);
    return m_data[index];
}


void Image::set(int r, int c, byte_t value) {
    const int index = get_index(r, c);
    m_data[index] = value;
}


Image Image::crop(int r, int c, int w, int h) const {
    Image sub_image(w, h);

    int sub_img_itr = 0;
    for (int row_itr = r; row_itr < (r + h); ++row_itr) {
        for (int col_itr = c; col_itr < (c + w); ++col_itr) {
            //std::clog << "Reading cell: " << row_itr << ", " << col_itr << std::endl;
            sub_image.m_data[sub_img_itr] = get(row_itr, col_itr);
            ++sub_img_itr;
        }
    }

    return sub_image;
}


}
