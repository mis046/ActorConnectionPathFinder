#ifndef ADJACENCYMATRIX_HPP
#define ADJACENCYMATRIX_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "MatrixMultiply.hpp"

using namespace std;

class AdjacencyMatrix {
 protected:
    vector<vector<int>> * matrix;
    unordered_map<string, int> * nameIndexMap;
    vector<string> * names;
    unordered_map<string, vector<string>> * moviesToActors;

 public:
    AdjacencyMatrix() {
        matrix = new vector<vector<int>>();
        nameIndexMap = new unordered_map<string, int>();
        names = new vector<string>();
        moviesToActors = new unordered_map<string, vector<string>>();
    }
    ~AdjacencyMatrix() {
        delete matrix;
        delete nameIndexMap;
        delete names;
        delete moviesToActors;
    }

    void buildMatrix(const char *in_filename) {
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
            add(actor_name, movie_title, movie_year); // build connection hashmap
            nameIndexMap->insert(pair<string, int>(actor_name, nameIndexMap->size()));
            names->push_back(actor_name);
        }
        // after we have the hashmap of movie to all actors in that movie
        // would could start to mark connections between characters
        // first, zero fill the matrix
        vector<int> temp = vector<int>();
        for (unsigned int i = 0; i < nameIndexMap->size(); i ++) {
            temp.push_back(0);
        }
        for (unsigned int i = 0; i < nameIndexMap->size(); i ++) {
            matrix->push_back(temp);
        }
        // now use setConnection function to set connections
        auto beginIt = moviesToActors->begin();
        auto endIt = moviesToActors->end();
        while (beginIt != endIt) {
            for (unsigned int i = 1; i < (*beginIt).second.size(); i ++) {
                setConnection((*beginIt).second.at(i), (*beginIt).second.at(i-1));
            }
            beginIt ++;
        }
        // matrix built
    }

    void add(string & actor_name, string & movie_title, int & movie_year) {
        string title_year = movie_title;
        title_year += "#@";
        title_year += to_string(movie_year);
        // check if the hashmaps already contains the movie
        if (moviesToActors->count(title_year) == 0) {
            // add to hashmap
            vector<string> vec = vector<string>();
            vec.push_back(actor_name);
            moviesToActors->insert(pair<string, vector<string>>(title_year, vec));
        } else {
            moviesToActors->at(title_year).push_back(actor_name);
        }
    }

    void setConnection(string s1, string s2) {
        int rowIndex = nameIndexMap->at(s1);
        int colIndex = nameIndexMap->at(s2);
        matrix->at(rowIndex).at(colIndex) = 1;
    }

    vector<vector<int>> * commonNeighborsMatrix() {
        // matrix multiply
        const int dim1 = matrix->size();     // a rows
        const int dim2 = matrix[0].size();  // a cols
        const int dim3 = matrix[0].size();  // b cols
        vector<vector<int>> * result = new vector<vector<int>>();
        vector<int> temp = vector<int>();

        for (unsigned int i = 0; i < nameIndexMap->size(); i ++) {
            temp.push_back(0);
        }
        for (unsigned int i = 0; i < nameIndexMap->size(); i ++) {
            result->push_back(temp);
        }
        for (auto itop = 0; itop < dim1; itop += 32) {
          for (auto jtop = 0; jtop < dim3; jtop += 32) {
            for (auto ktop = 0; ktop < dim2; ktop += 32) {
              for (auto i = itop; i < ((itop + 32) > dim1 ? dim1 : (itop + 32));
                   i++) {
                for (auto j = jtop; j < ((jtop + 32) > dim3 ? dim3 : (jtop + 32));
                     j++) {
                  for (auto k = ktop; k < ((ktop + 32) > dim2 ? dim2 : (ktop + 32));
                       k++) {
                    result->at(i).at(j) += matrix->at(i).at(k) * matrix->at(k).at(j);
                  }
                }
              }
            }
          }
        }
        return result;
    }

    /**
     * Print the matrix built for debugging.
     */
    void printMatrix() {
        for (unsigned int i = 0; i < matrix->size(); i ++) {
            cout << names->at(i) << " ";
            for (unsigned int j = 0; j < matrix->at(0).size(); j ++) {
                cout << matrix->at(i).at(j) << " ";
            }
            cout << endl;
        }
    }
};

#endif
