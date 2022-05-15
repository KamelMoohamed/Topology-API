#include "API.h"
#include "json.hpp"
#include <fstream>
#include "component.h"
#include "Device.h"

Topology_API::Topology_API() {

}

void Topology_API::readJSON(string FilePath) {
fstream file(FilePath);
    try {
        nlohmann::json jsonFile = nlohmann::json::parse(file);
        topology_list topology;
        topology.setId(jsonFile["id"]);
        for(int i = 0; i<jsonFile["components"].size(); i++){
            if(jsonFile["components"][i]["type"] == "resistor"){
                device *Device = new device(jsonFile["components"][i]["resistance"]["default"],
                                           jsonFile["components"][i]["resistance"]["min"],
                                           jsonFile["components"][i]["resistance"]["max"]);

                unordered_map<string, string> netList;
                netList.insert({"t1", jsonFile["components"][i]["netlist"]["t1"]});
                netList.insert({"t2", jsonFile["components"][i]["netlist"]["t2"]});

                component *comp = new component("resistor",
                                                jsonFile["components"][i]["id"],
                                                *Device, netList);
                topology.addComponent(comp);
            }else{

                device *Device = new device(jsonFile["components"][i]["m(l)"]["default"],
                                            jsonFile["components"][i]["m(l)"]["min"],
                                            jsonFile["components"][i]["m(l)"]["max"]);

                unordered_map<string, string> netList;
                netList.insert({"drain", jsonFile["components"][i]["netlist"]["drain"]});
                netList.insert({"gate", jsonFile["components"][i]["netlist"]["gate"]});
                netList.insert({"source", jsonFile["components"][i]["netlist"]["source"]});

                component *comp = new component(jsonFile["components"][i]["type"],
                                                jsonFile["components"][i]["id"],
                                                *Device, netList);




                topology.addComponent(comp);
            }
        }
        Topologies.push_back(topology);
    }catch (exception){
        cout << "Invalid to read the file...";
    }
}

void Topology_API::writeJSON(string topologyID) {
    if(Topologies.size() == 0){
        cout << "\nThere is no topologies to write...";
        return;
    }
    cout << "Please enter the file path and name (with extension .json): ";
    string filePath;
    cin >> filePath;

    ofstream o(filePath);
    topology_list Topology;
    bool Found = false;
    for(int i=0; i<Topologies.size(); i++){
        if(Topologies[i].getID() == topologyID){
            Topology = Topologies[i];
            Found = true;
            break;
        }
    }


    // Writing the topology to a JSON File
    if(Found) {
        o << "{\n";
        o << R"( "id": ")" + Topology.getID() + + R"(",)" + "\n";
        o << R"( "components" :[)";
        o << "\n";
        vector<component> components = Topology.getComponents();
        for(int i=0; i<components.size(); i++){
            if(i != 0){
                o << ",\n";
            }
            o << "\t{\n\t";
            o << R"("type": )";
            if(components[i].getType() == "resistor"){
                o << "\"" + components[i].getType() + "\",\n\t";
                o << R"("id": ")";
                o << components[i].getID() << "\",\n\t";
                o << R"("resistance": {)";
                o << "\n\t\t";
                o << R"("default": )" << components[i].getDevice().getDefault() << ",\n\t\t";
                o << R"("min": )" << components[i].getDevice().getMin() << ",\n\t\t";
                o << R"("max": )" << components[i].getDevice().getMax() << "\n\t\t";
                o << "},\n\t\t";
                o << R"("netlist": {)";
                unordered_map<string, string> netList = components[i].getNetlist();
                int count = 1;
                for(auto j: netList){
                    o << "\"" + j.first + "\": \"" + j.second + "\"";
                    if(count != netList.size()){
                        o << ",\n\t\t";
                    }
                    count++;
                }
                o << "}\n}";
            }else{
                o << "\"" + components[i].getType() + "\",\n\t";
                o << R"("id": ")";
                o << components[i].getID() << "\",\n\t";
                o << "\"m(l)\": {\n\t\t";
                o << R"("default": )" << components[i].getDevice().getDefault() << ",\n\t\t";
                o << R"("min": )" << components[i].getDevice().getMin() << ",\n\t\t";
                o << R"("max": )" << components[i].getDevice().getMax() << "\n\t";
                o << "},";
                o << R"("netlist": {)";
                unordered_map<string, string> netList = components[i].getNetlist();
                int count = 1;
                for(auto j: netList){
                    o << "\"" + j.first + "\": \"" + j.second + "\"";
                    if(count != netList.size()){
                        o << ",\n\t\t";
                    }
                    count++;
                }
                o << "}\n\t}";
            }
        }
        o << "\n]\n}";
    }else{
        cout << "\nThere is no topologies with that ID...";
    }
}

vector<topology_list> Topology_API::queryTopologies() {
    return Topologies;
}

topology_list Topology_API::deleteTopology(string topologyID) {
    bool Found = false;
    topology_list Topo;
    for(int i=0; i<Topologies.size(); i++){
        if(Topologies[i].getID() == topologyID){
            Topo = Topologies[i];
            Found = true;
            if(i != Topologies.size()-1){
                for(int j=i; j<Topologies.size(); j++){
                    Topologies[i] = Topologies[i+1];
                }
            }
            Topologies.pop_back();
        }
    }
    if(Found)
        return Topo;
    else
        return {};
}

vector<device> Topology_API::queryDevices(string topologyID) {
    bool Found = false;
    topology_list Topology;
    vector<component> outputDevices;
    for(int i=0; i<Topologies.size(); i++){
        if(Topologies[i].getID() == topologyID){
            Topology = Topologies[i];
            Found = true;
            break;
        }
    }
    if(Found){
        vector<device> Devices;
        for(auto j : Topology.getComponents()){
            Devices.push_back(j.getDevice());
        }
        return Devices;
    }else{
        return {};
    }
}

vector<device> Topology_API::queryDevicesWithNetlistNode(string topologyID, string netListID) {
    bool Found = false;
    topology_list Topology;
    vector<device> outputDevices;
    for(int i=0; i<Topologies.size(); i++){
        if(Topologies[i].getID() == topologyID){
            Topology = Topologies[i];
            Found = true;
            break;
        }
    }
    if(Found){
        vector<component> components = Topology.getComponents();
        for(int i=0; i< components.size(); i++){
            unordered_map<string, string> netList = components[i].getNetlist();
            bool netConnected = false;
            for(auto i:netList){
                if(i.second == netListID){
                    netConnected = true;
                    break;
                }
            }
            if(netConnected)
                outputDevices.push_back(components[i].getDevice());
        }
        return outputDevices;
    }else{
        return {};
    }
}