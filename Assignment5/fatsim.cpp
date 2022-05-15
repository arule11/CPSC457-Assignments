/*
* Athena Mc5eil-Roberts
* cpsc457 assignment 5
*/

// -------------------------------------------------------------------------------------
// this is the only file you need to edit
// -------------------------------------------------------------------------------------
//
// (c) 2021, Pavol Federl, pfederl@ucalgary.ca

#include "fatsim.h"
#include <cstdio>
#include <iostream>
#include <algorithm> 

std::vector<bool> visited;
std::vector<long> longest_path;
std::vector<std::vector<long> > adj_list; 

// dfs based off code found from https://www.programiz.com/dsa/graph-dfs
long DFSsearch(long block){

  visited[block] = true; // mark the block as visited
  std::vector<long> sub_list = adj_list[block];

  if(!sub_list.empty()){
    long max = 0;
    for(long i = 0; i < (int)sub_list.size(); i++){
      long adj = sub_list[i]; // one of blocks adjacent blocks
      if(!visited[adj]){
        DFSsearch(adj); // perform search on adjacent block
        if(longest_path[adj] > max){ // compare lengths - if block has multiple blocks pointing to it
          max = longest_path[adj];
        }
      }
    }
    longest_path[block] += max;
  }
  return longest_path[block]; 
}


std::vector<long> fat_check(const std::vector<long> & fat)
{
  adj_list.resize(fat.size());
  for(int j =0; j < (int)fat.size(); j++){
    if(fat[j] != -1){
      adj_list[fat[j]].push_back(j); // create adjacency list for all blocks
    }
  }

  visited.resize(adj_list.size(), false);
  longest_path.resize(adj_list.size(), 1); // set default path length to 1 for all nodes ie itself
  std::vector<long> allPaths;

  for(int i = 0; i < (int)fat.size(); i++){
    if(fat[i] == -1){ // if block is last then start dfs 
      allPaths.push_back(DFSsearch(i)); // add length of path to list
    }
  }
 
  std::sort(allPaths.begin(), allPaths.end()); // sort results in ascending order
  return allPaths;

}
