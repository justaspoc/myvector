#include <iostream>
#include "Vector.h"
#include "time.h"
#include <vector>
#include <string>
#include <iterator>

int main()
{
    /*
    Vector<int> vec;
    int tmp;int x = 0;

    while (x < 5)
    {
        if (x == 5)
            break;

        std::cin >> tmp;
        vec.push_back(tmp);
        x++;
    }
    std::cout << "OOga booga " << vec.size() << " elem\n";
    for (int i = 0; i < vec.size(); i++)

        std::cout << vec[i] << "\n";

    std::cout << "\n";
    vec.erase(vec.begin()+1);
    for (int i = 0; i < vec.size(); i++)

        std::cout << vec[i] << "\n";
    
   */
    clock_t pradzia, pabaiga;
    Vector<int> v;
    std::vector<int> a;
    pradzia = clock();
    for (size_t i = 0; i < 100000; i++)
    {
        v.push_back(i);
    }
    std::cout << v[1000] << "\n";
    pabaiga = clock();
    std::cout << pabaiga - pradzia;
    
    return 0;
    
}