/*
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>
#include <stdio.h>

#include "MetroLine.h"

using namespace std;

// MetroLine.cpp
// purpose: stmulates a Metro line
// by : Asiyah Mumuney.
// date :10/09/2019




using namespace std; 

/*** We have given you a template for your function contracts
 *** You are welcome to use it or another layout as long as
 *** the contracts are easy to read and have the right information.
 *** We will not do this for every assignment, so you need to
 *** understand everything that's here.
 ****/

// Default constructor 
// Parameters: None
// Returns: None
// Does: set the number of passengers to 0
// and teh train to the first station. 
MetroSim::MetroSim()
{
	
	//Station
	Redline = new Station [40];
	stationOccup = 0;
	stationSize   = 40;

	 //Passengrs at Station

	for (int i = 0; i < stationOccup; i++){	
		Redline[i]. atStation = new Passenger [10];
		Redline[i].statCurrOccup = 0;
		Redline[i].statMaxSize   = 10;

	}
	//Train
	Joe.location = 1;
	Joe.speed    = 1; 

	Joe.onTrain = new Passenger[10];
	trainCurrOccup = 0;
	trainMaxSize   = 10;

	total_passengers = 0;

	//TODO
}


// Function: read_file
// Parameters: fstream input and output
// Returns: None
// Does: file i/o. Reads info from 
// input file and prints to output 
// file or cout

void MetroSim :: read_stationsFile( istream &input_source)
{
	string station, command;	
	int i = 0;
		
	// read stations
	getline (input_source, Redline[i].stationName);
	stationOccup = 1;
	Redline[i].stationNum = stationOccup; 


	while (!input_source.eof()){

		i++;

		getline(input_source,Redline[i].stationName);
		stationOccup++;
		Redline[i].stationNum = stationOccup;

		
		expand();
			
	}		
}

// Function: read_file
// Parameters: fstream input and output
// Returns: None
// Does: file i/o. Reads info from 
// input file and prints to output 
// file or cout

void MetroSim :: print_outputFile (int i, ostream &output_source)
{
	output_source << "Passenger " << Joe.onTrain[i].passengerID 
		<< " left train at Station " << Redline[Joe.location - 1].stationName << endl;
} 

// Function: command_line_argument
// Parameters: number of arguments and name of arguments
// Returns: None
// Does: determines the number of arguments for input, 
// output and command. 

void MetroSim :: read_commandsFile ( istream &input_source , 
	ostream &output_source, string *filename)
{
	cout << "Command? " ;
	string command;
	string type, command1, command2;
	int arrival, departure;
	int counter = 1;

	getline(input_source, command);
	print();

	while (!input_source.eof()){
				

		stringstream ss(command);
		ss >> type;
		

		if (type == "m"){
			ss >> command1;
			

			if (command1 == "m"){
				//print();


				move(output_source);

			}
			else {
				
				finish();
				
			}
		}
		else if (type == "p"){
			ss >> command1 >> command2;
			arrival = string2int(command1);
			departure = string2int(command2);


			transport(arrival, departure);


			//print();
		}
		else if (type == "f"){
			ss >> command1;
			*filename = command1; 
			//output_source.close();
			//output_source.open(&command1);

			
			//figure out later

			//output_source.close();
			//output_source.open(command1);

		}
		print();
		cout << "Command? " ;
		getline(input_source, command);
		counter++;
	}

	cout << "Thanks for playing MetroSim. Have a nice day!" << endl; 

}

// Function: move
// Parameters: ostream &output_source
// Returns: None
// Does: moves the train, drops and 
// picks passengers 

void MetroSim :: move (ostream &output_source)
{		

	//drop passengers.
	for (int i = 0; i < trainCurrOccup; i++){
		if (Joe.onTrain[i].departure == Joe.location){
			
			print_outputFile(i, output_source);
			removeAtTrain(i); // remove from passengers on train
			
		}
	}

	//pick passengers
	
	int counter = Redline[Joe.location-1].statCurrOccup;

	for (int i = 0; i < counter; i++){
		
		addToBackTrain( Redline[Joe.location - 1].atStation[0]);
		
		
		//removeAtStation(0); 
		removeFrontStation();
	

	}

	//move to next 

	if(Joe.location >= stationOccup and Joe.speed == 1){

		Joe.speed = -1;
	}
	else if (Joe.location <= 1  and Joe.speed == -1){

		Joe.speed = 1;

	}

	if (Joe.speed == 1){
		Joe.location++;
	}
	else{
		Joe.location--;
	}

}


// Function destroy
// Parameters: None
// Returns: None
// Does: serves as the destructor of the class
// erases all excess memory after we finish
// running the program

