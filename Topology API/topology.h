#ifndef TOPOLOGY_API_TOPOLOGY_H
#define TOPOLOGY_API_TOPOLOGY_H

#include <bits/stdc++.h>
#include "component.h"
using namespace std;

class topology {
private:
    string id;
    vector<component> components;

public:
    void setId(string id);
    string getID();
    void addComponent(component *comp);
    vector<component> getComponents();
};

#endif //TOPOLOGY_API_TOPOLOGY_H
