#include "topology.h"


void topology::setId(string id) {
    this->id = id;
}

void topology::addComponent(component *comp) {
    components.push_back(*comp);
}

string topology::getID() {
    return this->id;
}

vector<component> topology::getComponents() {
    return components;
}