int MetroSim :: finish()
{
	destroy();
	return 0;
}

// Function transport
// Parameters: Passenger Alamin
// Returns: none
// Does: inserts a Passenger to the end of the line

void MetroSim :: transport(int arrival, int departure)
{

	total_passengers++;
	Passenger teni;
		teni.passengerID = total_passengers;
				
		teni.arrival = arrival;
		teni.departure = departure;

		addToBackStation(arrival , teni);
		//addAtStation(arrival,teni,Redline[arrival-1].statCurrOccup);

		//cerr << "should output (ID, arrival -> departure); 

}



// Function destroy
// Parameters: None
// Returns: None
// Does: serves as the destructor of the class
// erases all excess memory after we finish
// running the program

void MetroSim::destroy()
{
	// check on deleting arrays
	// loop through and delete
	 delete [] Joe.onTrain;

	for (int i = 0; i < stationOccup; i++){

		delete [] Redline[i].atStation;

	}
	 delete [] Redline;
	 
	// need to ask what to do for destroy
	trainCurrOccup = 0;
	trainMaxSize = 0;

	for (int i = 0; i < stationOccup; i++){	
		Redline[i].statCurrOccup = 0;
    	Redline[i].statMaxSize = 0;
    }

    stationOccup = 0;
    stationSize  = 0;
    //find out about passengers at station
}

// Function isEmpty
// Parameters: None
// Returns: boolean
// Does: Checks whether there are zero passengers 
// returns true if it is else returns false.
bool MetroSim::isEmpty()
{
	if (trainCurrOccup == 0){
		return true;
	}
	else {
		return false;
	}
	
}

// Function makeEmpty
// Parameters: None
// Returns: None
// Does: sets passengers to zero

void MetroSim::makeEmpty()
{

	
	trainCurrOccup = 0;	
}

// Function size
// Parameters: none
// Returns: integer
// Does: return the number of passengers 
// in a LargeNumber
int MetroSim::size()
{
	return trainCurrOccup;
} 

// Function first
// Parameters: None
// Returns: int
// Does: returns the first passenger 

Passenger MetroSim::first()
{
	return Joe.onTrain[0];
}

// Function last 
// Parameters: none
// Returns: int
// Does: returns the last passenger

Passenger MetroSim::last()
{
	return Joe.onTrain[trainCurrOccup - 1];
} 

// Function passengerAt
// Parameters: int i (ie pos)
// Returns: int
// Does: returns the passenger at ith 
// position
Passenger MetroSim::passengerAt(int pos)
{
	if ((pos <= 0) or (pos > trainCurrOccup - 1)){
		generateException("range_error");
	}
	return Joe.onTrain[pos];
} 

// Function print
// Parameters: none
// Returns: none
// Does: prints out map
void MetroSim::print()
{
	// printing passengers on train
	cout << "Passengers on the train: {";
	for (int i = 0; i < trainCurrOccup; i++){
		cout << "[" << Joe.onTrain[i].passengerID 
		<< "," << Joe.onTrain[i].arrival 
		<< "->" << Joe.onTrain[i].departure << "]";
	}
	cout << "}" << endl; 
	

	// printing train and stations.
	for (int i = 0; i < stationOccup; i++){
		if (Redline[i].stationNum == Joe.location){
			cout << "TRAIN: [" <<Redline[i].stationNum <<"]"
				 << Redline[i].stationName << "{";

			for ( int j = 0; j < Redline[i].statCurrOccup; j++){
				cout << "[" << Redline[i].atStation[j].passengerID
					 << "," << Redline[i].atStation[j].arrival
					 << "->"<< Redline[i].atStation[j].departure << "]";
			}
			cout << "}" << endl;
		}
		else {
			cout << "       [" <<Redline[i].stationNum <<"]"
				 << Redline[i].stationName << "{";

			for ( int j = 0; j < Redline[i].statCurrOccup; j++){
				cout << "[" << Redline[i].atStation[j].passengerID
					 << "," << Redline[i].atStation[j].arrival
					 << "->"<< Redline[i].atStation[j].departure << "]";
			}
			cout << "}" << endl;
		}
	}
	//take care of if empty
} 

// Function insertLastPassenger
// Parameters: Passenger Alamin
// Returns: none
// Does: inserts a Passenger to the end of the line
void MetroSim::addToBackTrain(Passenger Alamin)
{

	if (trainCurrOccup >= trainMaxSize){
		expandTrain ();
	}

	Joe.onTrain[trainCurrOccup] = Alamin;
	trainCurrOccup++;
  
}

