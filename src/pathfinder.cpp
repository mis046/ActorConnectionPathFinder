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
    // TODO: Implement code for "Part 1: Path Finder"
    // example usage:
    //> ./pathfinder movie_casts.tsv u test_pairs.tsv out_paths_unweighted.tsv
    if (argc != 5) {
        cout << "Called with incorrect arguments." << endl <<
        "Usage: ./pathfinder data_file u/w pair_file out_file" << endl;
        return -1;
    }
    cout << "args: " << argv[1] << " " << argv[2] << " " <<
    argv[3] << " " << argv[4] << endl;

    const char * data_file = argv[1];
    bool use_weighted_edges = false;
    string weight_str(argv[2]);
    if (weight_str == "w") {
        use_weighted_edges = true;
    }
    string input_file = string(argv[3]);
    string output_file = string(argv[4]);

    /* 1. build the actor graph, with infile and weight flag*/
    ActorGraph ag = ActorGraph();
    ag.loadFromFile(data_file, use_weighted_edges);
    cout << "Actor number: " << ag.getActorNum() << endl;
    cout << "Movie number: " << ag.getMovieNum() << endl;


    /* 2. Read each line of the file of pair of actors */
    // Initialize the file stream
    ifstream infile(input_file);
    ofstream outfile(output_file);

    outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;

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
        actor_pair.push_back(next);
      }
      if (actor_pair.size() != 2) {
        // we should have exactly 2 columns
        continue;
      }
      string actor1(actor_pair[0]);
      string actor2(actor_pair[1]);
      cout << "Computing path for (" << actor1 <<
              ") -> (" << actor2 << ")" << endl;

      if (!ag.containsActor(actor1)) {
        cout << "Failed to locate node " << actor1 << endl;
        cout << "Called with incorrect arguments." << endl <<
        "Usage: ./pathfinder data_file u/w pair_file out_file" << endl;
        return -1;
      }
      if (!ag.containsActor(actor2)) {
          cout << "Failed to locate node " << actor2 << endl;
          cout << "Called with incorrect arguments." << endl <<
          "Usage: ./pathfinder data_file u/w pair_file out_file" << endl;
          return -1;
      }

      /* 3. For each line, call (un)weightedfind path function to find path */
      stringstream path_str;
      stack<string> * path_stack;
      if (!use_weighted_edges) {
        path_stack = ag.unweighted_path(actor1, actor2);
      }
      else {
        path_stack = ag.weighted_path(actor1, actor2);
      }
      path_str << "(" << path_stack->top() << ")";
      path_stack->pop();
      while (!path_stack->empty()) {
          //(FABIAN, AVA)--[MOBSTERS#@1991]-->
          //(COLLISON, FRANK)--[SUSPECT ZERO#@2004]-->
          //(CHAPMAN, MICHAEL (I))
          path_str << "--[" << path_stack->top() << "]-->";
          path_stack->pop();
          path_str << "(" << path_stack->top() << ")";
          path_stack->pop();
      }
      outfile << path_str.str() << endl;
      delete path_stack;
    }

    if (!infile.eof()) {
      cerr << "Failed to read " << input_file << "!\n";
      return -1;
    }
    infile.close();
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
