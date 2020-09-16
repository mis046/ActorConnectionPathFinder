/*
 * ActorGraph.cpp
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in movie_casts.tsv.
 *
 * Feel free to modify any/all aspects as you wish.
 */
#include "ActorGraph.hpp"
#include "Vertex.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

ActorGraph::ActorGraph(void) {
    actors = new unordered_map<string, Node>();
    movies = new unordered_map<string, Edge>();
    // edge names are in form "movie_name#@year"
}
ActorGraph::~ActorGraph() {
    delete actors;
    delete movies;
}

vector<string> * ActorGraph::getCore(int k) {
    // initialize an output list L.
    unordered_set<string> * l = new unordered_set<string>();
    unordered_map<string, int> * index = new unordered_map<string, int>();
    vector<pair<string, int>> * vertices = new vector<pair<string, int>>();
    int maxDegree = 0;
    auto it = actors->begin();
    auto end = actors->end();
    while (it != end) {
        string name = (*it).first;
        int degree = 0;
        unordered_set<string> * visited = new unordered_set<string>();
        visited->insert(name);
        for (unsigned int i = 0; i < (*it).second.edges.size(); i++) {
            string movie = (*it).second.edges.at(i);
            for (unsigned int j = 0; j < movies->at(movie).nodes.size(); j++) {
                string actor = movies->at(movie).nodes.at(j);
                if (visited->count(actor) == 0) {
                    visited->insert(actor);
                    degree ++;
                }
            }
        }
        if (degree > maxDegree) {maxDegree = degree;}
        vertices->push_back(pair<string, int>(name, degree));
        index->insert(pair<string, int>(name, degree));
        it++;
        delete visited;
    }

    cout << "maxDegree " << maxDegree << endl;
    if (k > maxDegree) {
        return new vector<string>();
    }

    // Initialize an array D such that D[i] contains a list of the vertices v
    // that are not already in L for which dv = i.
    vector<unordered_set<string> *> d(maxDegree+1);
    for (unsigned int i = 0; i < vertices->size(); i ++) {
        string name = vertices->at(i).first;
        int degree = vertices->at(i).second;
        if (d.at(degree) == NULL) {
            d.at(degree) = new unordered_set<string>();
        }
        d.at(degree)->insert(name);
    }

    // Initialize k to 0.
    // int k = 0;
    // Repeat n times:
    for (int i = 0; i < k; i ++) {
        // Scan the array cells D[0], D[1], ... until finding an i for which D[i] is nonempty.
        if (d.at(i) != NULL) {
            // Set k to max(k,i)
            // k = max(k, i);
            // Select a vertex v from D[i]. Add v to the beginning of L and remove it from D[i].
            auto it = d.at(i)->begin();
            auto end = d.at(i)->end();
            while (it != end) {
                string currV = (*it);
                if (l->count(currV) == 0) {
                    l->insert(currV);
                    // For each neighbor w of v not already in L, subtract one from dw
                    // and move w to the cell of D corresponding to the new value of dw.
                    unordered_set<string> * checked = new unordered_set<string>();
                    for (unsigned int a = 0; a < actors->at(currV).edges.size(); a ++) {
                        string currE = actors->at(currV).edges.at(a);
                        for (unsigned int b = 0; b < movies->at(currE).nodes.size(); b++) {
                            string currW = movies->at(currE).nodes.at(b);
                            if (checked->count(currW) == 0){
                                checked->insert(currW);
                                if (l->count(currW) == 0) {
                                    int wInd = index->at(currW);
                                    d.at(wInd)->erase(currW);
                                    if (wInd-1 > 0) {
                                        if (d.at(wInd-1) == NULL) {
                                            d.at(wInd-1) = new unordered_set<string>();
                                        }
                                        d.at(wInd-1)->insert(currW);
                                        index->at(currW) = wInd-1;
                                    }
                                    else {
                                        index->erase(currW);
                                        l->insert(currW);
                                    }
                                    if (wInd-1 < i+1 && wInd-1>0) {
                                        i = wInd-1-1;
                                    }
                                }
                            }
                        }
                    }
                    delete checked;
                }

                it++;
            }
        }
    }
    vector<string> * result = new vector<string>();
    // delete d and add actos at least k core to result
    for (unsigned int i = 0; i < d.size(); i ++) {
        // cout << i << endl;
        if (d.at(i) != NULL) {
            if (i >= (unsigned)k) {
                auto it = d.at(i)->begin();
                auto end = d.at(i)->end();
                while (it != end) {
                    if (l->count(*it) == 0) {
                        result->push_back(*it);
                    }
                    it ++;
                }
            }
        }
        delete d.at(i);
    }
    delete index;
    delete vertices;
    delete l;

    sort(result->begin(), result->end());
    return result;
}


