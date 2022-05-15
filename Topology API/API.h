#include "topology.h"
#include "component.h"
#ifndef TOPOLOGY_API_API_H
#define TOPOLOGY_API_API_H
class Topology_API {
private:
    vector<topology_list> Topologies;
public:
    Topology_API();
    void readJSON(string FilePath);
    void writeJSON(string topologyID);
    vector<topology_list> queryTopologies();
    topology_list deleteTopology(string topologyID);
    vector<device> queryDevices(string topologyID);
    vector<device> queryDevicesWithNetlistNode(string topologyID, string netListID);
};
#endif //TOPOLOGY_API_API_H
