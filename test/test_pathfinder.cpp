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

    // build unweighed graph with tsv/movie_casts_small.tsv
    string s = "tsv/movie_casts.tsv";
    const char * in_filename = s.c_str();;
    const bool use_weighted_edges = true;

    ActorGraph ag = ActorGraph();
    ag.loadFromFile(in_filename, use_weighted_edges);

    cout << "graph finished building" << endl;
    // pathfinder tests
    string start = "50 CENT";
    string end = "B-REAL";

    cout << "should return 1" << endl;
    //int length = ag.unweighted_path(start, end);
    stack<string> result = ag.weighted_path(start, end);
    while (!result.empty()) {
        cout << result.top() << " -> ";
        result.pop();
    } cout << endl;

    //cout << "path length:" << length << endl;

    end = "HANNA, SALEM";
    cout << "should return less than or equal to 4" << endl;
    //length = ag.unweighted_path(start, end);
    //cout << "path length:" << length << endl;
    result = ag.weighted_path(start, end);
    while (!result.empty()) {
        cout << result.top() << " -> ";
        result.pop();
    } cout << endl;

    start = "JACKSON, DEE JAY";
    //cout << "should return 0" << endl;
    //length = ag.unweighted_path(start, end);
    //cout << "path length:" << length << endl;
    result = ag.weighted_path(start, end);
    while (!result.empty()) {
        cout << result.top() << " -> ";
        result.pop();
    } cout << endl;

    end = "ABC";
    //cout << "should return -1" << endl;
    //length = ag.unweighted_path(start, end);
    //cout << "path length:" << length << endl;
    result = ag.weighted_path(start, end);
    while (!result.empty()) {
        cout << result.top() << " -> ";
        result.pop();
    } cout << endl;

    start = "BONES, KEN";
    end = "FACIO, GIANNINA";
    cout << "should return 1" << endl;
    //length = ag.unweighted_path(start, end);
    //cout << "path length:" << length << endl;
    result = ag.weighted_path(start, end);
    while (!result.empty()) {
        cout << result.top() << " -> ";
        result.pop();
    } cout << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_time);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << "Runtime in microseconds: " << duration.count() << endl;
}
