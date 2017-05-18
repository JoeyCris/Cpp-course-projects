#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : 
nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	
	// initialize the sets
	for(int i = 0; i < n; i++){
		nodes[i] = new ll_entry();
		nodes[i]->content = i;
		nodes[i]->next = nullptr;	
	}
	
	for(int j = 0; j < n; j++){
		sets[j] = new set_info();
		sets[j]->size = 1;
		sets[j]->head = nodes[j];
		sets[j]->tail = nodes[j];
	}
	
	for(int k = 0; k < n; k++){
		nodes[k]->ptr_to_info = sets[k];
	}
	
}

Disjoint_set::~Disjoint_set() {
	// deallocate memory
	for(int i = 0; i < initial_num_sets; i++){
		delete sets[i];
		nodes[i]->ptr_to_info = nullptr;
	}
	delete[] sets;
	for(int j = 0; j < initial_num_sets; j++){
		delete nodes[j];
	}
	delete[] nodes;
}
int Disjoint_set::find_set(int item) const{
	return nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	if (node_index1 == node_index2){
		return;
	}
		
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;
	
	ll_entry* set_pointer = nodes[ni2]->ptr_to_info->head; //set_pointer points to the head of the small set
	set_info* new_set = nodes[ni1]->ptr_to_info;           //set_info of the larger set
	new_set->tail->next = set_pointer;                     //Let the tail of the larger set points to the head of the smaller set
	new_set->size += nodes[ni2]->ptr_to_info->size;        //Update the size of the larger set
	
	/* iterate through the shorter list and modify the pointers*/
	while (set_pointer != nullptr) {
		if(set_pointer->next == nullptr){                  //If the set pointer points to the last node in the shorter list
			new_set->tail = set_pointer;                   //Set the new tail
		}
		set_pointer->ptr_to_info = new_set;                //Update the set info node
		set_pointer = set_pointer->next;                   //Move to the next node
	}
	set_counter--;                                         //One less set in the data structure
	// delete the set_info entry that no longer exists	
}


#endif