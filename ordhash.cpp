#include "ordhash.h"
#include <iostream>
#include <cmath> 
#include <vector>

hashtable2::hashtable2(){ //constructor for class hashtable2
    int count = 0;
    Node *tem = nullptr;
}

hashtable2::~hashtable2() { //deconstructor

}

Node::Node(int pid, int saddr){ //constructor for class node
    processid = pid;
    startaddress = saddr;
}
Node::~Node() { //deconstructor
    Node *next = nullptr;

}
linkedlist::linkedlist() {

}
linkedlist::~linkedlist() { //deconstructor

}


void hashtable2::create(int N, int P){
    m = N/P;
    total_mem_size = N;
    page_size = P;
    mem_array = new int [total_mem_size]; //create an array with size N to represent all memory
    pages = new int [m]; // array of size m to represent which pages have been  take

    std::fill_n(pages, m, -1); // set all index to -1 as no start address is reserved
    std::fill_n(mem_array, N, 0);
    htable2.resize(m);
}

void hashtable2::search(long PID){
    int probe = PID % htable2.capacity();

    // search the LL starting for process with process_id = PID
    for(Node *temp = htable2[probe].head; temp != nullptr; temp = temp -> next){
        if(temp -> processid  == PID){
            cout << "found " << temp-> processid << " in " << probe << endl;
            return;
        }
    }
    cout << "not found" << endl;
    return;
}

//private function used to calculate the start address of a newly added process
int hashtable2::find_unassigned_page(){
    int index = 0;

    while(index < m){
        if (pages[index] == -1){
            return index;
        }
        index += 1;
    }

    return -1; // did not find start address

}

void hashtable2::insert(long PID){
    int probe = PID % htable2.capacity();
    Node *temp= htable2[probe].head; // point to head to LL at index 'probe'

    int page_num = find_unassigned_page();
    int start_address = page_num * page_size;
    // if find_assigned_page returns -1 means no page is available
    if (page_num == -1){
         cout << "failure" << endl;
         return;
    }

    if(temp == nullptr) { //if the index at that pointer is null then we will set it to the PID
        count += 1;
        htable2[probe].head = new Node(PID, start_address);
        pages[page_num] = 1; // to signal that we have allocated this page number
        cout << "success" << endl;
        return;
    }

    else if(temp->processid == PID){  // this means that the pid already exits
        cout << "failure" << endl;
        return;
    }

    else if(temp->processid < PID){
        count += 1;
        Node *temp2 = htable2[probe].head;
        htable2[probe].head = new Node(PID, start_address);
        pages[page_num] = 1; // update the pages array to show that this page is being used

        (htable2[probe].head)->next = temp2;

        cout << "success" << endl; //my att
        return;

    }

    // have to insert node into LL while keeping LL descending 
    else {
        while(temp->next != nullptr && temp->next->processid >= PID) {
            if(temp-> processid == PID) { //this means that it already exists 
                cout << "failure" << endl;
                return;
            }
            
            temp = temp->next;
        }

        //insert node now after temp
        count += 1;
        Node * temp2 = temp->next;
        temp->next = new Node(PID, start_address);
        temp->next->next = temp2;
        pages[page_num] = 1; // update the pages array to show that this page is being used

        cout << "success" << endl;
        return;
    }
}

void hashtable2::write(long PID, long ADDR, int x) {
    int probe = PID % htable2.capacity();

    if(ADDR >= page_size || ADDR < 0){
        cout << "failure" << endl;
        return;
    }
    // search the LL starting for process with process_id = PID
    for(Node *temp = htable2[probe].head; temp != nullptr; temp = temp -> next){
        if(temp -> processid  == PID){
            mem_array[temp->startaddress + ADDR] = x;
            cout << "success" << endl;
            return;
        }
    }
    cout << "failure" << endl;
    return;
}

void hashtable2::read(long PID, long ADDR) {    
   int probe = PID % htable2.capacity();

   if(ADDR >= page_size || ADDR < 0){
        cout << "failure" << endl;
        return;
    }
    // search the LL starting for process with process_id = PID
    for(Node *temp = htable2[probe].head; temp != nullptr; temp = temp -> next){
        if(temp -> processid  == PID){
            cout << ADDR << " " << mem_array[temp->startaddress + ADDR] << endl;
            return;
        }
    }
}

void hashtable2::deletekey(long PID) {
    int probe = PID % htable2.capacity();
    Node *temp = htable2[probe].head;

    if(temp == nullptr){
        cout << "failure" << endl;
        return;
    }

    // check the head fist
    else if(temp->processid == PID){
        htable2[probe].head = temp->next;
        count -= 1;
        pages[temp->startaddress / page_size] = -1; // update the pages array to show that this page is free to use
        delete temp;
        
        cout << "success" << endl;
        return;
    }

    else{
        while(temp->next != nullptr && temp->next->processid != PID){
            temp = temp->next;
        }

        if(temp->next == nullptr){
            //did not find the key
            cout << "failure" << endl;
            return;
        }
        // we found the node we want to delete, perform deletion
        Node *temp2 = temp->next;
        temp->next = temp->next->next;
        delete temp2;
        pages[temp->startaddress / page_size] = -1;

        count -= 1;
        cout << "success" << endl;
        return;
    }

}

void hashtable2::print(int m) {
    Node *temp= htable2[m].head; // point to head to LL at index 'probe'

    // check if LL is empty
    if(temp == nullptr){
        cout << "chain is empty" << endl;
        return;
    }
    //print out every process/node
    while(temp != nullptr){
        cout << temp->processid << " "; // print out pid of process(LL should already be in decending order)
        temp = temp->next;
    }
    cout << endl;
    return;
}

// free all node in each LL
void hashtable2::deallocate_hashtable() { //we will call this when program is terminated 
     Node *temp;
     Node *temp2;

    for(int i = 0; i < m; i++){
        temp = htable2[i].head;
        while(temp != nullptr){
            temp2 = temp -> next;
            delete temp;
            temp = temp2; 
        }
    }
    delete pages;
    delete mem_array;

}