vector<string> ActorGraph::new_collaborations(string & actor) {
    Node * curr = &(actors->at(actor));
    vector<string> result = vector<string>();

    unordered_set<string> * neighbors = new unordered_set<string>();
    for (unsigned int i = 0; i < curr->edges.size(); i++) {
        for (unsigned int j = 0; j < movies->at(curr->edges.at(i)).nodes.size();
         j++) {
            string name = movies->at(curr->edges.at(i)).nodes.at(j);
            if (name != actor) {
                neighbors->insert(movies->at(curr->edges.at(i)).nodes.at(j));
            }
        }
    }
    typedef std::priority_queue<pair<int, string>,
            std::vector<pair<int, string>>, paircomp_rev> mypq;
    mypq count;
    int commonNum = 0;

    unordered_set<string> tested1;
    unordered_set<string> tested2;


    for (unsigned int a = 0; a < curr->edges.size(); a++) {
        string movie1 = curr->edges.at(a);
        for (unsigned int b = 0; b < movies->at(movie1).nodes.size(); b++) {
            string actor1 = movies->at(movie1).nodes.at(b);
            if (actor1 != actor && tested1.count(actor1) == 0) {
                tested1.insert(actor1);
                for (unsigned int c = 0; c < actors->at(actor1).edges.size(); c++) {
                    string movie2 = actors->at(actor1).edges.at(c);
                    for (unsigned int d = 0; d < movies->at(movie2).nodes.size(); d ++) {
                        string actor2 = movies->at(movie2).nodes.at(d);
                        if (actor2 != actor &&
                            neighbors->count(actor2) == 0 &&
                            tested2.count(actor2) == 0) {
                            tested2.insert(actor2);
                            // check for this actor
                            unordered_set<string> * counted = new unordered_set<string>();
                            for (unsigned int e = 0; e < actors->at(actor2).edges.size(); e++) {
                                string hopMovie = actors->at(actor2).edges.at(e);
                                for (unsigned int f = 0; f < movies->at(hopMovie).nodes.size(); f++) {
                                    string hopActor = movies->at(hopMovie).nodes.at(f);
                                    if (hopActor != actor &&
                                        neighbors->count(hopActor) != 0 &&
                                        counted->count(hopActor) == 0) {
                                        counted->insert(hopActor);
                                        commonNum ++;
                                    }
                                }
                            }
                            delete counted;
                            //cout << actor2 << commonNum << "    ";
                            count.push(pair<int, string>(commonNum, actor2));
                            commonNum = 0;
                        }
                    }
                }
            }
        }
    }

    //cout << " " << endl << endl;
    for (int i = 0; i < 4; i ++) {
        result.push_back(count.top().second);
        //cout << count.top().first << ", " << (count.top().second) <<endl;
        count.pop();
    }
    delete neighbors;
    return result;
}

vector<string> ActorGraph::future_interactions(string & actor) {
    Node * curr = &(actors->at(actor));
    vector<string> result = vector<string>();

    unordered_set<string> * neighbors = new unordered_set<string>();
    for (unsigned int i = 0; i < curr->edges.size(); i++) {
        for (unsigned int j = 0; j < movies->at(curr->edges.at(i)).nodes.size();
         j++) {
            string name = movies->at(curr->edges.at(i)).nodes.at(j);
            if (name != actor) {
                neighbors->insert(movies->at(curr->edges.at(i)).nodes.at(j));
            }
        }
    }
    typedef std::priority_queue<pair<int, string>,
            std::vector<pair<int, string>>, paircomp_rev> mypq;
    mypq count;
    int commonNum = 0;
    unordered_set<string> tested;
    for (unsigned int i = 0; i < curr->edges.size(); i++) {
        // cout << "size of actor array " << movies->at(curr->edges.at(i)).nodes.size() << endl;
        for (unsigned int j = 0; j < movies->at(curr->edges.at(i)).nodes.size(); j++) {
            string neighborName = movies->at(curr->edges.at(i)).nodes.at(j);
            if (neighborName != actor && tested.count(neighborName) == 0) {
                unordered_set<string> * counted = new unordered_set<string>();
                tested.insert(neighborName);
                for (unsigned int k = 0; k < actors->at(neighborName).edges.size();
                 k++) {
                    for (unsigned int q = 0;
                    q < movies->at(actors->at(neighborName).edges.at(k)).nodes.size();
                    q++) {
                        string s = movies->at(actors->at(neighborName).edges.at(k)).nodes.at(q);
                        if (counted->count(s) == 0 && neighbors->count(s) != 0) {
                            counted->insert(s);
                            commonNum ++;
                        }
                    }
                }
                delete counted;
                //cout << commonNum << ", " << neighborName << ", ";
                count.push(pair<int, string>(commonNum, neighborName));
                commonNum = 0;
            }
        }
    }
    //cout << " " << endl << endl;
    for (int i = 0; i < 4; i ++) {
        result.push_back(count.top().second);
        //cout << count.top().first << ", " << (count.top().second) <<endl;
        count.pop();
    }
    delete neighbors;
    return result;
}

