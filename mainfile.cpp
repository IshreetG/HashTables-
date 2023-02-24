#include <iostream>
#include <vector>
#include "openhash.h"
#include "ordhash.h"

using namespace std;

int main() {
    string command;
    int N, P,m,x;
    long PID, ADDR;
    hashtable a; 
    hashtable2 a2; 
    
    cin >> command;
    if(command == "OPEN"){
        while(cin >> command){

            if(command == "M"){
                cin >> N;
                cin >> P;
                a.create(N,P);
                cout << "success" << endl;
            }
            if(command == "INSERT"){
                cin >> PID;
                a.insert(PID);
            }
            if(command == "DELETE"){
                cin >> PID;
                a.deletekey(PID);
            }
            
            if(command == "SEARCH"){
                cin >> PID;
                a.search(PID);
            }
            if(command == "WRITE"){
                cin >> PID;
                cin >> ADDR;
                cin >> x;
                a.write(PID, ADDR, x);
                
            }
            if(command == "READ"){
                cin >> PID;
                cin >> ADDR;
                a.read(PID, ADDR);
                
            }

            if(command == "END"){
               // a.deallocate_hashtable();
                return 0;
            }

    }
    }

     if(command == "ORDERED"){
        while(cin >> command){

            if(command == "M"){
                cin >> N;
                cin >> P;
                a2.create(N,P);
                cout << "success" << endl;
            }
            if(command == "INSERT"){
                cin >> PID;
                a2.insert(PID);
            }
            if(command == "DELETE"){
                cin >> PID;
                a2.deletekey(PID);
            }
            
            if(command == "SEARCH"){
                cin >> PID;
                a2.search(PID);
            }
            if(command == "WRITE"){
                cin >> PID;
                cin >> ADDR;
                cin >> x;
                a2.write(PID, ADDR, x);
                
            }
            if(command == "READ"){
                cin >> PID;
                cin >> ADDR;
                a2.read(PID, ADDR);
                
            }
             if(command == "PRINT"){
                cin >> m;
                a2.print(m);
                
            }
            if(command == "END"){
                a2.deallocate_hashtable();
                return 0;
            }

}
     }
     return 0;
}