#include "API.h"
//#include "topology.h"
//#include "Device.h"
//#include ""
#ifndef TOPOLOGY_API_TEST_H
#define TOPOLOGY_API_TEST_H
class test{
private:
    Topology_API topologyAPI;
public:
    test();
    void readTestQuery();
    void writeTestQuery();
    void deleteTestQuery();
    void queryTopologiesTest();
    void queryDevicesTest();
    void queryDevicesWithNetlistTest();
};
#endif //TOPOLOGY_API_TEST_H
