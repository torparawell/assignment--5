#include "Assignment-5.h"

Person::Person() {
    id = -1;
    level = "null";
}

Person::Person(int id, string level) {
    this->id = id;
    this->level = level;
}

Person::~Person() {
    // Bye bye person.
}