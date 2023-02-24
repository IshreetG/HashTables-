#include "openhash.h"
#include <iostream>
#include <cmath> 
#include <vector>

using namespace std;

process::process(int PID, int ADDR){
    processid = PID;
    startaddress = ADDR;
}

process::~process(){ }

hashtable::hashtable(){
    int count = 0;
}
hashtable::~hashtable(){ 
    for(int i = 0; i < m; i++){
        if(htable[i] != nullptr){
            delete htable[i];
        }
    }
}

void hashtable::create(int N, int P){
    m = N/P;
    total_mem_size = N;
    page_size = P;
    mem_array.resize(N); //create an array with size N to represent all memory
    htable.resize(m);

}

//is double hashing algorith is correct here?
int hashtable::calculate_probe(long PID){

    int h1 = PID % htable.capacity();
    int h2 = int(floor(PID / htable.capacity())) % htable.capacity();
    int probe;

    if (h2 % 2 == 0){
        h2 += 1; // h2 must be odd so if it is even we do + 1
    }
    //since htable is not at capacitiy we must be able to hash
    // ℎ(𝑘,𝑖)=(ℎ1(𝑘)+𝑖∗ℎ2(𝑘)) 𝑚𝑜𝑑 𝑚,
    int i = 0;
    probe = (h1 + i*h2) % m;

    while(htable[probe] != nullptr && i < m) {
        if(htable[probe]->processid == PID) { //this means that it already exists 
            return -1;
        }
        i += 1;
        probe = (h1 + i*h2) % m;;
    }

    if(htable[probe] == nullptr){
        // found empty slot in hashtable, can add process in it
        return probe;
    }
    //hashtable is at capacity then return failure

    return -1; 

}

// there is one edge case where do of the same process can be inserted, don't know how to fix it without making runntime worse
void hashtable::insert(long PID){
    int probe =  calculate_probe(PID);

    if (probe == -1){
        cout << "failure" << endl;
        return; 
    }

    htable[probe] = new process(PID, probe * page_size);
    count = count +1; //update count
    cout << "success" << endl;
    return;
}

// every function below is correct but runtime is not good(assignment asks for  constant)
void hashtable::search(long PID){

    int h1 = PID % htable.capacity();
    int h2 = int(floor(PID / htable.capacity())) % htable.capacity();
    int probe;

    if (h2 % 2 == 0){
        h2 += 1; // h2 must be odd so if it is even we do + 1
    }
    //since htable is not at capacitiy we must be able to hash
    // ℎ(𝑘,𝑖)=(ℎ1(𝑘)+𝑖∗ℎ2(𝑘)) 𝑚𝑜𝑑 𝑚,
    int i = 0;
    probe = (h1 + i*h2) % m;

    while( i < m) {
        if(htable[probe] != nullptr && htable[probe]->processid == PID) {
           cout << "found " << PID << " in " << probe << endl;
           return;
        }
        i += 1;
        probe = (h1 + i*h2) % m;;
    }
    
    cout << "not found" << endl;
    return; 

}

void hashtable::deletekey(long PID) {
    int h1 = PID % htable.capacity();
    int h2 = int(floor(PID / htable.capacity())) % htable.capacity();
    int probe;

    if (h2 % 2 == 0){
        h2 += 1; // h2 must be odd so if it is even we do + 1
    }
    //since htable is not at capacitiy we must be able to hash
    // ℎ(𝑘,𝑖)=(ℎ1(𝑘)+𝑖∗ℎ2(𝑘)) 𝑚𝑜𝑑 𝑚,
    int i = 0;
    probe = (h1 + i*h2) % m;

    while(i < m) {
        if(htable[probe] != nullptr && htable[probe]->processid == PID) { 
            delete htable[probe];
            htable[probe] = nullptr;  // set it back to nullptr
            count = count -1;
            cout << "success" << endl;
           return;
        }
        i += 1;
        probe = (h1 + i*h2) % m;;
    }
    
    cout << "failure" << endl;
    return; 

}

void hashtable::write(long PID, long ADDR, int x) {

    if(ADDR >= page_size || ADDR < 0){
        cout << "failure" << endl;
        return;
    }

    int h1 = PID % htable.capacity();
    int h2 = int(floor(PID / htable.capacity())) % htable.capacity();
    int probe;

    if (h2 % 2 == 0){
        h2 += 1; // h2 must be odd so if it is even we do + 1
    }
    //since htable is not at capacitiy we must be able to hash
    // ℎ(𝑘,𝑖)=(ℎ1(𝑘)+𝑖∗ℎ2(𝑘)) 𝑚𝑜𝑑 𝑚,
    int i = 0;
    probe = (h1 + i*h2) % m;

    while(i < m) {
        if(htable[probe] != nullptr && htable[probe]->processid == PID) { //we found the key
            mem_array[htable[probe]->startaddress + ADDR] = x;
            cout << "success" << endl;
            return;
        }
        i += 1;
        probe = (h1 + i*h2) % m;;
    }
    
    cout << "failure" << endl; // key did not exist
    return; 
}

void hashtable::read(long PID, long ADDR) { 
    if(ADDR >= page_size || ADDR < 0){
        cout << "failure" << endl;
        return;
    }

    int h1 = PID % htable.capacity();
    int h2 = int(floor(PID / htable.capacity())) % htable.capacity();
    int probe;

    if (h2 % 2 == 0){
        h2 += 1; // h2 must be odd so if it is even we do + 1
    }
    //since htable is not at capacitiy we must be able to hash
    // ℎ(𝑘,𝑖)=(ℎ1(𝑘)+𝑖∗ℎ2(𝑘)) mod m,
    int i = 0;
    probe = (h1 + i*h2) % m;

    while(i < m) {
       if(htable[probe] != nullptr && htable[probe]->processid == PID){ //we found the key
            mem_array[htable[probe]->startaddress + ADDR];
            cout << ADDR << " " << mem_array[htable[probe]->startaddress + ADDR] << endl;
            return;
        }
        i += 1;
        probe = (h1 + i*h2) % m;;
    }
    
    cout << "failure" << endl; // key did not exist
    return;

}
