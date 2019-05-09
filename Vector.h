#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>
#include <string.h>
#include <iterator>
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
template <typename T>
class Vector
{
private:
    int vsize, maxsize, maximum = 10000000;
    T *array;
    inline void alloc_new()
    {
        maxsize = vsize * 2;
        T *tarr = new T[maxsize];
        memcpy(tarr, array, vsize * sizeof(T));
        delete[] array;
        array = tarr;
    }

public:
    typedef T value_type;
    typedef const T const_value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef value_type &reference;
    typedef value_type *pointer;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef const_value_type *const_pointer;
    typedef const_value_type &const_reference;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    pointer begin()
    {
        pointer it;
        it = (&array[0]);
        return it;
    }
    pointer end()
    {
        pointer it;
        it = &array[vsize - 1];
        return it;
    };
    reference front()
    {
        return (array[0]);
    };
    reference back()
    {
        return (array[vsize - 1]);
    };
    Vector()
    {
        maxsize = 20;
        array = new value_type[maxsize];
        vsize = 0;
    };
    Vector(value_type i)
    {
        maxsize = i;
        array = new value_type[maxsize];
        vsize = 0;
    };
    Vector(const Vector &v)
    {
        maxsize = v.maxsize;
        vsize = v.vsize;
        array = new value_type[maxsize];
        for (size_t i = 0; i < v.vsize; i++)
        {
            array[i] = v.array[i];
        }
    };
    ~Vector()
    {
        delete[] array;
    };

    int size() { return vsize; };
    int max_size() { return maximum; };
    int capacity() { return maxsize; };
    value_type operator[](int i)
    {
        if (i < vsize)
            return array[i];
        throw std::out_of_range("out of range");
    };
    Vector &operator=(const Vector &v)
    {
        if (this != &v)
        {
            maxsize = v.maxsize;
            vsize = v.vsize;
            delete[] array;
            array = new value_type[maxsize];
            for (size_t i = 0; i < v.vsize; i++)
            {
                array[i] = v.array[i];
            }
        }
        return *this;
    }
    Vector &operator+=(value_type i)
    {
        this->push_back(i);
        return *this;
    }
    value_type at(int i)
    {
        if (i < vsize)
            return array[i];
        throw std::out_of_range("out of range");
    };
    void push_back(value_type i)
    {
        if (vsize + 1 > maxsize)
            alloc_new();
        array[vsize] = i;
        vsize++;
    };
    bool empty()
    {
        if (vsize == 0)
            return true;
        else
            return false;
    };
    void assign(int a, value_type b)
    {
        for (size_t i = 1; i <= a; i++)
        {
            if (vsize + 1 > maxsize)
                alloc_new();
            array[vsize] = b;
            vsize++;
        }
    }
    void shrink_to_fit()
    {
        maxsize = vsize;
        value_type *tmp = new value_type[maxsize];
        for (int i = 0; i < vsize; i++)
            tmp[i] = array[i];
        delete[] array;
        array = tmp;
    };
    void clear()
    {
        vsize = 0;
        delete[] array;
        array = new value_type(maxsize);
    }
    void pop_back()
    {
        vsize = vsize - 1;
        value_type *tmp = new value_type[maxsize];
        for (int i = 0; i < vsize; i++)
            tmp[i] = array[i];
        delete[] array;
        array = tmp;
    };
    void erase(pointer it)
    {
        pointer iit = &array[it - array];
        (*iit).~T();
        memmove(iit, iit + 1, (vsize - (it - array) - 1) * sizeof(T));
        --vsize;
    }
    void erase(pointer first, pointer last)
    {
        value_type *temp = first;
        pointer f = &array[first - array];
        for (; first != last; ++first)
            (*first).~T();
        memmove(f, last, (vsize - (last - array)) * sizeof(T));
        vsize -= last - temp;
    }

