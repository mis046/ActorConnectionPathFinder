#include "../src/ActorGraph.hpp"
#include <iostream>
#include <chrono>
#include <vector>

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

    // tests go here
    /*
    AdjacencyMatrix * am = new AdjacencyMatrix();
    am->buildMatrix("tsv/movie_casts.tsv");
    //am->printMatrix();
    vector<vector<int>> * mo = am->commonNeighborsMatrix();
    delete am;
    delete mo;
    */
    ActorGraph * ag = new ActorGraph();
    ag->loadFromFile("tsv/movie_casts.tsv", false);
    /*string actor = "50 CENT";
    vector<string> future_interactions = ag->future_interactions(actor);
    cout << "Future_interactions of " << actor << ": " << endl;
    for (unsigned int i = 0; i < future_interactions.size(); i++) {
        cout << future_interactions.at(i) << " ";
    }
    cout << endl;
    actor = "AARON, CAROLINE";
    future_interactions = ag->future_interactions(actor);
    cout << "Future_interactions of " << actor << ": " << endl;
    for (unsigned int i = 0; i < future_interactions.size(); i++) {
        cout << future_interactions.at(i) << " ";
    }
    cout << endl;
    actor = "AARONS, BONNIE";
    future_interactions = ag->future_interactions(actor);
    cout << "Future_interactions of " << actor << ": " << endl;
    for (unsigned int i = 0; i < future_interactions.size(); i++) {
        cout << future_interactions.at(i) << " ";
    }
    cout << endl;
    actor = "AASLAND, DEREK";
    future_interactions = ag->future_interactions(actor);
    cout << "Future_interactions of " << actor << ": " << endl;
    for (unsigned int i = 0; i < future_interactions.size(); i++) {
        cout << future_interactions.at(i) << " ";
    }
    cout << endl;
    actor = "ABATEMARCO, TONY";
    future_interactions = ag->future_interactions(actor);
    cout << "Future_interactions of " << actor << ": " << endl;
    for (unsigned int i = 0; i < future_interactions.size(); i++) {
        cout << future_interactions.at(i) << " ";
    }
    cout << endl; */

    string actor = "50 CENT";
    vector<string> newC = ag->new_collaborations(actor);
    cout << "new_collaborations of " << actor << ": " << endl;
    for (unsigned int i = 0; i < newC.size(); i++) {
        cout << newC.at(i) << " ";
    }

    delete ag;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_time);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << "Runtime in microseconds: " << duration.count() << endl;
}
