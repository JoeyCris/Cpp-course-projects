#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

struct Weighted_edge;

struct Weighted_edge{
	double weight;
	int node_1;
	int node_2;
};

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int* degree_array;
		int num_nodes;
		int num_edges;
		
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
	if(n < 0){
		throw illegal_argument();
	}
	graph = new double*[n];
	for(int h = 0; h < n; h++){
		graph[h] = new double[n];
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			graph[i][j] = INF;
		}
	}
	degree_array = new int[n];
	for(int m = 0; m < n; m++){
		degree_array[m] = 0;
	}
	num_edges = 0;
	num_nodes = n;
}

Weighted_graph::~Weighted_graph() {
	for(int i = 0; i < num_nodes; i++){
		delete[] graph[i];
	}
	delete[] graph;
	delete[] degree_array;
}

int Weighted_graph::degree(int u) const {
	if(u >= num_nodes || u < 0){
		throw illegal_argument();
	}
	return degree_array[u];
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
	if(i >= num_nodes || j >= num_nodes || i < 0 || j < 0){
		throw illegal_argument();
	}
	if(i == j){
		return true;
	}
	if(graph[i][j] == INF){
		return false;
	}else{
		graph[i][j] = INF;
		graph[j][i] = INF;
		num_edges --;
		degree_array[i] --;
		degree_array[j] --;
		return true;
	}		
}

void Weighted_graph::clear_edges() {

	for(int i = 0; i < num_nodes; i++){
		for(int j = 0; j < num_nodes; j++){
			graph[i][j] = INF;
		}
	}

	for(int m = 0; m < num_nodes; m++){
		degree_array[m] = 0;
	}
	
	num_edges = 0;	
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	
	if(i >= num_nodes || j >= num_nodes || i < 0 || j < 0 || d <= 0){
		throw illegal_argument();
	}
	if(i == j){
		return false;
	}
	
	if(graph[i][j] == INF){
		graph[i][j] = d;
		graph[j][i] = d;
		num_edges ++;
		degree_array[i] ++;
		degree_array[j] ++;		
		return true;
	}else{
		graph[i][j] = d;
		graph[j][i] = d;
		return true;
	}
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	double total_weight = 0.0;
	int edge_counter = 0;
	
	if(num_edges == 0){
		return std::pair<double, int>( 0.0, 0 );
	}
	
	Disjoint_set* set = new Disjoint_set(num_nodes);
	
	Weighted_edge edges[num_edges];
	
	int e = 0;
	for(int i = 0; i < num_nodes; i++){
		for(int j = 0; j < i; j++){
			if(graph[i][j] != INF){
				edges[e].node_1 = i;
				edges[e].node_2 = j;
				edges[e].weight = graph[i][j];
				e++;
			}
		}
	}
	
	bool swapped = true;
      int m = 0;
      Weighted_edge tmp;
      while (swapped) {
            swapped = false;
            m++;
            for (int j = 0; j < num_edges - m; j++) {
                  if(edges[j].weight > edges[j+1].weight){
						Weighted_edge temp = edges[j];
						edges[j] = edges[j+1];
						edges[j+1] = temp;
						swapped = true;
				  }
            }
      }

	Weighted_edge current_edge;
	for(int i = 0; i < num_edges; i++){
		current_edge = edges[i];
		if(set->find_set(current_edge.node_1) != set->find_set(current_edge.node_2)){		
			set->union_sets(current_edge.node_1,current_edge.node_2);
			total_weight += current_edge.weight;
		}		
		edge_counter ++;	
		if(set->num_sets() == 1){
			break;
		}
	}	
	delete set;
	return std::pair<double, int>( total_weight, edge_counter );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif