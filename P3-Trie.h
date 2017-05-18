#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdlib.h>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors
		
		bool string_check( std::string const & ) const; 
		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators
		
		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie(){
	root_node = nullptr;
	trie_size = 0;
}

Trie::~Trie() {	
	if(root_node != nullptr){
		root_node->clear();
	}	
}

bool Trie::string_check(std::string const &str) const {
	char letter;
	for(int i = 0; i < str.length(); i++){
		letter = str[i];
		if(!((letter >= 'a' && (int)letter <= 'z') || ((int)letter >= 'A' && (int)letter <= 'Z'))){
			return false;
		}
	}
	return true;
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if(size() != 0){
		return false;
	}else{
		return true;
	}
	
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	
	bool valid = string_check(str);
	if(valid == false){
		throw illegal_argument();
	}
	if(empty()){		
		return false;
	}
	if(root_node->member(str,1)){
		return true;
	}else{
		return false;
	}	
}

bool Trie::insert( std::string const &str ) {
	if(member(str)){		
		return false;
	}
	if(string_check(str) == false){		
		throw illegal_argument();
	}else{
		if(root_node == nullptr){
		root_node = new Trie_node();
		}
		bool inserted = root_node->insert(str,1);
		if(inserted){
			trie_size ++;
		}
		return inserted;
	}
}

bool Trie::erase( std::string const &str ) {	
	if(empty()){
		return false;
	}
	if(string_check(str) == false){
		throw illegal_argument();
	}else if(root_node->member(str,1) == false){
		return false;
	}else{
		bool deleted = root_node->erase(str,0,root_node);
		if(deleted){
			trie_size --;
		}
		return deleted;
	}	
}

void Trie::clear() {
	if(root_node == nullptr){
		return;
	}
	root_node->clear();
	root_node = nullptr;
	trie_size = 0;
}

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {
	
	return out;
}

#endif