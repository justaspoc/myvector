#include "student.h"
#include "Vector.h"
#include <algorithm>

void student::galutinis_balas(){
    int kiekis = pazymiai_.size() - 1;
    int suma = 0;
    if (kiekis != 0)
    {
        for (int x = 0; x < kiekis; x++)
        {
            suma += pazymiai_[x];
        }
        galutinis_ = 0.4 * suma / kiekis + 0.6 * pazymiai_[kiekis];
    }
    else
        galutinis_ = 0.6 * pazymiai_[kiekis];
}

void student::mediana_skaiciavimas(){
    size_t size = pazymiai_.size();
    if (size != 0)
    {
        //sort(pazymiai_.begin(), pazymiai_.end());
        if (size % 2 == 0)
        {
            med_ = (double)((pazymiai_[size / 2 - 1] + pazymiai_[size / 2]) * 0.5);
        }
        else
        {
            med_ = pazymiai_[size / 2];
        }
    }
}
