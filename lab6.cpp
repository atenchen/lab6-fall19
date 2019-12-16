#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <vector>
#include <utility>
#include "Trie.h"
#include "Trie.h"
#include "ProbSearch.h"

using namespace std;

vector< pair<string, double> > parse(string filename){
    fstream file(filename, fstream::in);
    vector< pair<string, double> > planets;
    if(file.is_open()){
        while(!file.eof() && !file.fail()){
            string name;
            double probs;
            file >> name;
            file >> probs;
            file.ignore(1000, '\n');
            if(!name.empty()) planets.push_back(pair<string, double>(name, probs));
        }
        file.close();
    }
    return planets;
}

int main(){
    srand(unsigned(time(0)));

#ifndef TEST0
    {
        cerr << "\n\tTEST #0: Trie is empty" << endl;
        Trie t;
        //size should return the number of leaves
        assert(t.numLeaves() == 0);
        assert(t.numNodes() == 0);
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST1
    {
        cerr << "\n\tTEST #1: add elements" << endl;
        vector< pair<string, double> > planets = parse("testa.dat");
        Trie t;
        unsigned int num_leaves = 0;
        unsigned int num_nodes[] = {4, 8, 12, 18};
        int i = 0;
        for(auto p: planets){
            t.add(p);
            assert(t.numLeaves() == ++num_leaves);
            assert(t.numNodes() == num_nodes[i++]);
        }
        t.printTrie();
        cerr << "\n\t========================PASS========================\n" << endl;

    }
#endif
#ifndef TEST2
    {
        cerr << "\n\tTEST #2: add overlapping elements" << endl;
        vector< pair<string, double> > planets = parse("testb.dat");
        Trie t;
        unsigned int num_leaves = 0;
        unsigned int num_nodes[] = {4, 6, 9, 12, 15, 17, 20, 22};
        int i = 0;
        for(auto p: planets){
            t.add(p);
            assert(t.numLeaves() == ++num_leaves);
            assert(t.numNodes() == num_nodes[i++]);
        }
        t.printTrie();
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST3
    {
        cerr << "\n\tTEST #3: search Trie" << endl;
        vector< pair<string, double> > planets = parse("testb.dat");
        Trie t;
        for(auto p: planets){
            t.add(p);
        }
        ProbSearch psr;
        t.search("abc", psr.reset());
        assert(psr.prob == 1.0);
        assert(psr.steps_taken == 3);
        t.search("abd", psr.reset());
        assert(psr.prob == 2.0);
        assert(psr.steps_taken ==3);
        t.search("acd", psr.reset());
        assert(psr.prob == 3.0);
        assert(psr.steps_taken == 3);
        t.search("aaa", psr.reset());
        assert(psr.prob ==  4.0);
        assert(psr.steps_taken == 3);
        t.search("bc", psr.reset());
        assert(psr.prob ==  5.0);
        assert(psr.steps_taken == 2);
        t.search("bd", psr.reset());
        assert(psr.prob == 6.0);
        assert(psr.steps_taken == 2);
        t.search("cd", psr.reset());
        assert(psr.prob ==  7.0);
        assert(psr.steps_taken == 2);
        t.search("ca", psr.reset());
        assert(psr.prob == 8.0);
        assert(psr.steps_taken == 2);
        t.search("none", psr.reset());
        assert(psr.prob ==  -1.0);
        assert(psr.steps_taken == 0);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST4
    {
        cerr << "\n\tTEST #4: add and search with large dataset" << endl;
        vector< pair<string, double> > planets = parse("testc.dat");
        Trie t;
        unsigned int num_leaves = 0;
        for(auto p: planets){
            t.add(p);
            assert(t.numLeaves() == ++num_leaves);
        }
        ProbSearch psr;
        t.search("HAT-P-27b", psr.reset());
        assert(psr.prob == 25.97);
        assert(psr.steps_taken == 9);

        t.search("Kepler-1098b", psr.reset());
        assert(psr.prob == 43.4);
        assert(psr.steps_taken == 12);

        t.search("upsilonAndd", psr.reset());
        assert(psr.prob == 55.53);
        assert(psr.steps_taken == 11);

        t.search("K2-3b", psr.reset());
        assert(psr.prob == 22.74);
        assert(psr.steps_taken == 5);

        t.search("BD+144559b", psr.reset());
        assert(psr.prob == 73.47);
        assert(psr.steps_taken == 10);

        t.search("7CMab", psr.reset());
        assert(psr.prob == 48.04);
        assert(psr.steps_taken == 5);

        t.search("XO-3b", psr.reset());
        assert(psr.prob == 59.59);
        assert(psr.steps_taken == 5);

        t.search("CoRoT-9b", psr.reset());
        assert(psr.prob == 88.02);
        assert(psr.steps_taken == 8);

        t.search("Kepler-1049b", psr.reset());
        assert(psr.prob == 19.32);
        assert(psr.steps_taken == 12);

        t.search("HD116029b", psr.reset());
        assert(psr.prob == 35.0);
        assert(psr.steps_taken == 9);

        t.search("WASP-21b", psr.reset());
        assert(psr.prob == 72.71);
        assert(psr.steps_taken == 8);

        t.search("GJ649b", psr.reset());
        assert(psr.prob == 12.37);
        assert(psr.steps_taken == 6);

        t.search("none", psr.reset());
        assert(psr.prob == -1.0);
        assert(psr.steps_taken == 0);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST5
    {
        cerr << "\n\tTEST #5: Large data set" << endl;
        vector< pair<string, double> > planets = parse("exoplanets.dat");
        Trie t;
        for(auto p: planets) t.add(p);

        ProbSearch psr;

        t.search("HD102329b", psr.reset());
        assert(psr.prob == 23.55);
        assert(psr.steps_taken == 9);

        t.search("Kepler-1322b", psr.reset());
        assert(psr.prob == 14.62);
        assert(psr.steps_taken == 12);

        t.search("WASP-140b", psr.reset());
        assert(psr.prob == 38.32);
        assert(psr.steps_taken == 9);

        t.search("Kepler-???", psr.reset());
        assert(psr.prob == -1.0);
        assert(psr.steps_taken == 7);
        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    cerr << "\n\tTests complete! Don't forget to submit your commit hash on MyCourses and run with valgrind.\n" << endl;
}
