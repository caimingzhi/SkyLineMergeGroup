//
// Created by Admin on 2023/5/22.
//

#include <mylib/calculatePrize/SimulateBeta.h>
#ifndef UNTITLED9_SIMULRECT_H
#define UNTITLED9_SIMULRECT_H
#include<vector>
#include<list>
#define BLEED 3
using namespace std;
class RectIndent
{
private:
    double height;
    double width;
    double area;
    double quantity;
    int indentIndex;
public:
    RectIndent( double height, double width, double quantity, int indentIndex )
    {
        this->height = height;
        this->width = width;
        this->area = width * height;
        this->quantity = quantity;
        this->indentIndex = indentIndex;
    }

    double getHeight( )
    {
        return height;
    }

    double getWidth( )
    {
        return width;
    }

    double getArea( )
    {
        return area;
    }
    double getQuantity( )
    {
        return quantity;
    }
    int getIndex( )
    {
        return  indentIndex;
    }

};

class RectIndentPool
{
public:
    vector<RectIndent> indentPool;
    RectIndentPool(){};
    RectIndentPool( int poolSize , int seed = 0 )
    {
        vector<double> sampleheigth( poolSize, 0);
        vector<double> sampleWith( poolSize,0);
        vector<double> sampleArea( poolSize, 0);
        vector<double> sampleQuantity( poolSize, 0);

        randSbeta( sampleheigth, poolSize, seed );
        otherSideBeta( sampleheigth, sampleWith, seed );
        quantitySet( sampleQuantity , seed );
        areaCount( sampleWith, sampleheigth, sampleArea);

        for (int i = 0; i < poolSize; ++i) {
            RectIndent thisIndent( sampleheigth[i], sampleWith[i], sampleQuantity[i], i);
            indentPool.emplace_back( thisIndent );
        }


    }

    RectIndentPool( vector<vector<int>> & poList )
    {
        int poolSize = poList.size();
        for (int i = 0; i < poolSize; ++i) {
            RectIndent thisIndent( poList[i].at(2) + BLEED, poList[i].at(1) + BLEED, poList[i].at(0), i);
            indentPool.emplace_back( thisIndent );
        }
    }



};





#endif //UNTITLED9_SIMULRECT_H
