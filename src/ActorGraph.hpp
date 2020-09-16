/*
 * ActorGraph.hpp
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>

// Maybe include some data structures here
#include "Node.hpp"
#include "Edge.hpp"
#include <unordered_map>
#include <stack>

class paircomp_rev
{
    bool reverse;
    public:
    // return left > right
    paircomp_rev(const bool& revparam=false)
        {reverse=revparam;}
    bool operator() (const pair<int, string> & lhs,
        const pair<int, string> & rhs) const
    {
        if (lhs.first == rhs.first) {
            return rhs.second < lhs.second;
        }
        if (reverse) return (lhs.first>rhs.first);
        else return (lhs.first<rhs.first);
     }
};
class paircomp
{
    bool reverse;
    public:
    // return left > right
    paircomp(const bool& revparam=false)
        {reverse=revparam;}
    bool operator() (const pair<int, string> & lhs,
        const pair<int, string> & rhs) const
    {
        if (lhs.first == rhs.first) {
            return rhs.second > lhs.second;
        }
        if (reverse) return (lhs.first<rhs.first);
        else return (lhs.first>rhs.first);
     }
};

class ActorGraph {
 protected:
  // Maybe add class data structure(s) here
    unordered_map<string, Node> * actors;
    unordered_map<string, Edge> * movies;

 public:
  ActorGraph(void);
  ~ActorGraph();

  // Maybe add some more methods here...

  /**
    * Return k core
    */
  vector<string> * getCore(int k);

  /**
    * Returns the top 4 actors two hops away with the most common
    * neighbors with the given actor.
    */
  vector<string> new_collaborations(string & actor);
  /**
    * Returns the top 4 neighbors with the most common
    * neighbors with the given actor.
    */
  vector<string> future_interactions(string & actor);

  int getActorNum();
  int getMovieNum();
  bool containsActor(string & actor);
  /**
   * Find shorted path between to nodes, unweighted. Return a string
   * vector of path names.
   */
   stack<string> * unweighted_path(string & node1, string & node2);
   stack<string> * weighted_path(string & node1, string & node2);

  /**
   * This function adds actor - movie relationship with vector containing
   * actor, movie, movie year. Return true if success. False if not.
   */
  void add(string & actor_name, string & movie_title, int & movie_year,
           bool use_weighted_edges);

  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2018 -
   * movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char *in_filename, const bool use_weighted_edges);
};

#endif  // ACTORGRAPH_HPP
