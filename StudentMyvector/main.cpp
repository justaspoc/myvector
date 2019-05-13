#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#if (defined(_WIN32) || defined(_WIN64))
#include <direct.h>
#elif (defined(LINUX) || defined(__linux__))
#include <sys/stat.h>
#endif
#include "student.h"
#include "Vector.h"

using std::cin;
using std::cout;
using std::string;

int main(int argc, char *argv[])
{
#if (defined(_WIN32) || defined(_WIN64))
    mkdir("Results");
#elif (defined(LINUX) || defined(__linux__))
    mkdir("Results", 0777);
#endif
    Vector<student> studentai;
    int pazymiai_kiekis = 0;
    Vector<int> nd;
    if (std::atoi(argv[1]) == 1)
    {
        inputFile.open("Results/kursiokai.txt");
        if (inputFile.fail())
        {
            cout << "Nerastas 'kursiokai.txt' failas. Noredami skaityti pazymius is failo privalote ji susikurti.\n";
        }
        else
        {
            int failo_pabaiga;
            while (failo_pabaiga != 1)
            {
                if (!inputFile.eof())
                {
                    skaityti_pazymius(nd, studentai);
                }
                else
                {
                    failo_pabaiga = 1;
                }
            }
            inputFile.close();
            print(studentai, 1, 0, "0");
        }
    }
    else if (std::atoi(argv[1]) == 2)
    {
        clock_t pradzia, pabaiga;
        pradzia = clock();
        generuoti_studentus();
        pabaiga = clock();
        cout << "Generavimas uztruko: " << pabaiga - pradzia << " tiku(s)\n";
        for (size_t i = 10; i <= 100000; i *= 10)
        {
            pradzia = clock();
            rusiuoti_studentus(i);
            pabaiga = clock();
            cout << i << " studentu rusiavimas uztruko: " << pabaiga - pradzia << " tiku\n";
        }
    }
    else if (std::atoi(argv[1]) == 3)
    {
        Vector<student> laikinas_studentas;
        student laik;
        laikinas_studentas.push_back(laik);
        std::string temp, temp_vardas, temp_pavarde;
        int n, done = 0;

        cout << "Iveskite varda: ";
        std::getline(cin, temp_vardas);
        laikinas_studentas[0].set_vardas(temp_vardas);

        cout << "Iveskite pavarde: ";
        std::getline(cin, temp_pavarde);
        laikinas_studentas[0].set_pavarde(temp_pavarde);

        cout << "Iveskite pazymius(kai baigsit ivesite irasykite 'd', iveskite 'r' jei norite sugeneruoti atsitiktinius pazymius): \n";
        while (!done)
        {
            cin >> temp;
            if (temp == "d")
            {
                done = 1;
            }
            else if (temp == "r")
            {
                cout << "Iveskite kiek pazymiu norite sugeneruoti: ";
                cin >> pazymiai_kiekis;
                using hrClock = std::chrono::high_resolution_clock;
                std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
                std::uniform_int_distribution<int> dist(1, 10);
                for (int i = 0; i < pazymiai_kiekis; i++)
                {
                    nd.push_back(dist(mt));
                }
                nd.push_back(dist(mt));
                done = 1;
            }
            else
            {
                try
                {
                    if (stoi(temp) < 0 || stoi(temp) > 10)
                    {
                        std::cout << "Pazymys turi buti nuo 0 iki 10.\n";
                    }
                    else
                    {
                        nd.push_back(stoi(temp));
                    }
                }
                catch (const std::exception &e)
                {
                    cout << "Neatpazinta komanda! Bandykite vel \n";
                }
            }
        }
        if (temp != "r")
        {
            cout << "Iveskite egzamino rezultata: \n";
            while (true)
            {
                int laikinas;
                std::cin >> laikinas;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Iveskite skaiciu!!\n";
                }
                else if (laikinas < 0 || laikinas > 10)
                {
                    std::cout << "Pazymys turi buti nuo 0 iki 10.\n";
                    continue;
                }
                else
                {
                    nd.push_back(laikinas);
                    break;
                }
            }
        }
        string pasirinkimas;

        pazymiai_kiekis = nd.size() - 1;
        laikinas_studentas[0].set_pazymiai(nd);
        laikinas_studentas[0].galutinis_balas();
        laikinas_studentas[0].mediana_skaiciavimas();

        int teisingai = 0;

        cout << "Pasirinkite koki rezultata norite matyti: vidurki(vid), mediana(med).\n";
        while (!teisingai)
        {
            cin >> pasirinkimas;
            if (pasirinkimas == "med")
            {
                print(laikinas_studentas, 2, laikinas_studentas[0].mediana(), pasirinkimas);
                teisingai = 1;
            }
            else if (pasirinkimas == "vid")
            {
                print(laikinas_studentas, 2, laikinas_studentas[0].galutinis(), pasirinkimas);
                teisingai = 1;
            }
            else
            {
                cout << "Neteisingai ivedete komanda! \n";
            }
        }
        cout << laikinas_studentas[0];
    }
    return 0;
}