// Function insertLastPassenger
// Parameters: Passenger Alamin
// Returns: none
// Does: inserts a Passenger to the end of the line
void MetroSim::addToBackStation(int arrival,Passenger Alamin)
{

	if (Redline[arrival-1].statCurrOccup >= Redline[arrival-1].statMaxSize){
		
		expandStat (arrival);
		
	}

	Redline[arrival-1].atStation[Redline[arrival-1].statCurrOccup] = Alamin;
	Redline[arrival-1].statCurrOccup++;
  
}

// Function insertLastPassenger
// Parameters: Passenger Alamin
// Returns: none
// Does: inserts a Passenger to the end of the line
void MetroSim::addToBack(Station Alamin)
{

	if (stationOccup >= stationSize){
		expand ();
	}

	Redline[stationOccup] = Alamin;
	stationOccup++;
  
}

// Function insertFirstPassenger
// Parameters: Passenger Asiyah
// Returns: none
// Does: inserts a digit at the 0th position of the 
// number


// Function insertAt
// Parameters: PAssenger Fatimah, int pos
// Returns: none
// Does: inserts a Passenger into the posth position 


void MetroSim::addAtTrain(Passenger Fatimah, int pos)
{
	

	if ((pos < 0) and (pos > trainCurrOccup - 1)){
		generateException("range_error");
	}

	if (trainCurrOccup >= trainMaxSize){
		expand ();
	}
	
	for (int i = pos; i < trainCurrOccup; i++){
		Joe.onTrain[i+1] = Joe.onTrain[i];
	}
	Joe.onTrain[pos] = Fatimah;


	trainCurrOccup++;

	
} 


// Function insertAt
// Parameters: PAssenger Fatimah, int pos
// Returns: none
// Does: inserts a Passenger into the posth position 


void MetroSim::addAtStation(int arrival, Passenger Fatimah, int pos)
{
	

	if ((pos < 0) and (pos > Redline[arrival-1].statCurrOccup - 1)){
		generateException("range_error");
	}

	if (Redline[arrival-1].statCurrOccup >= Redline[arrival-1].statMaxSize){
		expandStat (arrival);
	}
	
	for (int i = pos; i < Redline[arrival-1].statCurrOccup; i++){
		Redline[arrival - 1].atStation[i+1] = Redline[arrival - 1].atStation[i];
	}
	Redline[arrival - 1].atStation[pos] = Fatimah;


	Redline[arrival-1].statCurrOccup++;

	
} 

// Function replace
// Parameters: Passenger Fatimah, int pos
// Returns: none
// Does: replace the Passenger at posth with value
void MetroSim::replaceTrain(Passenger Fatimah, int pos)
{


	if ((pos < 0) and (pos > trainCurrOccup - 1)){
		generateException("range_error");
	}
	Joe.onTrain[pos] = Fatimah;
	
}

// Function replace
// Parameters: Passenger Fatimah, int pos
// Returns: none
// Does: replace the Passenger at posth with value




// Function removeLowestDigit
// Parameters: none
// Returns: none
// Does: removes the last passenger
void MetroSim::removeBackTrain()
{
	

	if (trainCurrOccup < trainMaxSize / 2){
		shrink();
	}

	trainCurrOccup--;
}

// Function removeLowestDigit
// Parameters: none
// Returns: none
// Does: removes the last passenger




// Function removeAt
// Parameters: int pos
// Returns: none
// Does: removes the passenger at the posth 
// position 
void MetroSim::removeAtTrain(int pos)
{

	if ((pos < 0) or (pos > trainCurrOccup - 1)){
		generateException("range_error");
	}

	if (trainCurrOccup < trainMaxSize / 2){
		shrinkTrain();
	}

	for (int i = pos; i < trainCurrOccup; i++){
		Joe.onTrain[i] = Joe.onTrain[i+1];
	}
	trainCurrOccup--;

	
}

void MetroSim :: removeFrontStation()
{
	if (Redline[Joe.location - 1].statCurrOccup < Redline[Joe.location - 1].statMaxSize / 2){
		shrinkStat(Joe.location);
	}

	for (int i = 0; i < Redline[Joe.location - 1].statCurrOccup; i++){
		

		Redline[Joe.location -1].atStation[i] = 
			Redline[Joe.location -1].atStation[i+1];
		
	}

	Redline[Joe.location - 1].statCurrOccup--;

} 