    pointer insert(pointer it, const T &val)
    {
        pointer iit = &array[it - array];
        if (vsize == max_size)
        {
            max_size <<= 2;
            alloc_new();
        }
        memmove(iit + 1, iit, (vsize - (it - array)) * sizeof(T));
        (*iit) = val;
        ++vsize;
        return iit;
    }

    pointer insert(pointer it, T &&val)
    {
        pointer iit = &array[it - array];
        if (vsize == maxsize)
        {
            maxsize <<= 2;
            alloc_new();
        }
        memmove(iit + 1, iit, (vsize - (it - array)) * sizeof(T));
        (*iit) = std::move(val);
        ++vsize;
        return iit;
    }
    void reserve(int sz) {
		if (sz > maxsize) {
			maxsize = sz;
			alloc_new();
		}
	}
    void resize(int sz)
    {
        if (sz > vsize)
        {
            if (sz > maxsize)
            {
                maxsize = sz;
                alloc_new();
            }
        }
        else
        {
            size_type i;
            for (i = vsize; i < sz; ++i)
                array[i].~T();
        }
        vsize = sz;
    }

    void resize(int sz, const T &c)
    {
        if (sz > vsize)
        {
            if (sz > maxsize)
            {
                maxsize = sz;
                alloc_new();
            }
            size_type i;
            for (i = vsize; i < sz; ++i)
                array[i] = c;
        }
        else
        {
            size_type i;
            for (i = vsize; i < sz; ++i)
                array[i].~T();
        }
        vsize = sz;
    }

    void swap(Vector<T> &other)
    {
        size_t tvsize = vsize,
               tmaxsize = maxsize;
        T *tarray = array;

        vsize = other.vsize;
        maxsize = other.maxsize;
        array = other.array;

        other.vsize = tvsize;
        other.maxsize = tmaxsize;
        other.array = tarray;
    }

    bool operator==(const Vector<value_type> &vec) const
    {
        if (vsize != vec.vsize)
            return false;
        size_type i;
        for (i = 0; i < vsize; ++i)
            if (array[i] != vec.array[i])
                return false;
        return true;
    }

    bool operator!=(const Vector<value_type> &vec) const
    {
        if (vsize != vec.vsize)
            return true;
        size_type i;
        for (i = 0; i < vsize; ++i)
            if (array[i] != vec.array[i])
                return true;
        return false;
    }

    bool operator<(const Vector<value_type> &vec) const
    {
        size_type i, j, ub = vsize < vec.vsize ? vsize : vec.vsize;
        for (i = 0; i < ub; ++i)
            if (array[i] != vec.array[i])
                return array[i] < vec.array[i];
        return vsize < vec.vsize;
    }

    bool operator<=(const Vector<value_type> &vec) const
    {
        size_type i, j, ub = vsize < vec.vsize ? vsize : vec.vsize;
        for (i = 0; i < ub; ++i)
            if (array[i] != vec.array[i])
                return array[i] < vec.array[i];
        return vsize <= vec.vsize;
    }

    bool operator>(const Vector<value_type> &vec) const
    {
        size_type i, j, ub = vsize < vec.vsize ? vsize : vec.vsize;
        for (i = 0; i < ub; ++i)
            if (array[i] != vec.array[i])
                return array[i] > vec.array[i];
        return vsize > vec.vsize;
    }

    bool operator>=(const Vector<value_type> &vec) const
    {
        size_type i, j, ub = vsize < vec.vsize ? vsize : vec.vsize;
        for (i = 0; i < ub; ++i)
            if (array[i] != vec.array[i])
                return array[i] > vec.array[i];
        return vsize >= vec.vsize;
    }

    const_iterator cbegin() const
    {
        return array;
    }

    const_iterator cend() const
    {
        return array + vsize;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(array + vsize);
    }

    const_reverse_iterator crbegin() const
    {
        return reverse_iterator(array + vsize);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(array);
    }

    const_reverse_iterator crend() const
    {
        return reverse_iterator(array);
    }

	value_type * data() noexcept {
		return array;
	}
};
#endif
