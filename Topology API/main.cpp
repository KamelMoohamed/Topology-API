#include <iostream>
#include "API.h"
using namespace std;

int main() {
    Topology_API *topo = new Topology_API();
    topo->readJSON("E:/hi.json");
    topo->deleteTopology("top1");
    topo->writeJSON("top1");
}
