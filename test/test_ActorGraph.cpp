#include <vector>
#include <string>
#include "../src/ActorGraph.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

/**
 * Test Driver for the Autocomplete class
 */
int main() {
    // Use auto keyword to avoid typing long
    // type definitions to get the timepoint
    // at this instant use function now()
    auto start = high_resolution_clock::now();

    // build unweighed graph with tsv/movie_casts_small.tsv
    string s = "tsv/movie_casts_small.tsv";
    const char * in_filename = s.c_str();;
    const bool use_weighted_edges = false;

    ActorGraph ag = ActorGraph();
    ag.loadFromFile(in_filename, use_weighted_edges);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // To get the value of duration use the count()
    // member function on the duration object
    cout << "Runtime in microseconds: " << duration.count() << endl;
}
