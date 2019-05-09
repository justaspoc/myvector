# MyVector
## Funkcionalumo tikrinimas
### Erase
```c++
void erase(pointer first, pointer last)
    {
        value_type *temp = first;
        pointer f = &array[first - array];
        for (; first != last; ++first)
            (*first).~T();
        memmove(f, last, (vsize - (last - array)) * sizeof(T));
        vsize -= last - temp;
    }
```
```shell
10
12
51
-12
45

//vec.erase(vec.begin(),vec.begin()+3);

-12
45
```
### Allocate
```c++
inline void alloc_new()
    {
        maxsize = vsize + 20;
        T *tarr = new T[maxsize];
        memcpy(tarr, array, vsize * sizeof(T));
        delete[] array;
        array = tarr;
    }
```
```shell
maxsize = 20

//vector.alloc_new();

maxsize = 40

```
### Insert
```c++
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
```
```shell
1
2
3
4
5

//vec.insert(vec.begin()+2, 2000);

1
2
2000
3
4
5
```
### Assign
```c++
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
```
```shell
1
2
3
4
5

//vec.assign(5,10);

1
2
3
4
5
10
10
10
10
10
```
### Pop_back
```c++
void pop_back()
    {
        vsize = vsize - 1;
        value_type *tmp = new value_type[maxsize];
        for (int i = 0; i < vsize; i++)
            tmp[i] = array[i];
        delete[] array;
        array = tmp;
    };
 ```
 ```shell
1
2
3
4
5

//vec.pop_back();

1
2
3
4
 ```
 ## Efektyvumo/spartos analize
 
|          	| 10000 	| 100000 	| 1000000 	| 10000000 	| 100000000 	|
|----------	|-------	|--------	|---------	|----------	|-----------	|
| Vector   	| 1     	| 2      	| 17      	| 201      	| 2230      	|
| Myvector 	| 1      	| 1       	| 9        	| 116         	| 1111          	|

## Atminties perskirstymai

|               	| Vector 	| Myvector 	|
|---------------	|--------	|----------	|
| Perskirstymai 	| 28     	| 23       	|


