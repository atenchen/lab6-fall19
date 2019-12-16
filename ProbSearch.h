#ifndef PROB_SEARCH_H
#define PROB_SEARCH_H
class ProbSearch {
public:
        double prob;
        int steps_taken;
        ProbSearch(): prob(0.0), steps_taken(0){}
        ProbSearch& reset(){prob = steps_taken = 0; return *this;}
};
#endif
