#include <iostream>
#include "API.h"
#include "test.h"
using namespace std;
void useAPI();

int main() {
    useAPI();

    // Test Code

//    test *Test =  new test();
//    Test->readTestQuery();
//    Test->writeTestQuery();
//    Test->deleteTestQuery();
//    Test->queryTopologiesTest();
//    Test->queryDevicesTest();
//    Test->queryDevicesWithNetlistTest();
}

void useAPI(){
    Topology_API *API = new Topology_API();
    printf("****** Welcome to Topology API ******\n");
    while(true){
        int option; string location;
        printf("\nPlease Choose an option:\n1-Read Topology from file.\n2-Write a topology to a JSON file.\n"
               "3-Query about which topologies in memory.\n4-Delete a given topology from memory.\n"
               "5-Query about which devices are in a given topology.\n6-Query about which devices are "
               "connected to a given netlist node in a given topology.\n7-Close The program.\n\nYour Choice: ");
        while(true){
            try{
                cin >> option;
                break;
            }catch (exception E){
                printf("Invalid Input, Please Try again.\nYour Choice: ");
            }
        }

        if(option == 1){
            printf("\nPlease Enter the File specific path Ex:(E://topology.json): ");
            cin >> location;
            try{
                API->readJSON(location);
                printf("Operation Succeeded... You Can Try another operation\n");
            }catch (exception E){
                printf("\nFailed to do Operation that Operation");
            }
        }else if(option == 2){
            printf("Please Enter Topology You want to write: ");
            string topoID;
            cin >> topoID;
            API->writeJSON(topoID);
        }else if(option == 3){
            vector<topology> Topologies = API->queryTopologies();
            while(true){
                cout << "- "<< Topologies.size() << " Founded in the memory, Choose an Option\n"
                                                    "1-Print the topologies IDs.\n2-Continue the Program.\n";
                cin >> option;
                if(option == 1){
                    printf("Topologies IDs: \n");
                    for(int i=0; i<Topologies.size(); i++){
                        cout << " - " << Topologies[i].getID() << "\n";
                    }
                    printf("\n\n");
                }else if(option == 2){
                    break;
                }
            }
        }else if(option == 4){
            string topoID;
            printf("Please enter the topology ID: ");
            cin >> topoID;
            API->deleteTopology(topoID);
        }else if(option == 5){
            string topoID;
            printf("Please enter the topology ID: ");
            cin >> topoID;
            vector<device> Devices= API->queryDevices(topoID);
            while(true){
                cout << Devices.size() << " Devices founded in the memory\n";

                if(Devices.size() > 0)
                    cout << "1-Print the Devices.\n2-Continue the Program.";
                else
                    cout << "press 0 to continue the program.\n";
                cin >> option;
                if(option == 1){
                    printf("Devices: \n");
                    for(int i=0; i<Devices.size(); i++){
                        cout << "- Default: " << Devices[i].getDefault();
                        cout << ", Min: " << Devices[i].getMin();
                        cout << ", Max: " << Devices[i].getMax() << ".\n";
                    }
                    printf("\n");
                }else if(option == 2 || option == 0){
                    break;
                }
            }
        }else if(option == 6){
            string topoID, netList;
            printf("\nPlease enter the topology ID: ");
            cin >> topoID;
            printf("\nPlease enter the NetList: ");
            cin >> netList;
            vector<device> Devices= API->queryDevicesWithNetlistNode(topoID, netList);
            while(true){
                cout << Devices.size() << " Devices founded in the memory\n";

                if(Devices.size() > 0)
                    cout << "1-Print the Devices.\n2-Continue the Program.";
                else
                    cout << "Press 0 to continue the program.\n";

                cin >> option;
                if(option == 1){
                    printf("Devices: \n");
                    for(int i=0; i<Devices.size(); i++){
                        cout << "- Default: " << Devices[i].getDefault();
                        cout << ", Min: " << Devices[i].getMin();
                        cout << ", Max: " << Devices[i].getMax() << ".\n";
                    }
                    printf("\n");
                }else if(option == 2 || option == 0){
                    break;
                }
            }
        }else if(option == 7){
            break;
        }
    }
    printf("Thank you for using Topology API, Have a nice time...");
}
