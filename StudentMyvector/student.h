#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
#include <iostream>
#include "Vector.h"


class zmogus
{
protected:
  std::string vardas_;
  std::string pavarde_;

public:
  virtual void set_vardas(std::string vardas) { vardas_ = vardas; }
  virtual void set_pavarde(std::string pavarde) { pavarde_ = pavarde; }
  std::string vardas() const { return vardas_; }
  std::string pavarde() const { return pavarde_; }
};
class student : public zmogus
{
private:
  double galutinis_;
  double med_;
  Vector<int> pazymiai_;

public:
  student(){};

  //Rule of three
  ~student(){};
  student(const student &stud)
  {
    vardas_ = stud.vardas_;
    pavarde_ = stud.pavarde_;
    galutinis_ = stud.galutinis_;
    med_ = stud.med_;
    pazymiai_ = stud.pazymiai_;
  }
  student operator=(student other)
  {
    std::swap(vardas_, other.vardas_);
    std::swap(pavarde_, other.pavarde_);
    std::swap(galutinis_, other.galutinis_);
    std::swap(med_, other.med_);
    std::swap(pazymiai_, other.pazymiai_);
	return *this;
  }

  //getters
  double galutinis() const { return galutinis_; }
  double mediana() const { return med_; }
  Vector<int> pazymiai() const { return pazymiai_; }

  //setters
  void set_galutinis(double galutinis) { galutinis_ = galutinis; }
  void set_mediana(double mediana) { med_ = mediana; }
  void set_pazymiai(Vector<int> pazymiai) { pazymiai_ = pazymiai; }

  void galutinis_balas();
  void mediana_skaiciavimas();

  friend std::ostream &operator<<(std::ostream &out, const student &stud)
  {
    out << stud.vardas_ << " " << stud.pavarde_ << " " << stud.galutinis_ << "\n";
    return out;
  };
  friend std::istream &operator>>(std::istream &in, student &stud)
  {
    in >> stud.vardas_ >> stud.pavarde_ >> stud.galutinis_;
  }
  friend bool operator==(student a, student b)
  {
    return a == b;
  }
  friend bool operator!=(student a, student b)
  {
    return !(a == b);
  }
};

extern std::ifstream inputFile;

void testinis_irasymas(Vector<student> studentai, std::string failas);
void rusiuoti_studentus(int kiekis);
void generuoti_studentus();
int didziausias_ilgis(Vector<student> studentai, int pasirinkimas);
void skaityti_pazymius(Vector<int> nd, Vector<student> &studentai);
void print(Vector<student> studentai, int pasirinkimas, double galutinis, std::string rezultatas);
#endif