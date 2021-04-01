#ifndef __CAESAR_IMAGE_HPP__
#define __CAESAR_IMAGE_HPP__

#include <exception>
#include <string>

#include "utilities.hpp"


namespace caesar {

class Image {

    public:

    class InvalidResolutionException : public std::exception {
        private:
        std::string m_msg;
        public:
        InvalidResolutionException(const std::string& msg): m_msg(msg) {}
    };

    class OutOfBoundsException : public std::exception {
        private:
        std::string m_msg;
        public:
        OutOfBoundsException(const std::string& msg): m_msg(msg) {}
    };

    private:
    
    int m_width;
    int m_height;
    byte_t* m_data;

    byte_t* copy_data() const;
    int get_index(int r, int c) const;
    
    static void check_bounds(int r, int c);
    static void check_resolution(int w, int h);

    public:
    
    static constexpr int S_MIN_WIDTH = 24;
    static constexpr int S_MAX_WIDTH = 1080;
    
    static constexpr int S_MIN_HEIGHT = 24;
    static constexpr int S_MAX_HEIGHT = 1920;

    Image(int w = S_MIN_WIDTH,
          int h = S_MIN_HEIGHT);
    
    ~Image();

    int get_width() const;
    int get_height() const;

    Image crop(int r, int c, int w, int h) const;

    byte_t get(int r, int c) const;
    void set(int r, int c, byte_t value);

    Image& operator=(Image&& other);
    Image(Image&& other);

    Image& operator=(const Image& other);
    Image(const Image& other);

}; // class Image

}


#endif // __CAESAR_IMAGE_HPP__
