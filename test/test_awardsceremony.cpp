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
    auto start_time = high_resolution_clock::now();

    // build actor ActorGraph
    ActorGraph * ag = new ActorGraph();
    ag->loadFromFile("tsv/movie_casts_medium.tsv", false);
    // call function to get the core table:
    vector<string> * core = ag->getCore(100);
    for (unsigned int i = 0; i < core->size(); i ++) {
        cout<<core->at(i)<<"   ";
    }
    cout << endl;
    cout << core->size() << endl;
    // pair<vector<string>, vector<int>> * getCoreTable();
    // delete core table
    // write the actors has core at least k to the outputfile

    delete ag;
    delete core;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_time);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << "Runtime in microseconds: " << duration.count() << endl;
}
