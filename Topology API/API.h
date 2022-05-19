#include <fstream>
#include "json.hpp"

#include "topology.h"
#include "component.h"
#include "Device.h"


#ifndef TOPOLOGY_API_API_H
#define TOPOLOGY_API_API_H
class Topology_API {
private:
    vector<topology> Topologies;
public:
    Topology_API();
    bool readJSON(string FilePath);
    bool writeJSON(string topologyID);
    vector<topology> queryTopologies();
    topology deleteTopology(string topologyID);
    vector<device> queryDevices(string topologyID);
    vector<device> queryDevicesWithNetlistNode(string topologyID, string netListID);
    int getTopologiesNumber();
};
#endif //TOPOLOGY_API_API_H
