#include "topology.h"


void topology_list::setId(string id) {
    this->id = id;
}

void topology_list::addComponent(component *comp) {
    components.push_back(*comp);
}

string topology_list::getID() {
    return this->id;
}

vector<component> topology_list::getComponents() {
    return components;
}
