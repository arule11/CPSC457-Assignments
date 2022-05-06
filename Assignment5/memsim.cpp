/*
* Athena Mc5eil-Roberts
* 30042085
* cpsc457 assignment 5
*/

// -------------------------------------------------------------------------------------
// this is the only file you need to edit
// -------------------------------------------------------------------------------------
//
// (c) 2021, Pavol Federl, pfederl@ucalgary.ca

#include "memsim.h"
#include <cassert>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>


struct Partition { 
  int tag; 
  int64_t size, addr; 
}; 

typedef std::list<Partition>::iterator PartitionRef; 
typedef std::set<PartitionRef>::iterator SetRef; 

int nPages = 0;

struct scmp { 
  bool operator()(const PartitionRef & c1, const PartitionRef & c2) const { 
    if (c1->size == c2->size) 
      return c1->addr < c2->addr; 
    else 
      return c1->size > c2->size; 
  } 
}; 

// I recommend you implement the simulator as a class. This is only a suggestion.
// If you decide not to use this class, please remove it before submitting it.
struct Simulator {

  int64_t pageSize;
  // all partitions, in a linked list 
  std::list<Partition> all_blocks; 
  // sorted partitions by size/address 
  std::set<PartitionRef,scmp> free_blocks; 
  // quick access to all tagged partitions 
  std::unordered_map<long, std::vector<PartitionRef>> tagged_blocks;  

  Simulator(int64_t page_size)
  {
    // constructor
    pageSize = page_size;
  }

  void allocate(int tag, int size)
  {
    SetRef x = free_blocks.begin();
    PartitionRef y = *x;
    if(!free_blocks.empty() && y->size >= size){ // if exists free blocks and size fits

      int64_t remains = y->size - size; // remaining free space
      // keep address of free block just change tag and size to incoming
      y->size = size; 
      y->tag = tag;
      free_blocks.erase(x); // remove the original free block

      if(remains != 0){ // need to create a new free block
        all_blocks.insert(std::next(y), Partition{-1, remains, y->addr + y->size}); 
        free_blocks.insert(free_blocks.begin(), std::next(y));
      }
      tagged_blocks[tag].push_back(y); // add tag to tagged blocks
      
    }else if(!free_blocks.empty() && std::prev(all_blocks.end())->tag == -1){ // if there are free blocks and the last one is free
      // can merge last into potential new space 
      int64_t newSize = size - std::prev(all_blocks.end())->size; // remaining size after using whatever is free
      int64_t remains;
      int64_t request;

      if(newSize % pageSize == 0){ // multiple of the page size
        request = (newSize / pageSize);
        remains = 0;
      }else{
        request = (newSize / pageSize) + 1;
        remains = (request * pageSize) - newSize;
      }
      nPages = nPages + request; // increment the number of requests

      PartitionRef cptr = std::prev(all_blocks.end()); // point to last 
      free_blocks.erase(cptr); // remove the last free block

      // keep address just change tag and size
      cptr->tag = tag; // change tag
      cptr->size = size; // change size 
      tagged_blocks[tag].push_back(cptr); // add to tagged blocks

      if(remains != 0){ // need to create a new free block
        all_blocks.push_back(Partition{-1, remains, cptr->addr + cptr->size});
        free_blocks.insert(free_blocks.begin(), --all_blocks.end()); // new free partition to free blocks
      }
    
    }else{ // request memory for block - no free blocks
    
      int64_t request;
      int64_t remains;

      if(size % pageSize == 0){ // multiple of the page size
        request = (size / pageSize);
        remains = 0;
      }else{
        request = (size / pageSize) + 1;
        remains = (request * pageSize) - size;
      }
      nPages = nPages + request; // increment the number of requests

      PartitionRef cptr = std::prev(all_blocks.end()); // point to last 

      if(all_blocks.empty()){ // inital case - no blocks
        all_blocks.push_back(Partition{tag, size, 0}); // set address to 0 
        cptr++; 
        tagged_blocks[tag].push_back(cptr); 

        if(remains!=0){ // need to create a new free block
          all_blocks.push_back(Partition{-1, remains, size});
          free_blocks.insert(free_blocks.begin(), --all_blocks.end()); // new free partition to free blocks
        }
      }else{
        all_blocks.push_back(Partition{tag, size, cptr->addr + cptr->size}); // add new block
        cptr++;
        tagged_blocks[tag].push_back(cptr);

        if(remains!=0){// need to create a new free block
          all_blocks.push_back(Partition{-1, remains, cptr->addr + cptr->size});
          free_blocks.insert(free_blocks.begin(), --all_blocks.end()); // new free partition to free blocks
        }
      }
    }
  }


