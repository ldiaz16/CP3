#include "Voter.h"

Voter::Voter(string firstname, string lastname, unsigned int voterage) {
        first = firstname;
        last = lastname;
        age = voterage;
}

Voter::Voter() {
        first = "";
        last = "";
        age = 0;
}

void Voter::show() const {
        cout << last << ", " << first << ": " << age << endl;
}

bool Voter::operator==(const Voter& other) const {
  return (first == other.first && last == other.last && age == other.age);
}
bool Voter::operator!=(const Voter& other) const {
  return !(*this == other);
}

bool Voter::operator<(const Voter& other) const {
  return age < other.age;
}

bool Voter::operator>(const Voter& other) const {
  return age > other.age;
}

bool Voter::operator>=(const Voter& other) const {
    return age >= other.age;
}

bool Voter::operator<=(const Voter& other) const {
    return age <= other.age;
}

ostream& operator<<(ostream& os, const Voter& voter) {
    os << voter.last << ", " << voter.first << ": " << voter.age;
    return os;
}


