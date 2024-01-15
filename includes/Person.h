#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:

  std::string str_name;
  std::string str_address;
  std::string str_email;

public:

  std::string name();
  std::string address();
  std::string email();

  void setName(std::string name);
  void setAddress(std::string address);
  void setEmail(std::string email);

};

#endif