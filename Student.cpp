#include "Student.h"

Student::Student(const string &name, const  string &id, double gpa) {
    this->name = name;
    this->id = id;
    this->gpa = gpa;
}

void Student::setName(const string &newName) {
    name = newName;
}

void Student::setId(const string &newId) {
    id = newId;
}

void Student::setGpa(const double &newGpa) {
    gpa = newGpa;
}

string Student::getName() const {return name;}

string Student::getId() const {return id;}

double Student::getGpa() const {return gpa;}

bool Student::operator<(const Student &other) const {
    return this->getName() < other.getName();
}