  void deallocate(int tag)
  {
    PartitionRef iter;
    for (int i = 0; i < (int)tagged_blocks[tag].size(); i++){
      iter = tagged_blocks[tag][i];
      iter->tag = -1;
      if(std::prev(iter)->tag == -1 && iter != all_blocks.begin()){ // has free block before it - can merge
          iter->size = iter->size + std::prev(iter)->size; // merge sizes
          iter->addr = std::prev(iter)->addr; //change addy to previous
          free_blocks.erase(std::prev(iter)); 
          all_blocks.erase(std::prev(iter));
      }

      if(std::next(iter)->tag == -1 && iter != std::prev(all_blocks.end()) ){ // has free block after it - can merge
          // keep address & tag just change size
          iter->size = iter->size + std::next(iter)->size; // merge sizes
          free_blocks.erase(std::next(iter));
          all_blocks.erase(std::next(iter));
      } 
      free_blocks.insert(free_blocks.begin(), iter); // new free partition to free blocks
    }
    tagged_blocks.erase(tag); // remove all instances
  }


  MemSimResult getStats()
  {
    MemSimResult result;
    if(!free_blocks.empty()){ // exists a free block
      SetRef n = free_blocks.begin();
      PartitionRef k = *n;
      result.max_free_partition_size = k->size;
      result.max_free_partition_address = k->addr;
    }else{ // are no free blocks
      result.max_free_partition_size = 0;
      result.max_free_partition_address = 0;
    }
    result.n_pages_requested = nPages;
    return result;
  }


  // void check_consistency()
  // {
  //   PartitionRef iter;
  //   std::cout << "######ALL BLOCKS#########" << std::endl;
  //   for (iter = all_blocks.begin(); iter != all_blocks.end(); iter++){
  //     std::cout << "tag: " << iter->tag << "  size: " << iter->size << "  addy: " << iter->addr << std::endl;
  //   }

  //   SetRef x;
  //   std::cout << "$$$$$$FREE BLOCKS$$$$$$" << std::endl;
  //   for (x = free_blocks.begin(); x != free_blocks.end(); x++){
  //     PartitionRef y = *x;
  //     std::cout << "tag: " << y->tag << "  size: " << y->size << "  addy: " << y->addr << std::endl;
  //   }

  //   std::cout << "@@@@@TAGGED BLOCKS@@@@@" << std::endl;
  //   for(auto it= tagged_blocks.begin(); it!= tagged_blocks.end();it++) {
  //     std::cout << "tag: " << it->first << std::endl;
  //   }
  // }
};

// re-implement the following function
// ===================================
// parameters:
//    page_size: integer in range [1..1,000,000]
//    requests: array of requests
// return:
//    some statistics at the end of simulation
MemSimResult mem_sim(int64_t page_size, const std::vector<Request> & requests)
{
  // if you decide to use the simulator class, you probably do not need to make
  // any changes to the code below, except to uncomment the call to check_consistency()
  // before submitting your code

  Simulator sim(page_size);
  for (const auto & req : requests) {
    if (req.tag < 0) {
      sim.deallocate(-req.tag);
    } else {
      sim.allocate(req.tag, req.size);
    }
    // sim.check_consistency();
  }
  return sim.getStats();
}
