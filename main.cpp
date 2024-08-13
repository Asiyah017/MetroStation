/*
 *
 */
#include <iostream>
#include <fstream>
#include <string>

#include "MetroLine.h"

using namespace std;

int main(int argc, char *argv[])
{
	MetroSim teni;
	ifstream infile;
	ofstream outfile;


	if (argc == 3){

		string stationsFile = argv[1];
		
		infile.open(stationsFile);
		
		teni.read_stationsFile(infile);


		teni.print();

		infile.close();


		
		string outputFile = argv[2];
	
		outfile.open(outputFile);

		
		string commandsFile = argv[3];
		
		infile.open(commandsFile);

		teni.read_commandsFile(cin, cout, &commandsFile);

		outfile.close();
		
	}

	else if ( argc == 4){
		
		string stationsFile = argv[1];
		
		infile.open(stationsFile);

		teni.read_stationsFile(infile);

		infile.close();


		
		string outputFile = argv[2];
		
		outfile.open(outputFile);

		
	    

		string commandsFile = argv[3];
		
		infile.open(commandsFile);


		teni.read_commandsFile(infile, outfile, &commandsFile);
		
		infile.close();

		outfile.close();
		

	}

	else {
		cerr << "Usage: MetroSim stationsFile outputFile"
				 << " [commandsFile]" << endl;
	}
	return 0;
}
