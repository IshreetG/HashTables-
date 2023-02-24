#ifndef _openhash_H
#define _openhash_H
#include <iostream>
#include <vector>

using namespace std;

class process {
    public:
    uint32_t processid;
    int startaddress;
    friend class hashtable;

    process(int PID, int ADDR); //contructor/deconstructor 
    ~process();
};

class hashtable {
    private:
    vector<process *> htable;
    int count; //to keep track of the size of the hashtable
    int total_mem_size;
    int page_size;
    int m;

    int calculate_probe(long PID);
    
    public:
    hashtable();
    ~hashtable();
    vector<int> mem_array; // represents all physical memory
    void create(int N, int P);
    void insert(long PID);
    void search(long PID);
    void write(long PID, long ADDR, int x); 
    void read(long PID, long ADDR); 
    void deletekey(long PID); 
};




#endif