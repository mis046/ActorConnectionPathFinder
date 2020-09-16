/*
 * LinkGraph class is used in linkpredictor. It is a graph of connected nodes
 * with unweighted path. The graph is backed with a hashmap of strings (nodes)
 * to string vectors containing its neighbor nodes.
 */
#ifndef LINKGRAPH_HPP
#define LINKGRAPH

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class LinkGraph {
 protected:
  // Maybe add class data structure(s) here
  unordered_map<string, vector<string>> * actors;

 public:
  ActorGraph();
  ~ActorGraph();

  // Maybe add some more methods here...

  /**
   * This function adds actor - actor relationship by adding name to the vector
   */
  void add(string & actor1, string & actor2);

  /**
   * Load the graph from a tab-delimited file of actor relationships.
   * in_filename - input filename
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char *in_filename);


  bool LinkGraph::containsActor(string & actor);
  int LinkGraph::getActorNum();
};

#endif  // LinkGraph
