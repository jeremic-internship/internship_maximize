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
#include <cstdlib>
#include <numeric>

using namespace std;

vector< vector<int> > dataVector;
vector<int> combination;
vector<int> combinationValue;
vector<int> maxValueSeenList;
vector<int> weightList;
int weightMax;
int maxValueSeen = 0;

void go(int offset, int k) {
  if (k == 0) {
  	if (std::accumulate(combination.begin(),combination.end(),0) < weightMax) {
  		if (accumulate(combinationValue.begin(),combinationValue.end(),0) > maxValueSeen) {
  			maxValueSeen = accumulate(combinationValue.begin(),combinationValue.end(),0);
  			maxValueSeenList = combinationValue;
  			weightList = combination;
  		}
  	}
    return;
  }
  for (int i = offset; i <= dataVector.size() - k; ++i) {
    combination.push_back(dataVector[i][0]);
    combinationValue.push_back(dataVector[i][1]);
    go(i+1, k-1);
    combination.pop_back();
    combinationValue.pop_back();
  }
}

int main( int argc, char *argv[] ) {
	// ofstream dataFile;
	// dataFile.open ("data.dat");
	// dataFile << "Writing this to a file.\n";
	// dataFile.close();
	// return 0;

	if (argc < 2) {
		cout << "This program takes one argument, the maximum weight...\n";
		return 666;
	}


	std::ifstream t("data.dat");
	std::string fileText((std::istreambuf_iterator<char>(t)),
    std::istreambuf_iterator<char>());


	int i = 0;
	stringstream ssin(fileText);
	
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

	weightMax = atoi(argv[1]); // /!\ READ THIS!!!!!!! The total weight will be LESS THAN this, as specified in the instructions.  Thus, Max is not a good name, but deal with it.

	for (int z = 1; z <= dataVector.size(); z++) {
		go(0, z);
	}

	ofstream outfile;
	outfile.open ("subset.res");

	for (int i = 0; i < weightList.size(); i++) {
		if (i != 0) {
			outfile << ", ";
		}
		outfile << weightList[i];
	}

	outfile << " -> " + to_string(accumulate(weightList.begin(),weightList.end(),0));
	
	outfile << "\n";

	for (int i = 0; i < maxValueSeenList.size(); i++) {
		if (i != 0) {
			outfile << ", ";
		}
		outfile << maxValueSeenList[i];
	}

	outfile << " -> " + to_string(accumulate(maxValueSeenList.begin(),maxValueSeenList.end(),0));
	
	outfile << "\n";
	
	outfile.close();

}