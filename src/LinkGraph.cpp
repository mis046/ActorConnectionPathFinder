/*
 * LinkGraph.cpp
 */
#include "LinkGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

LinkGraph::ActorGraph() {
    actors = new unordered_map<string, vector<string>>();
}
LinkGraph::~ActorGraph() {
    delete actors;
}

void LinkGraph::add(string & actor1, string & actor2) {
    // new actor
    // check if the hashmaps already contains the actor or movie
    if (actors->count(actor_name) == 0) {
        vector<string> neighbors;
        neightbors.push_back(actor2);
        // add to hashmap
        actors->insert(pair<string, Node>(actor_name, newActor));
    } else {
        actors->at(actor_name).addEdge(title_year);
    }

    if (movies->count(title_year) == 0) {
        Edge newMovie = Edge(title_year);
        if (use_weighted_edges) {
            int weight = 1 + (2018 - movie_year);
            newMovie = Edge(title_year, weight);
        }
        newMovie.addNode(actor_name);
        // add to hashmap
        movies->insert(pair<string, Edge>(title_year, newMovie));
    } else {
        movies->at(title_year).addNode(actor_name);
    }
}

bool LinkGraph::loadFromFile(const char *in_filename,
                              const bool use_weighted_edges) {
  // Initialize the file stream
  ifstream infile(in_filename);

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
    vector<string> record;

    while (ss) {
      string next;

      // get the next string before hitting a tab character and put it in 'next'
      if (!getline(ss, next, '\t')) break;

      record.push_back(next);
    }

    if (record.size() != 3) {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

    // TODO: we have an actor/movie relationship, now what?
    add(actor_name, movie_title, movie_year, use_weighted_edges);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;
}

bool LinkGraph::containsActor(string & actor) {
    if (actors->count(actor) == 0) {
        return false;
    } else {
        return true;
    }
}
int LinkGraph::getActorNum() {
    return actors->size();
}
