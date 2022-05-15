#include "component.h"
component::component() {

}

component::component(string type, string id, device Device, unordered_map<string, string> netList) {
    this->type = type;
    this->id = id;
    this->Device = Device;
    this->netList = netList;
}
// Setters
void component::setDevice(device Device) {
    this->Device = Device;
}

void component::setNetlist(unordered_map<string, string> netlist) {
    this->netList = netlist;
}

device component::getDevice() {
    return this->Device;
}

unordered_map<string, string> component::getNetlist() {
    return this->netList;
}

void component::setType(string type) {
    this->type = type;
}

void component::setID(string id) {
    this->id = id;
}

string component::getType() {
    return this->type;
}

string component::getID() {
    return this->id;
}
