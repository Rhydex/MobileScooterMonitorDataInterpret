#include <string>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <math.h>

using namespace std;
float s_t_i(string s) {
	istringstream instr(s);
	float n;
	instr >> n;
	return n;
};
string removeCommas(string input) {
	std::replace(input.begin(), input.end(), ',', ' ');
	return input;
}
string* parseLine(string input) {
	string* output = new string[11]; //cout << "output created" << endl;
	istringstream iss(input); //cout << "iss opened" << endl;
	int i = 0;
	do {
		string temp;
		iss >> temp;
		output[i] = temp;
		i++;
		//cout << i << "processed" << endl;
	} while (i<5);
	return output;
}


int main(int argc, char *argv[]) {
	//File labeled and opened
	fstream file, outputFile; string fileName, fileName2;

	//CHECKS FOR CMD LINE ARGUMENTS, assigns defaults for input and output file names based on number of arguments
	if (argc >1) {fileName2 = argv[2];}
	else { fileName2 = "output.csv";}
	if (argc> 0) { fileName = argv[1]; }
	else { fileName = "input.csv"; }

	file.open(fileName.c_str());
	outputFile.open(fileName2.c_str(), ios::out);

	//Declare string for input and scrape first line 
	string input = ""; float deltaX=0, deltaY=0, deltaZ=0, resultant=0;
	float x = 0, y = 0, z = 0, degree = 0;
	getline(file, input);
	outputFile << input << endl;

	//THESE INTS are used to show the range for cout<<endl;
	int showline = 0;

	//Loop through every remaining line of CVS file, using input as the unparsed input string
	while (getline(file, input)) {
		if (input.length() < 15) { break; }
		input = removeCommas(input); 
		string* parsedLine = parseLine(input); 
		float preX = x, preY = y, preZ = z;

		// convert and input into array
			x = s_t_i(parsedLine[1]),
			y=s_t_i(parsedLine[2]),
			z=s_t_i(parsedLine[3]),
			degree=s_t_i(parsedLine[4]);

			deltaX = -(preX - x); deltaY = -(preY - y); deltaZ = -(preZ - z); 
		resultant = sqrtf(powf(deltaX,2) + powf(deltaY,2) + powf(deltaZ,2));

		//Put deltas within the array
		parsedLine[5] = to_string(deltaX);
		parsedLine[6] = to_string(deltaY);
		parsedLine[7] = to_string(deltaZ);
		parsedLine[8] = to_string(resultant);
		

		//determine if moving or not, and apply such
		parsedLine[9] = (resultant > 2) ? "1":"0";
		
		//ensure non-undefined behavior
		parsedLine[10] = ' ';

		//FOR TESTING print out data
		if (showline > -1 && showline < 10) {
			for (int i = 0; i < 11; i++) {
				if (i != 0) { cout << ","; }
				cout << parsedLine[i];

			}
			cout << endl;
		} showline++;

		for (int i =0; i < 10; i++) { outputFile << parsedLine[i] << ","; } outputFile << parsedLine[10] << endl;

		//DELETE parsedLine HERE
		delete[] parsedLine;
	}

	
	std::cin >> input;
	//outputFile.close();
	file.close();
	//Last Line requirements?
	outputFile.close();
	return 1;
}