// Function removeAt
// Parameters: int pos
// Returns: none
// Does: removes the passenger at the posth 
// position 
void MetroSim::removeAtStation(int pos)
{

	if ((pos < 0) or (pos > trainCurrOccup - 1)){
		generateException("range_error");
	}

	if (Redline[Joe.location - 1].statCurrOccup < Redline[Joe.location].statMaxSize / 2){
		shrinkStat(Joe.location);
	}

	for (int i = pos; i < Redline[Joe.location].statCurrOccup; i++){
		Redline[Joe.location - 1].atStation[i] 
			= Redline[Joe.location - 1].atStation[i+1];
		
	}
	Redline[Joe.location].statCurrOccup--;	
} 

void MetroSim :: shift_right()
{

	for (int i = 0; i < trainCurrOccup; i++){
		Joe.onTrain[i+1] = Joe.onTrain[i];
	}

}

void MetroSim :: shift_left()
{
	for (int i = 1; i < trainCurrOccup; i++){
		Joe.onTrain[i-1] = Joe.onTrain[i];
	}
}

// Function concatenate
// Parameters: Passengers Fatimah
// Returns: none
// Does: insert the Passenger Fatimah at teh
// back at the Passengers Joe.onTrains
void MetroSim::concatenate(Passenger Fatimah)
{
	addToBackTrain(Fatimah);
	
}

// Function expand
// Parameters: none
// Returns: none
// Does: increase the size of teh array
// by a factor of two
void MetroSim::expand()
{
	//TODO
	// make sure to call expand for all insert cases

	if (stationOccup >= stationSize){

		stationSize = stationSize * 2;
		Station *temp = new Station [stationSize];
		for ( int i = 0 ; i < stationOccup; i++){
			temp[i] = Redline[i];
		}
		delete [] Redline;
		
	    Redline = temp;

   }
	// review dynamically allocated arrays
}

void MetroSim::expandStat(int arrival)
{

		Redline[arrival-1].statMaxSize = Redline[arrival-1].statCurrOccup * 2 + 2;

		Passenger *temp = new Passenger [Redline[arrival-1].statMaxSize];


		for ( int i = 0 ; i < Redline[arrival-1].statCurrOccup; i++){
			
			temp[i] = Redline[arrival-1].atStation[i];

		}

		delete [] Redline[arrival-1].atStation;
		
	    Redline[arrival-1].atStation = temp;
	

}

void MetroSim::expandTrain()
{

	if (trainCurrOccup >= trainMaxSize){
		trainMaxSize = trainMaxSize * 2;
		Passenger*temp = new Passenger [trainMaxSize];
		for ( int i = 0 ; i < trainCurrOccup; i++){
			temp[i] = Joe.onTrain[i];
		}
		delete [] Joe.onTrain;
		
	    Joe.onTrain = temp;
	}
}


// Function shrink
// Parameters: none
// Returns: none
// Does: decrease the size of the array by a factor of 2
void MetroSim::shrink()
{
	//TODO
	// make sure to call shrink for all remove cases.

	stationSize = stationSize / 2;
	Station *temp = new Station [stationSize];
	for ( int i = 0 ; i < stationOccup; i++){
		temp[i] = Redline[i];
	}
	delete [] Redline;
	
    Redline = temp;


}

void MetroSim::shrinkTrain()
{
	//TODO
	// make sure to call shrink for all remove cases.

	trainMaxSize = trainMaxSize / 2;
	Passenger*temp = new Passenger [trainMaxSize];
	for ( int i = 0 ; i < trainCurrOccup; i++){
		temp[i] = Joe.onTrain[i];
	}
	delete [] Joe.onTrain;
	
    Joe.onTrain = temp;
}

void MetroSim::shrinkStat(int arrival)
{
	//TODO
	// make sure to call shrink for all remove cases.

	Redline[arrival-1].statMaxSize = Redline[arrival-1].statCurrOccup + 2;
	Passenger *temp = new Passenger [Redline[arrival-1].statMaxSize];


	for ( int i = 0 ; i < Redline[arrival-1].statMaxSize; i++){
		temp[i] = Redline[Joe.location - 1].atStation[i];
	}


	delete [] Redline[Joe.location - 1].atStation;
	
    Redline[Joe.location - 1].atStation = temp;
}

// Function generateException
// Parameters: string exceptionName
// Returns: none
// Does: return the appropriatae error message given the 
// exceptionName

void MetroSim :: generateException(string exceptionName)
     throw(int, string, invalid_argument, logic_error)
{
     if (exceptionName == string("int"))
	  throw -1;
     else if (exceptionName == string("invalid_argument"))
	  throw invalid_argument("bad arg!");
     else if (exceptionName == string("string"))
	  throw string("I'm just a string");
     else if (exceptionName == string("logic_error"))
	  throw logic_error("Bud Lojack");
     else if (exceptionName == string("range_error"))
          throw out_of_range("Value out of range");

}

int MetroSim :: string2int(string s)
{
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}


