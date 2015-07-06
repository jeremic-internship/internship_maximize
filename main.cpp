// Made in 2 hours and 13 minutes.
// Deal with it.

#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main () {
	// ofstream dataFile;
	// dataFile.open ("data.dat");
	// dataFile << "Writing this to a file.\n";
	// dataFile.close();
	// return 0;


	std::ifstream t("data.dat");
	std::string fileText((std::istreambuf_iterator<char>(t)),
    std::istreambuf_iterator<char>());


	int i = 0;
	stringstream ssin(fileText);

	vector< vector<int> > dataVector;
	
	while (ssin.good()) {
		string tmp;
		ssin >> tmp;
		if (i != 0) {
			if (i % 2 == 1) {
				std::vector<int> tmpVec;
				tmpVec.push_back(atoi(tmp.c_str()));
				dataVector.push_back(tmpVec);
			} else {
				dataVector[dataVector.size()-1].push_back(atoi(tmp.c_str()));
			}
		}
		++i;
	}

	// At this point, dataVector contains the dataset in the form of a multidimensional vector.

	std::sort(dataVector.begin(), dataVector.end(), [](const std::vector< int >& a, const std::vector< int >& b){ return a[1] > b[1]; } ); //If you want to sort in ascending order, then substitute > with <.

	int weightMax = 9; // /!\ READ THIS!!!!!!! The total weight will be LESS THAN this, as specified in the instructions.  Thus, Max is not a good name, but deal with it.
	int currentWeight = 0;
	int currentValue = 0;
	string weightSubset = "";
	string valueSubset = "";

	for( int i=0; i<dataVector.size(); ++i) {
		if (currentWeight + dataVector[i][0] < weightMax) {
			currentWeight = currentWeight + dataVector[i][0];
			currentValue = currentValue + dataVector[i][1];

			int tmpWeight = dataVector[i][0];
			int tmpValue = dataVector[i][1];

			if (i != 0) {
				weightSubset.append(", ");
				valueSubset.append(", ");
			}	

			weightSubset.append(to_string(tmpWeight));
			valueSubset.append(to_string(tmpValue));
		}
	}

	weightSubset.append(" -> ");
	valueSubset.append(" -> ");
	weightSubset.append(to_string(currentWeight));
	valueSubset.append(to_string(currentValue));

	cout << weightSubset << "\n" << valueSubset << "\n";

	ofstream outfile;
	outfile.open ("subset.res");
	outfile << weightSubset << "\n" << valueSubset << "\n";
	outfile.close();
}