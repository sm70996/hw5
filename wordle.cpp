// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelp(std::string in, const std::string floating, const std::set<std::string>&dict, std::set<std::string>& possibleWords, size_t index); 


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		
	//set to hold possible answers
    std::set<std::string> possibleWords;
	size_t index = 0; 
    //recursive call to helper function 
	wordleHelp(in, floating, dict, possibleWords, index); 
	return possibleWords; 

}

// Define any helper functions here
/********************************************************
****Recursively call helper function to insert ***********
****letters into blank spaces to see ****************
****if you get a valid word  ******************
**************************************************/
void wordleHelp(std::string in, const std::string floating, const std::set<std::string>& dict, std::set<std::string>& possibleWords, size_t index)
{
    //checks to see if completed word is valid 
    if(in.size() == index){
        if(dict.find(in) != dict.end()){
            possibleWords.insert(in); 
        }
        return; 
    }
    else if(in[index] != '-'){
        wordleHelp(in, floating, dict, possibleWords, index + 1);
    }
    else{
        //recursively calls function by inserting misplaced letters into blanks
        std::set<char> floats; 
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz"; 
        for(size_t i = 0; i < floating.size(); i++){
            floats.insert(floating[i]); 
            in[index] = floating[i]; 
            std::string newFloat = floating.substr(0, i) + floating.substr(i+1, floating.size()); 
            wordleHelp(in, newFloat, dict, possibleWords, index + 1);
            in[index] = '-';  
        }

        //fills rest of blanks with random letters from alphabet 
        bool space = true; 
        size_t numSpaces = 0; 
        for(size_t j = 0; j < in.size(); j++){
            if(in[j] == '-'){
                numSpaces++; 
            }
        }
        if(numSpaces != floating.size() ){
            space = false; 
        }
        if(!space){
            for(size_t k = 0; k < alphabet.size(); k++){
                if(floats.find(alphabet[k]) == floats.end()){
                    in[index] = alphabet[k]; 
                    wordleHelp(in, floating, dict, possibleWords, index + 1); 
                    in[index] = '-' ; 
                }
            }
        }
    }

}