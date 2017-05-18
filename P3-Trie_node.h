#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		//char content;
		static int const CHARACTERS = 26;
		//char letters[26];


	public:
		Trie_node();
		Trie_node *child( int ) const;
		
		bool empty_children();

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;
};

Trie_node::Trie_node(){
	is_terminal = false;
	children = nullptr;	
}
/*children( nullptr ),
is_terminal( false ) {
	// empty constructor
}*/

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::empty_children(){
	int counter = 0;
	for(int i = 0; i < 26; i++){
		if(children[i] != nullptr){
			counter++;
		}
	}
	if(counter == 0){
		return true;
	}else{
		return false;
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	
	if(children == nullptr){
		return false;
	}
	char target_letter = str[depth-1];
	int pos;
	if((int)target_letter >= 97 && (int)target_letter <= 122){
		pos = target_letter -= 97;
	}else{
		pos = target_letter -= 65;
	}
	if(depth == str.length()){
		if(children[pos] != nullptr && children[pos]->is_terminal == true){         //The letter is in the tree and is a terminal
			return true;
		}else{
			return false;    //If we reach find the last letter of the string but it's not a terminal, the string is actually part of another word. Return false.
		}         			
	}else{
		if(children[pos] != nullptr && children[pos]->member(str,depth+1)){                       //If the current letter is matched and all following letters are also matched
			return true;			
		}else{
			return false;	
		}
	}
	return false;
}

bool Trie_node::insert( std::string const &str, int depth ){
	if(children == nullptr){
		children = new Trie_node*[26];    //If the curret node is a leaf, allocate children to it
		for(int i = 0; i < 26; i++){
			children[i] = nullptr;
		}
	}
	char target_letter = str[depth-1];
	int pos;
	bool success;
	if((int)target_letter >= 97 && (int)target_letter <= 122){
		pos = (int)(target_letter - 97);        //Determine the child using ascii table
	}else{
		pos = (int)(target_letter - 65);
	}

	if(children[pos] == nullptr){
		children[pos] = new Trie_node();
	}
	if(depth == str.length()){
		children[pos]->is_terminal = true;       //If the letter is the last one in the string, set is_terminal to true
		return true;
	}else{
		success = children[pos]->insert(str,depth+1);          //If it is not the last letter in the string, continue to insert the rest of the string
	}
	if(success){
		return true;
	}		
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ){
	if(depth == str.length()){
		if(children == nullptr){ //If the node is already a leaf, delete the node and return
			ptr_to_this = nullptr;     //QUESTION: If I do this, do I delete the node or only the pointer???
			delete this;
			return true;
		}else{
			is_terminal = false; //If this node is not a leaf, just deactivate the is_terminal
			return true;
		}	
	}else{		
		char next_letter = str[depth];         //Want to check its children
		int pos;
		if(next_letter >= 97 && next_letter <= 122){
			pos = next_letter -= 97;                           
		}else{                                   //Convert char to int
			pos = next_letter -= 65;
		}		
		bool success = children[pos]->erase(str,depth+1,children[pos]); //Erase the child 
		if(success){                                 //If the erase is successful
			if(empty_children()){        //If it has no children, turn the current node to a leaf first
				delete[] children;
				children = nullptr;
				if(is_terminal){
					return true;
				}
				ptr_to_this = nullptr;
				delete this;
				return true;
			}else{
				return true;                         //The current node still has children. This means it is part of another word
			}
		}else{
			return false;
		}
	}	
}

void Trie_node::clear(){	
	if(children == nullptr){
		delete this;
		return;
	}else{
		for(int i = 0; i < CHARACTERS; i++){
			if(children[i] != nullptr){
				children[i]->clear();
			}			
		}
		delete[] children;
		delete this;
		return;
	}			
}

#endif