stack<string> * ActorGraph::weighted_path(string & start, string & end) {
    if (actors->count(start) == 0 || actors->count(end) == 0) {
        return 0; // start not exist
    }

    // --------------- //
    // dijkstra
    // perform initialization step
    typedef std::priority_queue<pair<int, string>,
            std::vector<pair<int, string>>, paircomp> mypq;

    mypq pq; // initialize empty priority_queue

    auto beginIt = actors->begin();
    auto endIt = actors->end();

    unordered_map<string, Vertex> vertexes;

    string curr_actor;
    Vertex emptyV;
    while (beginIt != endIt) {
        curr_actor = (*beginIt).first;
        emptyV = Vertex();
        vertexes.insert(pair<string, Vertex>(curr_actor, emptyV));
        ++beginIt;
    }

    // perform the traversal
    vertexes.at(start).dist = 0;
    pq.push(pair<int, string>(0, start));
    while (!pq.empty()) {
        pair<int, string> curr = pq.top();
        pq.pop();
        if (curr.second == end) {
            stack<string> * result = new stack<string>();
            Vertex curr_v = vertexes.at(end);
            result->push(end);
            while (curr_v.prev != "") {
                result->push(curr_v.prevEdge);
                result->push(curr_v.prev);
                curr_v = vertexes.at(curr_v.prev);
            }
            return result;
        }
        if (vertexes.at(curr.second).done == false) { // if the vertex's min path hasn't been discovered yet
            vertexes.at(curr.second).done = true;
            vector<string> edges = (actors->at(curr.second)).edges;
            for (unsigned int i = 0; i < edges.size(); i ++) {
                vector<string> nodes = movies->at(edges.at(i)).nodes;
                for (unsigned int j = 0; j < nodes.size(); j ++) {
                    string w = nodes.at(j);
                    int c = (vertexes.at(curr.second)).dist + (movies->at(edges.at(i))).weight; // c is the total distance to w through v
                    if (c < vertexes.at(w).dist) {      // if a smaller-weight path has been found
                                        // (remember, all distances start at infinity!)
                        (vertexes.at(w)).prev = curr.second;     // update the node that comes just before w in the path from s to w
                        (vertexes.at(w)).prevEdge = edges.at(i);
                        (vertexes.at(w)).dist = c;      // update the distance of the path from s to w
                        pq.push(pair<int, string>(c, w));
                    }
                }
            }
        }
    }
    // --------------- //
    stack<string> * result = new stack<string>();
    Vertex curr_v = vertexes.at(end);
    result->push(end);
    while (curr_v.prev != "") {
        result->push(curr_v.prevEdge);
        result->push(curr_v.prev);
        curr_v = vertexes.at(curr_v.prev);
    }
    return result;
}

stack<string> * ActorGraph::unweighted_path(string & start, string & end) {
    if (actors->count(start) == 0) {
        return 0;
    }
    queue<string> q = queue<string>();
    unordered_set<string> visited = unordered_set<string>();
    unordered_set<string> pushed = unordered_set<string>();

    // For each vertex you encounter while searching, store a pointer to the
    // vertex from which you arrived at the current vertex.
    // When you reach the target, simply follow these "parent" pointers back
    // to the beginning. That is your path.

    unordered_map<string, string> parents;

    q.push(start);
    parents.insert(pair<string, string>(start, "0"));
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        visited.insert(curr);

        if (curr == end) {
            // if we have reached the vertex we are searching for
            stack<string> * result = new stack<string>();
            while (parents.count(curr) != 0) {
                result->push(curr);
                curr = parents.at(curr);
            }
            return result;
        }

        vector<string> edges = (actors->at(curr)).edges;
        //vector<pair<int, string>> neighbors = vector<pair<int, string>>();
        for (unsigned int i = 0; i < edges.size(); i ++) {
            vector<string> nodes = movies->at(edges.at(i)).nodes;
            for (unsigned int j = 0; j < nodes.size(); j ++) {
                if (visited.count(nodes.at(j)) == 0 &&
                    pushed.count(nodes.at(j)) == 0) {
                    parents.insert(pair<string, string>(edges.at(i), curr));
                    parents.insert(pair<string, string>(nodes.at(j), edges.at(i)));
                    q.push(nodes.at(j));
                    pushed.insert(nodes.at(j));
                }
            }
        }
    }
    return 0;
    // if we reach this point, then no path exists from u to v
}

void ActorGraph::add(string & actor_name, string & movie_title,
                     int & movie_year, bool use_weighted_edges) {
    // new actor
    string title_year = movie_title;
    title_year += "#@";
    title_year += to_string(movie_year); // XXX

    // check if the hashmaps already contains the actor or movie
    if (actors->count(actor_name) == 0) {
        Node newActor = Node(actor_name);
        newActor.addEdge(title_year);
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

bool ActorGraph::loadFromFile(const char *in_filename,
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

bool ActorGraph::containsActor(string & actor) {
    if (actors->count(actor) == 0) {
        return false;
    } else {
        return true;
    }
}
int ActorGraph::getActorNum() {
    return actors->size();
}
int ActorGraph::getMovieNum() {
    return movies->size();
}
