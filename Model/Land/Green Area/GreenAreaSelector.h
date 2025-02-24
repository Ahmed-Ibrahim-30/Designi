//
// Created by ahmed Ibrahim on 29-Jan-25.
//

#ifndef DESIGNI_GREENAREASELECTOR_H
#define DESIGNI_GREENAREASELECTOR_H
#include "Model/Polygon.h"
#include "Model/PolygonLibrary/PolygonAdjacencyAnalyzer.h"

class GreenAreaSelector {
public:
    virtual void select(Polygon1 &outerLand , vector<Polygon1> &lands , double greenAreaPercentage) = 0;
};


#endif //DESIGNI_GREENAREASELECTOR_H
