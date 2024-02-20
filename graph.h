//***************************************************************************
//
// Jose Barron
// Z02013735
// Fall 2023 CSCI 340 - PE1 Data Struct Algorithm Analysis
// Assignment 10: This program is intended to define the definitions
// given in "graph.h" to demonstrate a simple graph.
// Due Date: 12/04/23
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//***************************************************************************

#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <stack>

class Graph {
 private:
  int                          size; 
  std::vector<std::list<int> > adj_list; 
  std::vector<char>            labels;
  std::stack<int>              path; // used for traversal within search
  std::vector<int>             discovered; // the desired path
  std::vector<std::pair<int, int>> edges; // edges taken to reach desired path
  void                         Depthfirst(int);


 public:
  Graph(const char* filename);
  ~Graph();
  int  Getsize() const;
  void Traverse();
  void Print() const;
};

#endif  // GRAPH_H
