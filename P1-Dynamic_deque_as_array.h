#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"

using namespace std;

class Dynamic_deque_as_array
{
	private:
		int* array;
		int head_index;
		int tail_index;
		int count;
		int array_size;
		
	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();
		
		int head();
		int tail();
		int size();
		bool empty();
		int capacity();

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
};


Dynamic_deque_as_array::Dynamic_deque_as_array(int n) {      //Initailise the array
	array_size = n;          //The input is the array size
	if(n <= 0){
		array_size = 1;               //If we have negative size, turn the size to 1
	}
	array = new int[array_size] ;       //Declaration
	head_index = 0;        //Assign the position to both head and tail
	tail_index = 0;
	count = 0;            //The counter is set to 0 since there is nothing in the deque
	       //The size is set to the input size
}




Dynamic_deque_as_array::~Dynamic_deque_as_array() {
	delete[] array;         //Delete the array
}





int Dynamic_deque_as_array::size(){
	return count;         //The variable count tells the number of elements in the deque
}


int Dynamic_deque_as_array::capacity(){
	return array_size;    //The variabe array_size tells us the capacity of the deque 
}


bool Dynamic_deque_as_array::empty(){
	if(count){	
		return 0;         //If the counter is greater than 0, the deque is not empty
	}else{ 
		return 1;         //If the counter is 0, the deque is empty
	}	
}


int Dynamic_deque_as_array::head(){
	//if(array_size == 0){
	//	throw new underflow();
	//}
	if(!empty()){
		return array[head_index];  //If the array is not empty, return the integer stored in the head
	}else{
		throw underflow();
	}	
}


int Dynamic_deque_as_array::tail(){
	//if(array_size == 0){
	//	throw new underflow();
	//}
	if(!empty()){
		return array[tail_index];  //If the array is not empty, return the integer stored in the tail
	}else{
		throw underflow();
	}	
}



void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
	if(array_size == 0){
		throw new underflow();
	}
	if(empty()){
		//cout << array_size/2 << endl;
		head_index = 0;        //Assign the position to both head and tail
		tail_index = 0;		
		array[head_index] = obj;  //If the array is empty, insert the first element in the middle so we have enough space on both ends
		count = 1;                  //There is only one element in the deque
	}else if(count == array_size){  //The deque id full
		int *new_array;
		new_array = new int[2*array_size];              //Allocate a bigger array with double the size of the old one	
		if(head_index>tail_index){              //When the head is behind the tail
			for(int i = 0; i < array_size-head_index; i++){
				new_array[i] = array[i+head_index];   
			}
			for(int i = 0; i < head_index; i++){
				new_array[i+array_size-head_index] = array[i];   
			}
		}else{
			for(int i = 0; i < array_size; i++){
				new_array[i] = array[i];
			}
		}
		delete[] array;                               //Delete the old one
		array = new_array;                          
		head_index = 0;                 //Update the head and tail position by adding and offset of half the length of the old array.
		tail_index = array_size-1; 
		array_size = array_size*2;                  //Double the array size
		head_index--;                                     //Now insert. The head decrement to make space for the new data
		if(head_index < 0){                  //If the head value will be negative, insert the value from the back of the array. We treat the queue as a ring
			head_index = head_index + array_size;   //Take head(mod length) as the new head position
		}		
		array[head_index] = obj;                          //Store the data
		count ++;                                   //The counter increments
	}else{
		head_index--;                         //The head decrement to make space for the new data
		if(head_index < 0){                  //If the head value will be negative, insert the value from the back of the array. We treat the queue as a ring
			head_index = head_index + array_size;   //Take head(mod length) as the new head position
		}
		array[head_index] = obj;              //Store the data
		count ++;                       //The counter increments
	} 
	return;
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	if(array_size == 0){
		throw new underflow();
	}
	if(empty()){             //If the array is empty, insert the first element in the middle so we have enough space on both ends
		head_index = 0;          //Assign the position to both head and tail
		tail_index = 0;		
		array[tail_index] = obj;    
		count = 1;                  //There is only one element in the deque
	}else if(count == array_size){    //The deque id full
		int *new_array;
		new_array = new int[2*array_size];              //Allocate a bigger array with double the size of the old one	
		if(head_index>tail_index){              //When the head is behind the tail
			for(int i = 0; i < array_size-head_index; i++){
				new_array[i] = array[i+head_index];   
			}
			for(int i = 0; i < head_index; i++){
				new_array[i+array_size-head_index] = array[i];   
			}
		}else{
			for(int i = 0; i < array_size; i++){
				new_array[i] = array[i];
			}
		}
		delete[] array;                               //Delete the old one
		array = new_array;                          
		head_index = 0;                 //Update the head and tail position by adding and offset of half the length of the old array.
		tail_index = array_size-1;
		array_size = array_size*2;                  //Double the array size
		tail_index++;                                     //Now insert. The tail increment to make space for the new data
		if(tail_index > array_size-1){
			tail_index = tail_index - array_size;
		}		
		array[tail_index] = obj;                          //Store the data
		count ++;                                   //The counter increments
	}else{
		tail_index++;
		if(tail_index > array_size-1){
			tail_index = tail_index - array_size;
		}
		array[tail_index] = obj;
		count++;
	}
	return;
}


int Dynamic_deque_as_array::dequeue_head() {
	if(empty()){                                    //When the deque is empty
		throw underflow();                                     //Return NULL
	}else{
		int result;
		result = array[head_index];                            //Take out the head data, store is elsewhere
		array[head_index] = NULL;                              //Clear the head
		head_index++;                                          //Update the head position
		if(head_index > array_size-1){
			head_index -= array_size;
		}
		count--;                                         //Counter decrements
		return result;                                   //Return the data
	}

}

int Dynamic_deque_as_array::dequeue_tail() {
	if(empty()){
		throw underflow();
	}else{
		int result;
		result = array[tail_index];
		array[tail_index] = NULL;
		tail_index--;
		if(tail_index < 0){
			tail_index += array_size;
		}
		count--;
		return result;
	}
}


void Dynamic_deque_as_array::clear() {
	for(int i = 0;i < array_size;i++){
		if(array[i] != NULL){
			array[i] = NULL;                           //Clear everything
		}
	}
	head_index = 0;
	tail_index = 0;
	return;
}

#endif