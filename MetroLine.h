/*
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#ifndef _METROSIM_H_
#define _METROSIM_H_

using namespace std;

// Put any necessary includes here


// optional
struct Passenger
{
	int passengerID;
	int departure;
	int arrival;

};

//int total_passengers

//Station

//int stationOccup
// int stationSize

//Station Redline;
struct Station
{
	int stationNum;
	string stationName;
	Passenger *atStation;
	int statCurrOccup;
    int statMaxSize;


};
//stationPassengers

//int statCurrOccups
//int statMaxSize

// trainPassengers
//int trainCurrOccup
//int trainMaxSize

//Train Joe;
struct Train
{
	int location;
	int speed; //  for wrapping
	Passenger *onTrain;
};


class MetroSim
{
public:

	 	MetroSim(); 
        // Parameterized constructor 
        
        // Destroy all memory

        void read_stationsFile ( istream &input_source);
        void print_outputFile ( int i, ostream &output_source);
        void read_commandsFile ( istream &input_source , ostream &output_source, string *filename);

        

        void move (ostream &output_source);
        int finish();
        void transport(int arrival, int departure); // arrival, departure
        
        void destroy();

        // Check if zero 
        bool isEmpty(); 
        // Making the number zero
        void makeEmpty(); 

        // Getters
        int size(); 
        Passenger first(); 
        Passenger last(); 
        Passenger passengerAt(int pos); 

        // Print
        void print(); 

        // Inserts  passengers on train
        void addToBackTrain(Passenger Alamin); 
        void addAtTrain(Passenger Fatimah, int pos); 

		
        // Inserts  passengers on station
        void addToBackStation(int arrival, Passenger Alamin); 
        void addAtStation(int arrival, Passenger Fatimah, int pos);  

        //inserts new station
    	void addToBack(Station Alamin);            

        // Removes passengers on train
        void replaceTrain(Passenger Fatimah, int pos);
        void removeBackTrain(); 
        void removeAtTrain(int pos); 

        // Removes passengers on station
        void removeFrontStation();
        void removeBackStation(); 
        void removeAtStation(int pos); 

         void concatenate (Passenger Fatimah);


private:

		
		Station *Redline;
		Train Joe;// not an array. (just one) 
        int total_passengers;

		// data elements of Passenger on train array.
		
        int trainCurrOccup; // Number of array slots in use
        int trainMaxSize;   // Total size of array

        //data elements of Passengers at station array

        

        //data elements of station array 

        // we would need to concatenate with passengers already on the train
		//Redline -> atStation

        int stationOccup;
        int stationSize;

        // Changing the size of the array
        // You can change the signature of these
        void expandTrain(); 
        void expandStat(int arrival);
        void expand (); // no of stations

        void shrinkTrain();
        void shrinkStat(int arrival);
        void shrink(); //no of stations

        void shift_right();
        void shift_left();
        int string2int(string s);

        // concatenate
        

        //prompt


        // exceptions  
        void generateException(string exceptionName)
            throw(int,  string, invalid_argument, 
                logic_error);
        

       

        // Add any helper functions you need! 

};

#endif
