#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include "Exception.h"
#include "ece250.h"
#include<math.h>

using namespace std;

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
        int mod;
		int initial_size;
		T *array;
		state *array_state;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ){
	if(m < 0){                                     //If the input size is negative or 0
		m = 0;                                     //Set the size to 1
	}
	array_size = pow(2,m);
	initial_size = array_size;
	power = m;
	count = 0;
	
	array = new T[array_size];
	array_state = new state[array_size];
	for(int j = 0;j < array_size;j++){
		array_state[j] = EMPTY;               //Initialize the state array by setting every entry to ENPTY
	}
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	delete[] array;                                //Delete everything
	delete[] array_state;
}

template<typename T >
int LinearHashTable<T >::size() const {
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
	double count_in_double = (double)count;
	double array_size_in_double = (double)array_size;
	double alpha = count_in_double/array_size_in_double;
	return alpha;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
    if(count==0){
		return true;
	}else{
		return false;
	}
}


template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
	int mod = (int)(floor(obj)) % array_size;                      //Use the hash funciton to find h(k) = k mod m
	if(array[mod] == obj && array_state[mod] != DELETED){       
		return true;                                    //If the entry is at the expected mod, return true
	}else{                                              //If there is some other number in the expected bin, collision may have happened
		while(array_state[mod] != EMPTY){       //Search the following bins until we see an empty bin
			mod += 1;
			if(mod == array_size){                 
				mod = 0;                           //If we are at the end of the array, go to the start
			}
			if(array[mod] == obj && array_state[mod] != DELETED){
				return true;                            //We find the target element. It is somewhere else because of collision
			}
		}                                       
		return false;                                   //If we still haven't found it when we reach an empty bin, the element isn't in the table
	}
}

template<typename T >
T LinearHashTable<T >::bin( int n ) const {
		return array[n];                                 
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) { 
	 if(load_factor() > 0.75){                         //Check the load factor, if it's greater than or equal to 0.75, wee need a larger table
		 array_size *= 2;                               //Double the size
		 power ++;                                      //Update power
		 count = 0;                                     //Clear the counter, since this variable will be changed by the following recursion all

		 T* temp_array = array;                         //Use a temp array to store the elements in the old array
		 array = new T[array_size];                     //Allocate a longer array
		 
		 state* temp_array_state = array_state;
		 array_state = new state[array_size];
		 for(int j = 0;j < array_size;j++){
			 array_state[j] = EMPTY;                    //Initialize the new state array to all empty
		 }
		 
		 for(int i = 0;i < array_size/2;i++){
			 if(temp_array_state[i] == OCCUPIED){
				insert(temp_array[i]);
			}
		 }
		 delete[] temp_array;                           //Delete buffer arrays
		 delete[] temp_array_state; 
	 }
	mod = (int)(floor(obj)) % array_size;                     //Find the value of the hash function
	if(array_state[mod] == EMPTY){ //If the bin is empty
		array[mod] = obj;                         //Insert the element
		count ++;	                                    //Update the counter and state
		array_state[mod] = OCCUPIED;
	}else{
		while(array_state[mod] == OCCUPIED){      //If collision happens
			mod += 1;                             //Using linear probing until we find an empty slot
			if(mod == array_size){
				mod = 0;                          //If we reach the end of the array, start from the head
			}
		}
		array[mod] = obj;                         //Insert the element
		count ++;	                              //Update counter and state
		array_state[mod] = OCCUPIED; 
	}
	return;                                       //If the load factor is less than 0.75, just return	 
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	bool exists = member(obj);                            //Check whether the object is in the table at the very beginning
	if(!exists){
		return false;                                   //If the element is not in the array at all, return false 
	}
	if(load_factor() <= 0.25 && array_size != initial_size){                            //If the load factor is less than 0.25, we need a smaller array
		array_size /= 2;                                //Half the size 
		power --;                                       //Update power and the counter
		count = 0; 
		 
		T* temp_array = array;
		array = new T[array_size];
		 
		state* temp_array_state = array_state;
		array_state = new state[array_size];
		
		for(int j = 0;j < array_size;j++){
			array_state[j] = EMPTY;                      //This part is the same as insertion
		}
		 
		for(int i = 0;i < array_size*2;i++){
			if(temp_array_state[i] == OCCUPIED){
				insert(temp_array[i]);
			}		 
		}
		delete[] temp_array;
		delete[] temp_array_state;
	}
	mod = (int)(floor(obj)) % array_size;                      //Otherwise, calculate h(k)
	while(array[mod] != obj){                      //If collision happens, using linear probing to find the mod of the target element
		mod ++;
		if(mod == array_size){
			mod = 0;                               //If we reach the end, back to the start
		}
	}
	array_state[mod] = DELETED;                    //Update the state and counter
	count --;
	return true;
}

template<typename T >
void LinearHashTable<T >::clear() {
	for(int j = 0;j < array_size;j++){                   //Clear everything
		if(array_state[j] = OCCUPIED){
			array_state[j] = EMPTY;
		}	
	}
	count = 0;
}

template<typename T >
void LinearHashTable<T >::print() const{
	for(int i = 0;i < array_size;i++){
		if(array_state[i] == OCCUPIED){
			std::cout << i << "   " << array[i] << std::endl;
		}else if(array_state[i] == EMPTY){
			std::cout << i << "   " << "EMPTY" << std::endl;
		}else{
			std::cout << i << "   " << "DELETED" << std::endl;
		}		
	}
}

#endif