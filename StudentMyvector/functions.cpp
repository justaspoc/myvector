#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <chrono>
#include <sstream>
#include "student.h"
#include "Vector.h"

std::ifstream inputFile;
void testinis_irasymas(Vector<student> studentai, std::string failas)
{
    std::ofstream output;
    output.open(failas);
    int kiekis = studentai.size();

    for (size_t x = 0; x < kiekis; x++)
    {
        output << studentai[x].vardas() << " ";
        output << studentai[x].pavarde() << " ";
        output << std::setprecision(3) << studentai[x].galutinis() * 1.00 << "\n";
    }
    output.close();
    
}
void rusiuoti_studentus(int kiekis)
{
    std::string nuskaitymo_failas = "Results/" + std::to_string(kiekis) + ".txt";
    std::string vargsiukai_failas = "Results/vargsiukai" + std::to_string(kiekis) + ".txt";
    std::string smegenociai_failas = "Results/smegenociai" + std::to_string(kiekis) + ".txt";

    Vector<student> vargsiukai, smegenociai, studentai;
    std::string vardas, pavarde;
    double galutinis;
    student temp_studentas;
    std::ifstream inputFile;

    inputFile.open(nuskaitymo_failas);

    for (size_t x = 0; x < kiekis; x++)
    {
        inputFile >> vardas;
        temp_studentas.set_vardas(vardas);
        inputFile >> pavarde;
        temp_studentas.set_pavarde(pavarde);
        inputFile >> galutinis;
        temp_studentas.set_galutinis(galutinis);
        studentai.push_back(temp_studentas);
    }
    for (size_t i = 0; i < kiekis; i++)
    {
        if (studentai[i].galutinis() < 5.0)
        {
            vargsiukai.push_back(studentai[i]);
        }
        else
        {
            smegenociai.push_back(studentai[i]);
        }
    }
    testinis_irasymas(smegenociai, smegenociai_failas);
    testinis_irasymas(vargsiukai, vargsiukai_failas);

    smegenociai.clear();
    vargsiukai.clear();
    studentai.clear();
    inputFile.close();
}

void generuoti_studentus()
{
    student studentas;
    Vector<int> pazymiai;
    std::string failas;
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);
    for (size_t x = 10; x <= 100000; x *= 10)
    {
        failas = "Results/" + std::to_string(x) + ".txt";
        std::ofstream outputFile;
        outputFile.open(failas);
        for (size_t y = 0; y < x; y++)
        {
            studentas.set_vardas("vardas" + std::to_string(y + 1));
            studentas.set_pavarde("pavarde" + std::to_string(y + 1));
            for (size_t z = 0; z <= 5; z++)
            {
                pazymiai.push_back(dist(mt));
            }
            studentas.set_pazymiai(pazymiai);
            studentas.galutinis_balas();
            pazymiai.clear();
            outputFile << studentas.vardas() << " " << studentas.pavarde() << " ";
            outputFile << std::fixed << std::setprecision(2) << studentas.galutinis() << "\n";
        }
        outputFile.close();
    }
}

int didziausias_ilgis(Vector<student> studentai, int pasirinkimas)
{
    int laikinas_ilgis, ilgis;
    ilgis = studentai.size();
    if (pasirinkimas == 1)
    {
        laikinas_ilgis = 6;
    }
    else if (pasirinkimas == 2)
    {
        laikinas_ilgis = 7;
    }
    for (int i = 0; i < ilgis; i++)
    {
        if (pasirinkimas == 1 && studentai[i].vardas().length() > laikinas_ilgis)
        {
            laikinas_ilgis = studentai[i].vardas().length();
        }
        else if (pasirinkimas == 2 && studentai[i].pavarde().length() > laikinas_ilgis)
        {
            laikinas_ilgis = studentai[i].pavarde().length();
        }
    }
    return laikinas_ilgis;
}

void print(Vector<student> studentai, int pasirinkimas, double galutinis, std::string rezultatas)
{
    if (pasirinkimas == 1)
    {
        std::ofstream outputFile;
        outputFile.open("Results/rezultatas.txt");
        int irasu_kiekis = studentai.size();
        std::cout << irasu_kiekis;
        outputFile << std::left << std::setw(didziausias_ilgis(studentai, 1) + 3) << "Vardas";
        outputFile << std::left << std::setw(didziausias_ilgis(studentai, 2) + 3) << "Pavarde";
        outputFile << std::fixed << std::setw(19) << std::setprecision(2) << "Galutinis (vid.)";
        outputFile << std::fixed << std::setw(10) << std::setprecision(2) << "Galutinis (med.)\n";
        for (int x = 1; x <= ((didziausias_ilgis(studentai, 1) + 3) + (didziausias_ilgis(studentai, 2) + 3) + 35); x++)
        {
            outputFile << "-";
        }
        outputFile << "\n";
        for (int x = 0; x < irasu_kiekis; x++)
        {
            outputFile << std::left << std::setw(didziausias_ilgis(studentai, 1) + 3) << studentai[x].vardas();
            outputFile << std::left << std::setw(didziausias_ilgis(studentai, 2) + 3) << studentai[x].pavarde();
            outputFile << std::fixed << std::setw(19) << std::setprecision(2) << studentai[x].galutinis();
            outputFile << std::fixed << std::setw(19) << std::setprecision(2) << studentai[x].mediana();
            outputFile << "\n";
        }
        outputFile.close();
    }
    else if (pasirinkimas == 2)
    {
        std::cout << std::left << std::setw(didziausias_ilgis(studentai, 1) + 3) << "Vardas";
        std::cout << std::left << std::setw(didziausias_ilgis(studentai, 2) + 3) << "Pavarde";
        std::cout << std::fixed << std::setw(10) << std::setprecision(2) << "Galutinis (" << rezultatas << ".)\n";
        for (int x = 1; x <= ((didziausias_ilgis(studentai, 1) + 3) + (didziausias_ilgis(studentai, 2) + 3) + 16); x++)
        {
            std::cout << "-";
        }
        std::cout << "\n";
        std::cout << std::left << std::setw(didziausias_ilgis(studentai, 1) + 3) << studentai[0].vardas();
        std::cout << std::left << std::setw(didziausias_ilgis(studentai, 2) + 3) << studentai[0].pavarde();
        std::cout << std::fixed << std::setw(15) << std::setprecision(2) << galutinis;
        std::cout << "\n";
    }
}

void skaityti_pazymius(Vector<int> nd, Vector<student> &studentai)
{
    int temp;
    student temp_studentas;
    std::string vardas, pavarde, input;
    std::getline(inputFile, input);
    std::stringstream stream(input);

    stream >> vardas >> pavarde;
    temp_studentas.set_vardas(vardas);
    temp_studentas.set_pavarde(pavarde);

    while (true)
    {
        stream >> temp;
        if (!stream)
        {
            break;
        }
        nd.push_back(temp);
    }
    temp_studentas.set_pazymiai(nd);
    temp_studentas.mediana_skaiciavimas();
    temp_studentas.galutinis_balas();
    studentai.push_back(temp_studentas);
    nd.clear();
}
