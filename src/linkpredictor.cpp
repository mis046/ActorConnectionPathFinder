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
  // TODO: Implement code for "Part 2: Link Predictor and Recommending New
  // Links"
  // Example usage: > reflinkpredictor      movie_casts.tsv
  // actors.tsv     future_interactions.tsv     new_collaborations.tsv
  if (argc != 5) {
      cout << "Called with incorrect arguments." << endl <<
      "Usage: ./linkpredictor data_file actors_file outfile_future_interactions outfile_new_collaborations" << endl;
      return -1;
  }
  const char * data_file = argv[1];
  string actors_file = string(argv[2]);
  string future_interactions_file = string(argv[3]);
  string new_collaborations_file = string(argv[4]);

  /* build the ActorGraph, get actors input*/
  ActorGraph * ag = new ActorGraph();
  ag->loadFromFile(data_file, false);
  vector<string> actors;
  ifstream infile(actors_file);
  bool have_header = false;
  // keep reading lines until the end of file is reached
  while (infile) {
    string s;
    // get the next line
    if (!getline(infile, s)) break;
    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }
    istringstream ss(s);
    vector<string> actor_pair;
    while (ss) {
      string next;
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline(ss, next, '\t')) break;
      actors.push_back(next);
    } /*
    if (actor_pair.size() != 1) {
      // we should have exactly 2 columns
      continue;
    }
    actors.push_back(actor_pair.at(0));*/
  }
  if (!infile.eof()) {
    cerr << "Failed to read " << actors_file << "!\n";
    return -1;
  }
  infile.close();

  cout << "Actors Tested:" << endl;
  for (unsigned int i = 0; i < actors.size(); i ++) {
    cout << actors.at(i) << endl;
  }

  cout << "Testing Future Interactions" << endl;
  /* predict future interactions and write to file*/
  ofstream outfile1(future_interactions_file);
  outfile1 << "Actor1,Actor2,Actor3,Actor4" << endl;
  for (unsigned int i = 0; i < actors.size(); i ++) {
  vector<string> result = ag->future_interactions(actors.at(i));
    for (unsigned int j = 0; j < result.size(); j ++) {
        outfile1 << result.at(j);
        if (j != result.size() - 1) {
            outfile1 << '\t';
        }
    }
    //if (i != actors.size() - 1) {
    outfile1 << endl;
    //}
  }
  outfile1.close();

  cout << "Testing New Collaborations" << endl;
  /* predict new collaborations and write to file*/
  ofstream outfile2(new_collaborations_file);
  outfile2 << "Actor1,Actor2,Actor3,Actor4" << endl;
  for (unsigned int i = 0; i < actors.size(); i ++) {
  vector<string> result = ag->new_collaborations(actors.at(i));
    for (unsigned int j = 0; j < result.size(); j ++) {
        outfile2 << result.at(j);
        if (j != result.size() - 1) {
            outfile2 << '\t';
        }
    }
    //if (i != actors.size() - 1) {
    outfile2 << endl;
    //}
  }
  outfile2.close();
  delete ag;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start_time);
  long seconds = duration.count() / 1000000;
  // To get the value of duration use the count()
  // member function on the duration object
  cout << "Runtime in microseconds: " << duration.count() <<
  "     seconds: " << seconds << endl;
  return 0;
}
