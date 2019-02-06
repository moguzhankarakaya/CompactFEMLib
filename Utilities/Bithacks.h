//
// Created by oguzhan on 16.06.18.
//

#ifndef FEMPACKAGE_BITHACKS_H
#define FEMPACKAGE_BITHACKS_H

#include<vector>

namespace PrimaryUtilities {

#define MIN(x, y) (y ^ ((x ^ y) & -(x < y)))
#define MAX(x, y) (x ^ ((x ^ y) & -(x < y)))


    template <typename T>
    T nextToTop(std::vector<T>& container)
    {
        T t = container.back();
        container.pop_back();
        T ret = container.back();
        container.push_back(t);
        return ret;
    }

    template <typename T>
    void swap(T& t1, T& t2)
    {
        T temp = t2;
        t2 = t1;
        t1 = temp;
    }

    template <class T>
    class Tolerance
    {
    public:
        explicit Tolerance(T tollerance): _tolerance(tollerance), _boundary(0){}
        void set_boundary(T boundary){_boundary = boundary; }
        bool check_value(T value)
        {
            return (value > _boundary - _tolerance)&&(value < _boundary + _tolerance);
        }
    private:
        T _tolerance;
        T _boundary;
    };


    class Indexer
    {
    public:
        Indexer(size_t width, size_t height): _width(width), _height(height) {}

        size_t get_index(size_t x, size_t y)
        {
            if (x < 0) throw std::string("Invalid array indexer");
            if (y < 0) throw std::string("Invalid array indexer");
            if (x > _width - 1) throw std::string("Invalid array indexer");
            if (y > _height - 1) throw std::string("Invalid array indexer");

            return ((x)+(y) * (_width));
        }
    private:
        size_t _width;
        size_t _height;
    };

    template <typename T>
    void elementWiseOr(std::vector<T>& dest, std::vector<T>& source)
    {
        if(dest.size() != source.size())
            throw std::string("Boolean containers should have the same number of elements");

        for(int i = 0; i < dest.size(); i++)
        {
            dest[i] = dest[i] || source[i];
        }
    }

}

#endif //FEMPACKAGE_BITHACKS_H
