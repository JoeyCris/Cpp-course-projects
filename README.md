# Cpp-course-projects

This repository stores some C++ code written for the course Algorithm and Data Structures. There are four projects in total. 

P1 implements a dynamic deque data structure using a queue. The user can insert or extract objects from both ends of the deque. The deque will double its size when full and shrink its size by half when half empty. 

P2 implements a hash table. The data structure uses a hash function to map the input item to its slot. When collision happens, the program uses linear probing to find the next available slot. The table will double its size when the load factor is greater than 0.75 and will half its size when the load factor is less than 0.25. The user can insert, delete, and search for items.

P3 implements a Trie data structure. The trie stores input words from the user in a tree, and each letter is stored in a node. The node is implemented in another class. The letters are not physically stored in the node as a member variable, but are stored as an index ranged from 1 to 26. Each node has 26 children (26 pointers) and the non-null children indicate stored letters. i.e. the 5th child of letter "c" is not null, so letter "e" is stored after "c". If the 10th child of "c" is null, then letter "j" is not stored after "c". The user can insert, delete words and search for a particular word.

P4 implements a weighted graph. The graph is implemented using a weight matrix, recording the weight od each edge. There is also a program constructing the MST of the tree using a Kruskal's algorithm. The MST algorithm is implemented using disjoint set and linked list data structures. The user can add any edge with positive weight and find an MST using the Kruskal program.
