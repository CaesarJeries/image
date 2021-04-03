#include <iostream>
#include <utility>
#include <memory>
#include <cstring> // memcpy, strncmp

#include "image.hpp"



namespace caesar {


Image::Image(int h, int w):
m_height(h),
m_width(w),
m_data(nullptr) {
    check_resolution(h, w);
    m_data = new byte_t[h * w];
}


Image::~Image() {
    delete[] m_data;
}

void Image::check_bounds(int r, int c) const {
    // todo: add error message
    if (r < 0 || r >= m_height) throw OutOfBoundsException();
    if (c < 0 || c >= m_width) throw OutOfBoundsException();
}


void Image::check_resolution(int h, int w) {
    // todo: add error message
    if (h < S_MIN_HEIGHT || h > S_MAX_HEIGHT) throw InvalidResolutionException();
    if (w < S_MIN_WIDTH || w > S_MAX_WIDTH) throw InvalidResolutionException();
}


byte_t* Image::copy_data() const {
    byte_t* copy = new byte_t[m_height * m_width];
    memcpy(copy, m_data, m_height * m_width);

    return copy;
}


Image::Image(const Image& other):
m_height(other.m_height),
m_width(other.m_width),
m_data(other.copy_data())
{}


Image& Image::operator=(const Image& other) {
    if (this != &other) {
        byte_t* copy_address = nullptr;
        try {
            copy_address = new byte_t[other.m_height * other.m_width ];

            delete[] m_data;
            m_data = copy_address;

        } catch (const std::bad_alloc& e) {
            std::cerr << "Allocation failed: " << e.what() << std::endl;
        }
    }

    return *this;
}


Image::Image(Image&& other):
m_height(other.m_height),
m_width(other.m_width){
    m_data = other.m_data;
    other.m_data = nullptr;
    other.m_height = 0;
    other.m_width = 0;
}


Image& Image::operator=(Image&& other) {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_height = other.m_height;
        m_width = other.m_width;

        other.m_data = nullptr;
        other.m_height = 0;
        other.m_width = 0;
    }

    return *this;
}


int Image::get_index(int r, int c) const {
    return r * m_width + c;
}


byte_t Image::get(int r, int c) const {
    check_bounds(r, c);

    const int index = get_index(r, c);
    return m_data[index];
}


void Image::set(int r, int c, byte_t value) {
    check_bounds(r, c);

    const int index = get_index(r, c);
    m_data[index] = value;
}


int Image::get_height() const {
    return m_height;
}


int Image::get_width() const {
    return m_width;
}


Image Image::crop(int r, int c, int h, int w) const {
    check_bounds(r, c);
    check_bounds(r + h - 1, c + w - 1);

    Image sub_image(h, w);

    int sub_img_itr = 0;
    for (int row_itr = r; row_itr < (r + h); ++row_itr) {
        for (int col_itr = c; col_itr < (c + w); ++col_itr) {
            sub_image.m_data[sub_img_itr] = get(row_itr, col_itr);
            ++sub_img_itr;
        }
    }

    return sub_image;
}


Image Image::operator+(const Image& other) const {
    Image result(m_height, m_width);

    for (int row = 0; row < m_height; ++row) {
        for (int col = 0; col < m_width; ++col) {
            const int index = get_index(row, col);
            byte_t cell = m_data[index];
            
            result.set(row, col, cell + other.m_data[index]);
        }
    }

    return result;
}


Image Image::operator-(const Image& other) const {
    Image result (m_height, m_width);
    for (int row = 0; row < m_height; ++row) {
        for (int col = 0; col < m_width; ++col) {
            const int index = get_index(row, col);
            const byte_t cell = m_data[index];
            
            if (other.m_data[index] > cell) {
                result.set(row, col, 0);
            }
            else {
                result.set(row, col, cell - other.m_data[index]);
            }

        }
    }

    return result;
}


bool Image::operator==(const Image& other) const {
    return 0 == strncmp(reinterpret_cast<const char*>(m_data),
                        reinterpret_cast<const char*>(other.m_data),
                        m_height * m_width);
}


bool Image::operator!=(const Image& other) const {
    return !(*this == other);
}

}
