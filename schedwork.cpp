#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool isValidisValid(Worker_T ID, vector<Worker_T>& numShifts, const int maxShifts); 
bool schedHelper(int row, int col, AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<Worker_T>& numShifts); 

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
      return false;
    }
    sched.clear();
    // Add your code below

    int numRows = avail.size(); 
    int numCols = dailyNeed; 

    //initialize array to schedule workers
		std::vector<Worker_T> numShifts(avail[0].size(), 0);  
    //std::vector<Worker_T> schedRow; 
    for(int i = 0; i < numRows; i++){
      /*for(int j = 0; j < numCols; j++){
      	schedRow.push_back(INVALID_ID); 
      }*/
      //add vector to schedule 
			std::vector<Worker_T> schedRow(numCols, INVALID_ID); 
      sched.push_back(schedRow); 
      //schedRow.clear(); 
    }

    AvailabilityMatrix available = avail; 

    //call helper function 
    if(schedHelper(0, 0, available, dailyNeed, maxShifts, sched, numShifts)){
       return true; 
    }
    else{
      return false; 
    }
}

bool isValid(Worker_T ID, vector<Worker_T>& numShifts, const int maxShifts)
{
	int shifts = numShifts[ID]; 
	if(shifts > maxShifts){
		return false; 
	}
	return true; 
}

bool schedHelper(int row, int col, AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<Worker_T>& numShifts)
{

	int need = dailyNeed; 
  int days = avail.size(); 

  //get number of all workers 
  Worker_T workers = avail[0].size(); 
  //Worker_T schedWorker; 
	if(row == days){
		return true; 
	}
	else if(col == need){
		std::vector<Worker_T> schedRow(dailyNeed, INVALID_ID); 
		if(schedHelper(row + 1, 0, avail, dailyNeed, maxShifts, sched, numShifts)){
      return true; 
    }
		else{
			sched[row] = schedRow; 
		}	
	}
	else if(sched[row][col] == INVALID_ID){
  	for(Worker_T i = 0; i < workers; i++){
    	//worker is available that day
      if(avail[row][i] == 1){
        sched[row][col] = i;
				numShifts[i]++; 
        //avail[row][i] = 0; 
        //schedWorker = i; 
        //check if current schedule is valid
        if(isValid(i, numShifts, maxShifts)){
        	//check if next schedule is valid
					if(schedHelper(row, col + 1, avail, dailyNeed, maxShifts, sched, numShifts)){
          	return true; 
          }
        }
        //reset values for backtracking 
				numShifts[i]--; 
        //avail[row][schedWorker] = 1; 
        sched[row][col] = INVALID_ID;
      }
    }
  }
  return false; 
}

