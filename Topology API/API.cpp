#include "API.h"


Topology_API::Topology_API() {

}

void Topology_API::readJSON(string FilePath) {
fstream file(FilePath);
    try {
        nlohmann::json jsonFile = nlohmann::json::parse(file);
        topology Topology;
        Topology.setId(jsonFile["id"]);
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
                Topology.addComponent(comp);
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




                Topology.addComponent(comp);
            }
        }
        Topologies.push_back(Topology);
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

    ofstream output(filePath);
    topology Topology;
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
        output << "{\n";
        output << R"( "id": ")" + Topology.getID() + + R"(",)" + "\n";
        output << R"( "components" :[)";
        output << "\n";
        vector<component> components = Topology.getComponents();
        for(int i=0; i<components.size(); i++){
            if(i != 0){
                output << ",\n";
            }
            output << "\t{\n\t";
            output << R"("type": )";
            if(components[i].getType() == "resistor"){
                output << "\"" + components[i].getType() + "\",\n\t";
                output << R"("id": ")";
                output << components[i].getID() << "\",\n\t";
                output << R"("resistance": {)";
                output << "\n\t\t";
                output << R"("default": )" << components[i].getDevice().getDefault() << ",\n\t\t";
                output << R"("min": )" << components[i].getDevice().getMin() << ",\n\t\t";
                output << R"("max": )" << components[i].getDevice().getMax() << "\n\t\t";
                output << "},\n\t\t";
                output << R"("netlist": {)";
                unordered_map<string, string> netList = components[i].getNetlist();
                int count = 1;
                for(auto j: netList){
                    output << "\"" + j.first + "\": \"" + j.second + "\"";
                    if(count != netList.size()){
                        output << ",\n\t\t";
                    }
                    count++;
                }
                output << "}\n}";
            }else{
                output << "\"" + components[i].getType() + "\",\n\t";
                output << R"("id": ")";
                output << components[i].getID() << "\",\n\t";
                output << "\"m(l)\": {\n\t\t";
                output << R"("default": )" << components[i].getDevice().getDefault() << ",\n\t\t";
                output << R"("min": )" << components[i].getDevice().getMin() << ",\n\t\t";
                output << R"("max": )" << components[i].getDevice().getMax() << "\n\t";
                output << "},";
                output << R"("netlist": {)";
                unordered_map<string, string> netList = components[i].getNetlist();
                int count = 1;
                for(auto j: netList){
                    output << "\"" + j.first + "\": \"" + j.second + "\"";
                    if(count != netList.size()){
                        output << ",\n\t\t";
                    }
                    count++;
                }
                output << "}\n\t}";
            }
        }
        output << "\n]\n}";
        cout << "\n Successfully Wrote topology to the file";
    }else{
        cout << "\nThere is no topologies with that ID...";
    }
}

vector<topology> Topology_API::queryTopologies() {
    return Topologies;
}

topology Topology_API::deleteTopology(string topologyID) {
    bool Found = false;
    topology Topo;
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
    if(Found) {
        cout << "\nSuccessfully Deleted the topology from the memory...\n";
        return Topo;
    }
    else{
        cout << "\nNo Topology with that ID...\n";
        return {};
    }
}

vector<device> Topology_API::queryDevices(string topologyID) {
    bool Found = false;
    topology Topology;
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
    topology Topology;
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