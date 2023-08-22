//This is a class representing a student entity
#ifndef SOLUTION_STUDENT_H
#define SOLUTION_STUDENT_H
#include <string>
using namespace std;
class Student {
private:
    string id;
    string name;
    double gpa;
public:
    Student(const string &name, const string &id, double gpa);
    void setId(const string &newId);
    void setName(const string &newName);
    void setGpa (const double &newGpa);
    [[nodiscard]] string getId () const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] double getGpa() const;
    bool operator<(const Student &other) const;
};


#endif //SOLUTION_STUDENT_H
