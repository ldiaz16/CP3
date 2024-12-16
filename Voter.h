#ifndef _H_Voter_
#define _H_Voter_

#include <iostream>
#include <stdlib.h>
using namespace std;

class Voter {
   private:
      string first = "";
      string last = "";
      unsigned int age = 0;
   public:
      Voter(string firstname, string lastname, unsigned int voterage);
      Voter();
      void show() const;
  bool operator==(const Voter& other) const;
  bool operator!=(const Voter& other) const;
  bool operator<(const Voter& other) const;
  bool operator>(const Voter& other) const;
  bool operator>=(const Voter& other) const;
  bool operator<=(const Voter& other) const;
  friend ostream& operator<<(ostream& os, const Voter& voter);

};

#endif





