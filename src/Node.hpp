/*
 * Node class is used to represent the nodes in the graph.
 * A Node could have many edges, each goes to another different node.
 * Between two nodes there could be multiple edges.
 * A Node contains the information of:
 *   string name: the name of the node.
 *   vector<string> edges: the vector of the names of the edges.
 */

#define NODE_HPP

#include <string>
#include <vector>

using namespace std;

class Node {
  public:
    string name;
    vector<string> edges;

    /**
     * Constructor of the Node class
     * Parameter is the name of this node
     */
    Node(string & s) {
        name = s;
        edges = vector<string>();
    }
    /**
     * Function used to add an edge to the node
     */
    void addEdge(string & edgeName) {
        edges.push_back(edgeName);
    }
};
