#ifndef _ordhash_H
#define _ordhash_H
#include <iostream>
#include <vector>

using namespace std;

class Node {
    private:
    uint32_t processid;
    long startaddress;
    Node *next;

    public:
    Node(int pid, int saddr); //constructor
    ~Node(); //deconstructor 
    friend class hashtable2;

};

class linkedlist {
    private:
    Node *head;

    public:
    friend class hashtable2; 
    linkedlist();
    ~linkedlist();
};


class hashtable2 {
    private:
    int count; //to keep track of the size of the hashtable
    vector<linkedlist> htable2;
    Node *tem; 
    int total_mem_size;
    int page_size;
    int m;
    int find_unassigned_page();
    
    public:
    int *pages; // pointer to array to helps assign start addresses for processes 
    int *mem_array; // pointer to integer array represents all physical memory

    hashtable2(); //initalization of deconstructor/constructor
    ~hashtable2();
    void create(int N, int P);
    void hashsize(int m);
    void insert(long PID);
    void search(long PID); //return the start address of the process if exsits
    void write(long PID, long ADDR, int x); 
    void read(long PID, long ADDR); 
    void deletekey(long PID); 
    void print(int m);
    void deallocate_hashtable(); // deallocate node objects and arrays

};

#endif