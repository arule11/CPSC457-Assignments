/*
* CPSC457 Assignment4 - deadlock_detector.cpp
* Athena McNeil-Roberts
*/

#include "deadlock_detector.h"
#include "common.h"
#include <iostream>
#include <string>

std::vector<std::string> conversions;

struct FastGraph { 
    std::vector<std::vector<int> > adj_list; 
    std::vector<int> out_counts;
} graph;

/// this is the function you need to (re)implement
///
/// parameter edges[] contains a list of request- and assignment- edges
///   example of a request edge, process "p1" resource "r1"
///     "p1 -> r1"
///   example of an assignment edge, process "XYz" resource "XYz"
///     "XYz <- XYz"
///
/// You need to process edges[] one edge at a time, and run a deadlock
/// detection after each edge. As soon as you detect a deadlock, your function
/// needs to stop processing edges and return an instance of Result structure
/// with edge_index set to the index that caused the deadlock, and dl_procs set
/// to contain with names of processes that are in the deadlock.
///
/// To indicate no deadlock was detected after processing all edges, you must
/// return Result with edge_index = -1 and empty dl_procs[].
///

void addConversion(std::string node, int x){
    if((int)conversions.size() <= x){
        conversions.resize(x+1);
    }
    conversions[x] = node;
}

Result detect_deadlock(const std::vector<std::string> & edges)
{   
    std::vector<std::string> inputs;
    std::string process;
    std::string resource;
    std::string edge;
    Result result;
    Word2Int convert;

    std::cout << std::endl;

    for(int edgeIndex = 0; edgeIndex < (int)edges.size(); edgeIndex++){
        inputs =  split(edges[edgeIndex]);

        process = inputs[0];
        resource = inputs[2];
        resource.push_back('$'); // append $ to all resources 
        edge = inputs[1];

        int procInt = convert.get(process);
        int resInt = convert.get(resource);
        addConversion(process, procInt); // add process string to int conversion
        addConversion(resource, resInt); // add resource string to int conversion
        
        // check edge type
        if(edge.compare("->") == 0){ // request edge
           
            if(procInt >= (int)graph.adj_list.size()){
                graph.adj_list.resize(procInt + 1); // add process to list if not exists
            }

            if(resInt >= (int)graph.adj_list.size()){
                graph.adj_list.resize(resInt + 1); // add resource to list if not exists
            }
            graph.adj_list[resInt].push_back(procInt); // link the process to the resource as a node pointing towards

            

            if(procInt >= (int)graph.out_counts.size()){
                graph.out_counts.resize(procInt + 1);  // add process to list if not exists
                graph.out_counts[procInt] = 0;  // default number of outgoing edges to zero 
            }
            graph.out_counts[procInt]++; // increment outgoing edges since pointing to resource

            if(resInt >= (int)graph.out_counts.size()){
                graph.out_counts.resize(resInt + 1); // add resource to list if not exists
                graph.out_counts[resInt] = 0; // default number of outgoing edges to zero 
            }

        }else if(edge.compare("<-") == 0){ // assignment edge

            if(procInt >= (int)graph.adj_list.size()){
                graph.adj_list.resize(procInt + 1); // add process to list if not exists
            }
            graph.adj_list[procInt].push_back(resInt); // link the resource to the process as a node pointing towards

            if(resInt >= (int)graph.adj_list.size()){
                graph.adj_list.resize(resInt + 1); // add resource to list if not exists
            }

            if(procInt >= (int)graph.out_counts.size()){
                graph.out_counts.resize(procInt + 1); // add process to list if not exists
                graph.out_counts[procInt] = 0; // default number of outgoing edges to zero 
            }

            if(resInt >= (int)graph.out_counts.size()){
                graph.out_counts.resize(resInt + 1); // add resource to list if not exists
                graph.out_counts[resInt] = 0; // default number of outgoing edges to zero 
            }
            graph.out_counts[resInt]++; // increment outgoing edges since pointing to process
        }
    
        std::vector<int> out = graph.out_counts;
        std::vector<int> zeros; // nodes with out_count = 0
        
        for(int i = 0; i < (int)out.size(); i++){
            if(graph.out_counts[i] == 0){ // if outgoing edges is zero for node add to zeros list
                zeros.push_back(i);
            }
        }

        while(!zeros.empty()){
            int node = zeros.back(); // get last value
            zeros.pop_back(); // remove it
            for(int j = 0; j < (int)graph.adj_list[node].size(); j++){
                int n2 = graph.adj_list[node][j]; 
                out[n2]--;
                if(out[n2] == 0){
                    zeros.push_back(n2);
                }
            }
        }

        for(int k = 0; k < (int)out.size(); k++){
            if(out[k] != 0){
                std::string temp = conversions[k]; // get string value of node
                if(temp.find("$") == std::string::npos){
                    result.dl_procs.push_back(temp); // if its a process add to the dl_procs list
                }
            }
        }

        if(!result.dl_procs.empty()){ // deadlock detected
            result.edge_index = edgeIndex; // deadlock caused at current edge
            break;
        }
    }
    if(result.dl_procs.empty()){ // no deadlock detected
        result.edge_index = -1;
    }

    return result;
}
