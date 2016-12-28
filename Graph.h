/**
 * Amos Maimon And Or Zipori.
 */

#ifndef EX1_GRAPH_H
#define EX1_GRAPH_H

/**
 * Graph Class.
 *
 * Absract representaion of any graph.
 */

#include "Key.h"
#include <queue>

class Graph {
    virtual std::queue<Key>& getBrothers(Key &current) =0;
    virtual void setDistance(const Key &location, int distance)=0;
    virtual int getDistance(const Key &location)=0;
    virtual void setNextStep(const Key &location, const Key &nextStep)=0;
    virtual Key& getNextStep(const Key &location)=0;
};


#endif //EX1_GRAPH_H
