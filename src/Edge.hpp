/*
 * Edge class is used to represent the edges in a graph.
 * Edge has the following properties:
 *   string name: the name of the edge
 *   vector<string>: nodes the edge connects
 *   string weight: the weight of the edge
 */

#define EDGE_HPP

#include <string>
#include <vector>

using namespace std;

class Edge {
  public:
    string name;
    vector<string> nodes;
    int weight;

    /**
     * Constructor of the Edge class
     * Parameter: name
     * Unweighed
     */
    Edge(string & s_name) {
        name = s_name;
        weight = 1;
        nodes = vector<string>();
    }
    /**
     * Constructor of the Edge class
     * Parameter: name weight
     */
    Edge(string & s_name, int i_weight) {
        name = s_name;
        weight = i_weight;
        nodes = vector<string>();
    }
    /**
     * Function used to add an edge to the node
     */
    void addNode(string & nodeName) {
        nodes.push_back(nodeName);
    }
};
