#include "safecall.h"
/*
* By: Athena McNeil-Roberts
* ID# 30042085
*/

/*
* if the call to unsafe() crashes, safecall() will return -2
*
* if unsafe() does not return within 1s, safecall() will return -1
*   please note that safecall() must always return within 1s
*
* if the call to unsafe() returns within 1s, safecall() will return
* the value that unsafe() returned
*/

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <signal.h>
#include <cstdio>
#include <sys/wait.h>

int safecall(int i)
{
  FILE * tmpFile;
  int buffer;

  unlink("/tmp/tmpFile.txt"); // remove temporary file 
  auto pid = fork();

  if(pid == 0){
      int result = unsafe(i);
      tmpFile = fopen("/tmp/tmpFile.txt","wb");
      if(tmpFile == NULL){
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
      }
      fwrite(&result, sizeof(result), 1, tmpFile); // write unsafe(i) result in tmpFile.txt
      fclose(tmpFile);
      exit(0); // child finished

  } else if(pid > 0){
    auto start_time = std::chrono::steady_clock::now();

    while(1){
      int nap_time = 1; // 1us
      std::this_thread::sleep_for(std::chrono::microseconds(nap_time));
      auto res = waitpid(pid, NULL, WNOHANG); // res >= 1 to be done
      
      auto curr_time = std::chrono::steady_clock::now();
      double elapsed = std::chrono::duration_cast<std::chrono::microseconds>
      (curr_time - start_time).count() / 1000000.0;
      
      if(elapsed > 1.0) { 
        /* unsafe() is taking too long */ 
        kill(pid, SIGKILL); // kill child
        return -1;
      } else {
        if(res >= 1){
          // child has finished
          tmpFile = fopen("/tmp/tmpFile.txt","rb");
          if(tmpFile == NULL){
            return -2;
          }
          fread(&buffer, sizeof(int), 1, tmpFile); // result stored in tmpFile.txt 
          fclose(tmpFile);
          return buffer; // return unsafe(i) result from tmpFile.txt
        }
      }
     }
   } else{
     return -2;
   }
}