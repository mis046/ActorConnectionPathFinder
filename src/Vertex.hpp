#define VERTEX_HPP

#include <string>
#include <vector>
#include <climits>

using namespace std;

class Vertex {
  public:
    int dist;
    string prev;
    string prevEdge;
    bool done;

    /**
     * Constructor of the Node class
     * Parameter is the name of this node
     */
    Vertex() {
        dist = INT_MAX;
        prev = "";
        prevEdge = "";
        done = false;
    }
};
