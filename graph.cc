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

#include "graph.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

void Graph::Depthfirst(int v) 
{
    discovered.push_back(v); // Updates path with the correct vertex 

    if (discovered.size() == static_cast<std::vector<int>::size_type>(size)) // All vertices are discovered
    {
        return; 
    }
    path.push(v); // Current path 
    int indicator = 0; 
    
    // for all vertices that are adjacent to v
    for (auto vertex : adj_list[v]) 
    {
        // if the vertex is not labeled as discovered
        if (std::find(discovered.begin(), discovered.end(), vertex) == discovered.end()) 
        {
            edges.push_back(std::make_pair(v, vertex)); // Store the edge
            Depthfirst(vertex);
            ++indicator;
            
        }
    }
    // From the current vertex no other valid vertices were found to
    // continue traversal
    if (indicator == 0) 
    {
        // No unvisited adjacent vertices, backtrack
        int indicator1 = 0;
        while (indicator1 == 0 && !path.empty()) // backtrack until a valid vertex is found
        {
            path.pop();
            for (auto vertex : adj_list[path.top()]) 
            {
                // if the vertex is not labeled as discovered
                if (std::find(discovered.begin(), discovered.end(), vertex) == discovered.end()) 
                {
                    edges.push_back(std::make_pair(path.top(), vertex)); // Store the edge
                    Depthfirst(vertex);
                    ++indicator1;
                    break; // Exit the loop since a valid vertex was found
                }
            }
        }
    }
    
}


Graph::Graph(const char* filename)
{
    std::string line;
    char label;
    int filler;
    std::ifstream adj_m(filename); // opens desired file
    
    adj_m >> size; 
    adj_list.resize(size); // ensures the correct size for adj_list
    adj_m.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Process the given vertices character by character and storing them
    // in the correct order in labels vector
    getline(adj_m,line); 
    std::istringstream iss(line);
    while (iss >> label)
    {
        labels.push_back(label);
    }
    while (getline(adj_m,line))
    {
        std::istringstream iss2(line);
        char label1;
        iss2 >> label1;
        int pos;
        switch(label1) // converts the vertex on each line to the correct position within adj_list
        {
            case 'A':
                pos = 0;
                break;
            case 'B':
                pos = 1;
                break;
            case 'C':
                pos = 2;
                break;
            case 'D':
                pos = 3;
                break;
            case 'E':
                pos = 4;
                break;
            case 'F':
                pos = 5;
                break;
            case 'G':
                pos = 6;
                break;
        }
        int current_edge = 0;
        while (iss2 >> filler) // processes each line integer by integer
        {
            if (filler == 1) // if an adjacent edge then it is added to adj_list
            {
                adj_list[pos].push_back(current_edge);
            }
            ++current_edge; // used to keep track of current vertex
        }
    }
    adj_m.close(); // closes file
}

Graph::~Graph() // empties all containers
{
    size = 0;
    discovered.clear();
    labels.clear();
    path = std::stack<int>();
    edges.clear();
}

int Graph::Getsize() const 
{
    return size;
}

void Graph::Traverse() // prints out traverse in the desired format
{
    std::cout << "\n------- traverse of graph ------\n";
    Depthfirst(0);
    for (size_t i = 0; i != discovered.size() - 1; ++i)
    {
        std::cout << labels[discovered[i] ]<< ' ';
    }
    std::cout << labels[discovered[discovered.size() - 1] ]<< '\n';
    
    for (const auto& edge : edges) 
    {
        std::cout << "(" << labels[edge.first] << ", " << labels[edge.second] << ") ";
    }

    std::cout << "\n--------- end of traverse -------";


}

void Graph::Print() const // prints the simple graph in the desired format
{
    std::cout << "\nNumber of vertices in the graph: " << size << '\n';
    std::cout << "\n-------- graph -------\n";
    for ( size_t i = 0; i != adj_list.size(); ++i)
    {
        std::cout << labels[i] << ": ";
        bool printSeparator = false;
        for(auto edge : adj_list[i])
        {
            if (printSeparator) 
            {
                std::cout << ", ";
            }
            std::cout << labels[edge];
            printSeparator = true;
        }
        std::cout << '\n';
    }
    std::cout << "------- end of graph ------\n";
}
