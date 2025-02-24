//
// Created by ahmed Ibrahim on 30-Jan-25.
//

#include "UniformGreenDistributor.h"
#include "Model/PolygonLibrary/PolygonHelper.h"
#include "../../DesignGeometryManager.h"

void UniformGreenDistributor::select( Polygon1 &outerLand ,vector<Polygon1> &lands, double greenAreaPercentage) {
    int n = (int)lands.size();
    int greenAreas = n*greenAreaPercentage;
    cout<<"GREEN AREA = "<<greenAreas<<"\n";
    vector<vector<int>> landsAdj = PolygonAdjacencyAnalyzer::getAdj(lands);

    Point outerCentroid = outerLand.calculateCentroid();
    vector<Line> outerLine = outerLand.getLines();

    vector<set<int>> landsAdjSet(n);

    for (int i = 0; i < landsAdj.size(); ++i)
    {
        for(auto &adj : landsAdj[i])landsAdjSet[i].insert(adj);
    }

    vector<pair<int , int>> mapIndexToAdjCount;
    map<int , bool> isLandInBoundry;
    for (int i = 0; i < n; ++i)
    {

        bool inBoundry = false;
        double area = lands[i].getArea();

        for (int j = 0; j < lands[i].getPoints().size(); ++j)
        {
            Point a1 = lands[i].getPoints()[j];
            Point a2 = lands[i].getPoints()[(j+1) % lands[i].getPoints().size()];

            if(i == 25)
            {
                cout<< "Land 26 <<"<<a1.getX()<<","<<a1.getY()<<"\n";
            }

            for(auto &line : outerLine)
            {
                Point l1 (line.getX1() , line.getY1());
                Point l2 (line.getX2() , line.getY2());

                if(PolygonHelper::isPointOnLine(a1 , line)||PolygonHelper::isPointOnLine(a2 , line)||
                        a1 == l1 || a1 == l2 || a2 == l1 || a2 == l2)
                {
                    inBoundry = true;
                    break;
                }
            }
            if(inBoundry)break;
        }
        isLandInBoundry[i] = inBoundry;
        if(inBoundry)cout<<"outerLand = "<<i+1<<"\n";
        mapIndexToAdjCount.emplace_back(landsAdj[i].size() + (inBoundry * -area), i);
    }
    sort(mapIndexToAdjCount.begin(), mapIndexToAdjCount.end() , greater<>());

    for(auto &line : outerLine)
    {
        line.printJsonFormat();
    }

    set<int> greenAreasIndex;

    while (greenAreas--)
    {
        int index = mapIndexToAdjCount[0].second;
        greenAreasIndex.insert(index);
        cout<<"INDEX OF GREEN AREA = "<<index <<"Adj Size = "<<mapIndexToAdjCount[0].first<<"\n";
        lands[index].setDivisible(false);

        set<int> removedIndex;
        double area = lands[index].getArea();
        removedIndex.insert(index);
        // for(auto &ad : landsAdjSet[index])removedIndex.insert(ad);

        mapIndexToAdjCount.clear();
        landsAdjSet[index].clear();
        for (int i = 0; i < n; ++i)
        {
            set<int> newAdj = landsAdjSet[i];
            bool neighbourToGreenArea = false;
            for(auto &adj : landsAdjSet[i])
            {
                if (removedIndex.count(adj)){
                    newAdj.erase(adj);
                }
            }
            for(auto &adj : landsAdj[i])if(greenAreasIndex.count(adj))neighbourToGreenArea = true;
            landsAdjSet[i] = newAdj;

            if(!greenAreasIndex.count(i))mapIndexToAdjCount.emplace_back(landsAdjSet[i].size() +(neighbourToGreenArea*-area) +(isLandInBoundry[i] *-5*area), i);
        }
        sort(mapIndexToAdjCount.begin(), mapIndexToAdjCount.end() , greater<>());
    }
}
