#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
  auto start_time = high_resolution_clock::now();

  // TODO: Implement code for "Part 3: Award Ceremony Invitation"
  if (argc != 4) {
      cout << "Called with incorrect arguments"<< endl <<
      "Usage: ./awardsceremony k outfile" << endl;
      return -1;
  }
  const char * data_file = argv[1];
  int k = stoi(string(argv[2]));
  string output_file = string(argv[3]);

  // build actor ActorGraph
  ActorGraph * ag = new ActorGraph();
  ag->loadFromFile(data_file, false);
  // call function to get the core
  vector<string> * core = ag->getCore(k);

  ofstream outfile(output_file);
  outfile << "Actor" << endl;
  for (unsigned int i = 0; i < core->size(); i++) {
      outfile << core->at(i) << endl;
  }
  outfile.close();
  // pair<vector<string>, vector<int>> * getCoreTable();
  // delete core table
  // write the actors has core at least k to the outputfile

  delete ag;
  delete core;

  outfile.close();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start_time);
  long seconds = duration.count() / 1000000;
  // To get the value of duration use the count()
  // member function on the duration object
  cout << "Runtime in microseconds: " << duration.count() <<
  "     seconds: " << seconds << endl;
  return 0;
}
