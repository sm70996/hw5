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
bool isValid(int row, int col, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched); 
bool schedHelper(int row, int col, AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched); 

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
    std::vector<Worker_T> schedRow; 
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            schedRow.push_back(INVALID_ID); 
        }
        //add vector to schedule 
        sched.push_back(schedRow); 
        schedRow.clear(); 
    }

    AvailabilityMatrix available = avail; 

    //call helper function 
    if(schedHelper(0, 0, available, dailyNeed, maxShifts, sched)){
        return true; 
    }
    else{
        return false; 
    }

}

bool isValid(int row, int col, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched)
{
    int need = dailyNeed; 
    int days = sched.size(); 

    //get worker ID thats in the schedule 
    Worker_T worker = sched[row][col]; 

    size_t count = 0; 

   //iterate through schedule to ensure you don't pass maxShifts
    for(int i = 0; i < days; i++){
        for(int j = 0; j < need; j++){
            if(sched[i][j] == worker){
                count++; 
            }
        }
    }
    if(count > maxShifts){
        return false; 
    }
    else{
        return true; 
    }
}

bool schedHelper(int row, int col, AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched)
{
    int need = dailyNeed; 
    int days = avail.size(); 

    //get number of all workers 
    Worker_T workers = avail[0].size(); 
    Worker_T schedWorker; 

    if(sched[row][col] == INVALID_ID){
        for(Worker_T i = 0; i < workers; i++){
            //worker is available that day
            if(avail[row][i] == 1){
                sched[row][col] = i; 
                avail[row][i] = 0; 
                schedWorker = i; 
                //check if current schedule is valid
                if(isValid(row,col,dailyNeed,maxShifts,sched)){
                    //check if next schedule is valid
                    if(col < need - 1){
                        if(schedHelper(row, col + 1, avail, dailyNeed, maxShifts, sched)){
                            return true; 
                        }
                    }
                    else if(row < days - 1){
                        if(schedHelper(row + 1, 0, avail, dailyNeed, maxShifts, sched)){
                            return true; 
                        }
                    }
                    else{
                        return true; 
                    }
                }
            }
            //reset values for backtracking 
            avail[row][schedWorker] = 1; 
            sched[row][col] = INVALID_ID; 
        }
    }
    return false; 
}

