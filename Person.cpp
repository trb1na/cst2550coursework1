#include "Person.h"

std::string Person::address() {
	return str_address;
}

std::string Person::email() {
	return str_email;
}

std::string Person::name() {
	return str_name;
}

void Person::setAddress(std::string newaddress) {
	str_address = newaddress;
}

void Person::setEmail(std::string newemail) {
	str_email = newemail;
}

void Person::setName(std::string newname) {
	str_name = newname;
}