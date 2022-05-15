#ifndef TOPOLOGY_API_COMPONENT_H
#define TOPOLOGY_API_COMPONENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "Device.h"

using namespace std;

class component{
private:
    string type;
    string id;
    device Device;
    unordered_map<string, string> netList;

public:
    // Constructors
    component();
    component(string type, string id, device Device, unordered_map<string, string> netList);

    // Setters
    void setType(string type);
    void setID(string id);
    void setNetlist(unordered_map<string, string> netlist);
    void setDevice(device Device);

    // Getters
    string getType();
    string getID();
    unordered_map<string, string> getNetlist();
    device getDevice();

    };

#endif //TOPOLOGY_API_COMPONENT_H
