#include "test.h"

test::test() {

}

void test::readTestQuery() {
    cout << "Reading Tests\n";
    cout << " - Test 1\n";
    if (topologyAPI.readJSON("")){
        cout << "TEST Failed\n";
    }else{
        cout << "Test Passed\n";
    }

    cout << " - Test 2\n";
    if (topologyAPI.readJSON("topology.json")){
        cout << "TEST Passed\n";
    }else{
        cout << "Test Failed\n";
    }

    cout << " - Test 3\n";
    if (topologyAPI.readJSON("E://topology.json")){
        cout << "TEST Passed\n";
    }else{
        cout << "Test Failed\n";
    }
}

void test::writeTestQuery() {
    cout << "Writing Tests\n";
    topologyAPI.readJSON("E://topology.json");
    cout << "Writing Tests\n";
    cout << " - Test 1\n";
    if (topologyAPI.writeJSON("")){
        cout << "TEST Failed\n";
    }else{
        cout << "Test Passed\n";
    }
}

void test::deleteTestQuery() {
    cout << "Deleting Test\n";
    cout << " - Test 1\n";
    topologyAPI.readJSON("E://topology.json");
    topologyAPI.deleteTopology("top1");
    if(topologyAPI.getTopologiesNumber() == 0){
        cout << "Test Passed\n";
    }else{
        cout << "Test Failed\n";
    }
}

void test::queryTopologiesTest() {
    cout << "Query Topologies Test\n";
    cout << " - Test 1\n";
    topologyAPI.readJSON("E://topology.json");
    vector<topology> Topologies = topologyAPI.queryTopologies();
    if(Topologies.size() == 0){
        cout << "Test Failed\n";
    }else{
        cout << "Test Passed\n";
    }
}

void test::queryDevicesTest() {
    cout << "Query Devices Test\n";
    cout << " - Test 1\n";
    topologyAPI.readJSON("E://topology.json");
    vector<device> Devices = topologyAPI.queryDevices("top1");
    if(Devices.size() == 0){
        cout << "Test Failed\n";
    }else{
        cout << "Test Passed\n";
    }
}

void test::queryDevicesWithNetlistTest() {
    cout << "Query Devices with NetList Test\n";
    cout << " - Test 1\n";
    topologyAPI.readJSON("E://topology.json");
    vector<device> Devices = topologyAPI.queryDevicesWithNetlistNode("top1", "vdd");
    if(Devices.size() == 0){
        cout << "Test Failed\n";
    }else{
        cout << "Test Passed\n";
    }
}
