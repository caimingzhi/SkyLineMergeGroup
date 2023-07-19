//
// Created by Admin on 2023/5/22.
//
#include<mylib/calculatePrize/simulRect.h>
#include<algorithm>
#include<cmath>
#include<mylib/ModeSet.h>
#include<mylib/calculatePrize/OpenMachineFee.h>
#include "E:\code\testSkyLineInGroup\cmake-build-debug\calculatePrize\OpenMachineFee.h"
#include<mylib/calculatePrize/basePlate.h>
#include<E:\code\skyLine\cmake-build-debug\SkyLine.h>
#include <fstream>
#define HORIZONTALSPACING 12
#define VERTICALSPACING 15
#define IND_MAX_WASTE 1
#ifndef UNTITLED9_GROUPINDENT_H
#define UNTITLED9_GROUPINDENT_H
//class GroupIndent;

pair<int, int> balancePoint(  vector<Item> & myItemVector )
{
    int aa = 1000 - HORIZONTALSPACING;
    double maxRate = 0;
    int width1 = 0;
    int height1 = 0;

/*    const vector<vector<double>> PaperBackPapers
            {
                    { 392, 364 },
                    { 398, 295 },
                    { 443, 298 },
                    { 443, 398 },
                    { 545, 392 },
                    { 595, 295 },
                    { 595, 443 },
                    { 787, 364 },
                    { 787, 545 },
                    { 887, 398 },
                    { 887, 595 },
                    { 1000, 700 }
            };
    int bleed = 3;
    int levelCut = 12 + bleed * 2 ;
    int verticalCut = 15 + bleed * 2 ;

    for( auto iter = PaperBackPapers.begin(); iter != PaperBackPapers.end() ; ++iter )
    {
//        cout << " 长宽分别为：+++ " <<  (*iter)[0] - verticalCut << " " <<  (*iter)[1] - verticalCut << endl;
        SkyLinePacking skyLinePack(true, (*iter)[0] - levelCut, (*iter)[1] - verticalCut, myItemVector );
        auto thisSolution = skyLinePack.packing();
        if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
        {
            if ( maxRate < thisSolution.getRate() )
            {
                maxRate = thisSolution.getRate();
//                cout << " 利用率为： " << maxRate << endl;
                width = (*iter)[0];
//                height = skyLinePack.getLargestY();
                height = (*iter)[1];
                break;
//                cout << " the width and height are : " << width << " " << height << endl;
            }
        }
    }*/

    while( aa >= 260 )
    {
        SkyLinePacking skyLinePack(true, aa , 700 - VERTICALSPACING, myItemVector );
        auto thisSolution = skyLinePack.packing();
        if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
        {
            if ( maxRate < thisSolution.getRate() )
            {
                double width = aa ;
                double height = skyLinePack.getLargestY() + VERTICALSPACING;
                if(  myItemVector.size() == 1 )
                {
                    maxRate = thisSolution.getRate();
                    width1 = width;
                    height1 = height;
                    continue;
                }
                if ( width > height && width < 2 * height )
                {
                    maxRate = thisSolution.getRate();
                    width1 = aa;
                    height1 = skyLinePack.getLargestY() + VERTICALSPACING;
                }
                if ( height > width && height < width * 2 )
                {
                    maxRate = thisSolution.getRate();
                    width1 = aa;
                    height1 = skyLinePack.getLargestY() + VERTICALSPACING;
                }
            }
        } else
        {
            break;
        }
        aa -= 10;
    }
//        cout << "  天际线最优结果宽： " <<  width1 << " " << " 高： " <<  height1 << endl;

    SkyLinePacking skyLinePack(true, width1, height1, myItemVector );
    auto thisSolution = skyLinePack.packing();
//    cout << " the used rate is : " <<  thisSolution.getRate() << endl;
//    double theRate = thisSolution.getRate();
//    if ( width < height )
//    {
//        int a = width;
//        width = height;
//        height = a;
//    }
    pair<int, int> thisPair{ width1, height1 };
    return thisPair;
}

//bool testAreaSense(  vector<Item> & myItemVector )
//{
//    double maxRate = 0;
//    int width = 0;
//    int height = 0;
//
//    const vector<vector<double>> PaperBackPapers
//            {
//                    { 392, 364 },
//                    { 398, 295 },
//                    { 443, 298 },
//                    { 443, 398 },
//                    { 545, 392 },
//                    { 595, 295 },
//                    { 595, 443 },
//                    { 787, 364 },
//                    { 787, 545 },
//                    { 887, 398 },
//                    { 887, 595 },
//                    { 1000, 700 }
//            };
//    int bleed = 3;
//    int levelCut = 12 + bleed * 2 ;
//    int verticalCut = 15 + bleed * 2 ;
//    for( auto iter = PaperBackPapers.begin(); iter != PaperBackPapers.end() ; ++iter )
//    {
////        cout << " 长宽分别为：+++ " <<  (*iter)[0] - verticalCut << " " <<  (*iter)[1] - verticalCut << endl;
//        SkyLinePacking skyLinePack(true, (*iter)[0] - levelCut, (*iter)[1] - verticalCut, myItemVector );
//        auto thisSolution = skyLinePack.packing();
//        if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
//        {
//            if ( maxRate < thisSolution.getRate() )
//            {
//                maxRate = thisSolution.getRate();
////                cout << " 利用率为： " << maxRate << endl;
//                width = (*iter)[0];
//                height = skyLinePack.getLargestY();
//                if ( width < height * 2 )
//                {
//                    return true;
//                } else
//                {
//                    return false;
//                }
//            }
//        }
//    }
//    return false;
//
//}

bool compareRectIndent ( RectIndent &a , RectIndent & b )
{
    if ( a.getQuantity() <= b.getQuantity() )
    {
        return true;
    } else
    {
        return false;
    }
}


class MergeClass
{
public:
    double lowestSkyLine;
    bool mergeNumFlag;
    vector<vector<int>> theModeSet;
    vector<RectIndent>  thisGroupIndent;

    MergeClass( bool & mergeFlage, vector<vector<int>> & theMode, vector<RectIndent> & theGroup )
    {
        mergeNumFlag = mergeFlage;
        theModeSet = theMode;
        thisGroupIndent = theGroup;
        lowestSkyLine = 700;
    }
    void setFlag( bool & mergeFlag )
    {
        mergeNumFlag = mergeFlag;
    }
    void setModeSet( vector<vector<int>> & theMode )
    {
        if (theMode.size() == theModeSet.size() )
        {
            return;
        }
        theModeSet.clear();
        for (int i = 0; i < theMode.size(); ++i) {
            theModeSet.emplace_back( theMode[i] );
        }
    }
    void setLowestSkyline( double skyline )
    {
        lowestSkyLine = skyline;
    }
};


class GroupIndent
{
private:

    double getWidth( double totallArea )
    {
        double width = 3*(::ceil(::sqrt(totallArea/6 )));
        return width;
    }

    double getHight( double totallArea )
    {
        double hight = 2*(::ceil(::sqrt(totallArea/6 )));
        return hight;
    }
    double getGroupArea( const vector<int> & thisMode )
    {
        double totallArea = 0;
        for (int i = 0; i < groupOrderIndent.size(); ++i) {
            totallArea += thisMode[i]*groupOrderIndent[i].getArea();
        }
        return totallArea;
    }

    double getGroupArea(  )
    {
        double totallArea = 0;
        for (int i = 0; i < groupindent.size(); ++i) {
            totallArea += groupindent[i].getArea();
        }
        return totallArea;
    }

    pair<double, double> getGroupAreaBeta( const vector<int> & thisMode )
    {
//        ModeSet thisSet( indentNum.size() + 1 );
//        auto & thismodeset = thisSet.modeSet;

        vector<Item> myItemVector;
        for (int i = 0; i < thisMode.size(); ++i) {
            int theNum = thisMode[i];
            while( theNum-- )
            {
                Item thisItem(std::to_string(groupOrderIndent[i].getIndex()), groupOrderIndent[i].getWidth(), groupOrderIndent[i].getHeight());
                myItemVector.emplace_back( thisItem );
            }
        }

/*
        double width = 758;
        double hight = 700;
        double max = width;
        double min = hight;
        SkyLinePacking skyLinePack(true, width, hight, myItemVector );
        auto thisSolution = skyLinePack.packing();
        if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
        {
            min = skyLinePack.getLargestY();
            max = width;

//            std::ofstream  outw( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt");
//            std::ofstream  outh( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt");
//            std::ofstream  outx( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt");
//            std::ofstream  outy( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt");
//
//            for( auto thisW : thisSolution.getPlaceItemList() )
//            {
//                outw << thisW.getW() << endl;
//                outh << thisW.getH() << endl;
//                outx << thisW.getX() << endl;
//                outy << thisW.getY() << endl;
//
//            }
            cout << thisSolution.getRate() << endl;

            double theRate = thisSolution.getRate();
            if( theRate <= 0.7 )
            {
                cout << endl;
            }

        } else
        {
            width = 1000;
            hight = 700;
            SkyLinePacking skyLinePack(true, width, hight, myItemVector );
            auto thisSolution = skyLinePack.packing();
            min = skyLinePack.getLargestY();
            max = width;

//            std::ofstream  outw( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt");
//            std::ofstream  outh( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt");
//            std::ofstream  outx( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt");
//            std::ofstream  outy( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt");
//
//            for( auto thisW : thisSolution.getPlaceItemList() )
//            {
//                outw << thisW.getW() << endl;
//                outh << thisW.getH() << endl;
//                outx << thisW.getX() << endl;
//                outy << thisW.getY() << endl;
//
//            }
            cout << thisSolution.getRate() << endl;
        }
        pair<double, double> t1( min, max);
*/


        auto thisPair = balancePoint( myItemVector );
        double min = 0;
        double max = 0;
        if( thisPair.first > thisPair.second )
        {
            max = thisPair.first;
            min = thisPair.second;
        } else
        {
            max = thisPair.second;
            min = thisPair.first;
        }
        pair<double, double> t1( max, min );



        return t1;

    }



//    bool tryNextIndentArea( RectIndent & nextIndent )
//    {
//        double totallArea = 0;
//        for (int i = 0; i < groupindent.size(); ++i) {
//            totallArea += groupindent[i].getArea();
//        }
//        totallArea += nextIndent.getArea();
//        BasePlate thePlate;
//        if( totallArea > thePlate.maxArea )
//        {
//            return false;
//        } else
//        {
//            return true;
//        }
//
//    }
    void tryNextIndentArea( MergeClass & tmpMergeGroup )
    {
//        double lowestSkyline = 700;
        vector<vector<int>> selectMode;
        bool mergFlag = false;
        for (int i = 0; i < tmpMergeGroup.theModeSet.size(); ++i) {
            vector<Item> myItemVector;
            for (int j = 0; j < tmpMergeGroup.theModeSet[i].size(); ++j) {
                    int theNum = tmpMergeGroup.theModeSet[i][j];
                    while( theNum-- )
                    {
                        Item thisItem(std::to_string(tmpMergeGroup.thisGroupIndent[j].getIndex()), tmpMergeGroup.thisGroupIndent[j].getWidth(), tmpMergeGroup.thisGroupIndent[j].getHeight());
                        myItemVector.emplace_back( thisItem );
                    }
            }
//            mergFlag = testAreaSense( myItemVector );
//            selectMode.emplace_back( tmpMergeGroup.theModeSet[i] );

            SkyLinePacking skyLinePack(true, 1000 - HORIZONTALSPACING, 700 - VERTICALSPACING, myItemVector );
            auto thisSolution = skyLinePack.packing();
            if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
            {
                selectMode.emplace_back( tmpMergeGroup.theModeSet[i] );
//                lowestSkyline = skyLinePack.getLowestSkyLine();
                mergFlag = true;
            }
        }
        tmpMergeGroup.setFlag( mergFlag );
        tmpMergeGroup.setModeSet( selectMode );
//        tmpMergeGroup.setLowestSkyline( lowestSkyline );

    }

    MergeClass tryNextMode( RectIndent & nextIndent )
    {
        auto groupindentCopy = groupindent;
        groupindentCopy.emplace_back( nextIndent );
        std::sort(groupindentCopy.begin(), groupindentCopy.end(), compareRectIndent);
        vector<double> orderNum;
        for (int i = 0; i < groupindentCopy.size(); ++i) {
            orderNum.emplace_back( groupindentCopy[i].getQuantity()) ;
        }
        std::sort(orderNum.begin(), orderNum.end());
        ModeSetOrder thisSet01( orderNum.size() );
        auto & thismodeset = thisSet01.modeSet;
        vector<vector<int>> selectMode;
        bool mergeFlag = false;
        vector<int> choosMode( orderNum.size() );
        double totallWasteNum = INT64_MAX;
        for ( auto theMode : thismodeset ) {
            double printNum01 = 0;
            for (int i = 0; i < theMode.size(); ++i) {
                double thisPrintNum = orderNum[i] / theMode[i];
                if (thisPrintNum > printNum01) {
                    printNum01 = thisPrintNum;
                }
            }
            double thisModeWateNum = 0;
            int countNum = 0;
            for (int j = 0; j < theMode.size(); ++j) {
                thisModeWateNum += printNum01 * theMode[j] - orderNum[j];
                if( (printNum01 * theMode[j] - orderNum[j] ) < IND_MAX_WASTE )
                {
                    countNum++;
                }
                if ( countNum == orderNum.size() )
                {
                    selectMode.emplace_back( theMode );
                    mergeFlag = true;
                }
            }
        }

        MergeClass tmpMergeClass( mergeFlag, selectMode,  groupindentCopy );

        return tmpMergeClass;
    }


    bool placeNextMerge( RectIndent & nextIndent )
    {
        vector<Item> myItemVector;
//        vector<int> theIndexSeq;
        for (int i = 0; i < groupindent.size(); ++i) {
            int theNum = 1;
            while( theNum-- )
            {
                Item thisItem(std::to_string(groupindent[i].getIndex()), groupindent[i].getWidth(), groupindent[i].getHeight());
                myItemVector.emplace_back( thisItem );
            }
        }
        Item nextItem( to_string(nextIndent.getIndex()), nextIndent.getWidth(), nextIndent.getHeight() );
        myItemVector.emplace_back( nextItem );
        SkyLinePacking skyLinePack(true, 1000, 700, myItemVector );
        auto thisSolution = skyLinePack.packing();
        if( thisSolution.getPlaceItemList().size() != myItemVector.size() )
        {
            return false;
        } else
        {
            return true;
        }

    }

public:
    pair<double, double> getGroupAreaBetaplot( const vector<int> & thisMode )
    {
//        ModeSet thisSet( indentNum.size() + 1 );
//        auto & thismodeset = thisSet.modeSet;

        vector<Item> myItemVector;
        for (int i = 0; i < thisMode.size(); ++i) {
            int theNum = thisMode[i];
            while( theNum-- )
            {
                Item thisItem(std::to_string(groupOrderIndent[i].getIndex()), groupOrderIndent[i].getWidth(), groupOrderIndent[i].getHeight());
                myItemVector.emplace_back( thisItem );
            }
        }


        auto thisPair = balancePoint( myItemVector );
        pair<double, double> t1( thisPair.second, thisPair.first );


        SkyLinePacking skyLinePack(true, thisPair.first, thisPair.second, myItemVector );
        auto thisSolution = skyLinePack.packing();


        std::ofstream  outw( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt", std::ios::app);
        std::ofstream  outh( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt", std::ios::app);
        std::ofstream  outx( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt", std::ios::app);
        std::ofstream  outy( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt", std::ios::app);
        std::ofstream  outn( "E:\\code\\testSkyLineInGroup\\workFiles\\name.txt", std::ios::app);
        std::ofstream  outq( "E:\\code\\testSkyLineInGroup\\workFiles\\quantity.txt", std::ios::app);

        for( auto thisW : thisSolution.getPlaceItemList() )
        {
            outw << thisW.getW() << endl;
            outh << thisW.getH() << endl;
            outx << thisW.getX() << endl;
            outy << thisW.getY() << endl;
            outn << thisW.getName() << endl;
            int index = stoi(thisW.getName());
            int quantity = 0;
            for (int i = 0; i < this -> groupOrderIndent.size(); ++i) {
                if ( index == this -> groupOrderIndent[i].getIndex() )
                {
                    quantity = this -> groupOrderIndent[i].getQuantity() /thisMode[i];
                }
            }
            outq << quantity << endl;

        }

        outw << "-1" << endl;
        outh << "-1" << endl;
        outx << "-1" << endl;
        outy << "-1" << endl;
        outn << "-1" << endl;
        outq << "-1" << endl;

/*
        double width = 700;
        double hight = 758;
        double max = width;
        double min = hight;
        SkyLinePacking skyLinePack(true, width, hight, myItemVector );
        Solution thisSolution = skyLinePack.packing();
        if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
        {
            min = skyLinePack.getLargestY();
            max = width;
//
*/
/*            if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
            {
                std::ofstream  outw( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt");
                std::ofstream  outh( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt");
                std::ofstream  outx( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt");
                std::ofstream  outy( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt");

                for( auto thisW : thisSolution.getPlaceItemList() )
                {
                    outw << thisW.getW() << endl;
                    outh << thisW.getH() << endl;
                    outx << thisW.getX() << endl;
                    outy << thisW.getY() << endl;

                }
                cout <<  thisSolution.getPlaceItemList().size() << " " <<  myItemVector.size() << endl;
            }*//*

        } else
        {
            width = 1000;
            hight = 700;
            SkyLinePacking skyLinePack(true, width, hight, myItemVector );
            auto thisSolution = skyLinePack.packing();
            if( thisSolution.getPlaceItemList().size() != myItemVector.size() )
            {
                cout << endl << " something wrong !!! " << endl;
            }


            if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
            {
//            auto thisSolution = skyLinePack.packing();
//            cout << thisSolution.getRate() << endl;

                std::ofstream  outw( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt");
                std::ofstream  outh( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt");
                std::ofstream  outx( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt");
                std::ofstream  outy( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt");

                for( auto thisW : thisSolution.getPlaceItemList() )
                {
                    outw << thisW.getW() << endl;
                    outh << thisW.getH() << endl;
                    outx << thisW.getX() << endl;
                    outy << thisW.getY() << endl;

                }
//            cout <<  thisSolution.getPlaceItemList().size() << " " <<  myItemVector.size() << endl;
            }

            min = skyLinePack.getLargestY();
            max = width;
        }

//        SkyLinePacking skyLinePack(true, 1000, 700, myItemVector );
//        auto thisSolution = skyLinePack.packing();

//        cout << thisSolution.getRate() << endl;
//        double min = skyLinePack.getLargestY();
//        double max = 1000;
        pair<double, double> t1( min, max);*/
        return t1;
    }



public:
    vector<RectIndent> groupindent;
    vector<vector<int>> theSelectMode;
    vector<RectIndent> groupOrderIndent;
    vector<int> indentNum;
    double plateWidth;
    double plateHight;
    double groupArea;
    double groupRate;
    bool mergeFull = false;
    bool mergeLarge = false;
    bool mergeLargeSecond = false;
    bool secondLargeFlag = false;
    bool testFull()
    {
        return mergeFull;
    }
    GroupIndent( RectIndent & thisIndent )
    {
        groupindent.emplace_back( thisIndent );
        indentNum.emplace_back( thisIndent.getQuantity() );
        groupOrderIndent.emplace_back( thisIndent );
        trySky();
        if ( thisIndent.getArea() > 190000 )
        {
            mergeLarge = true;
        }
        if ( thisIndent.getArea() > 50000 )
        {
            secondLargeFlag = true;
        }
    }
    void trySky()
    {
        vector<vector<int>> tmpV;
        for (int i = 1; i < 13; ++i) {
            vector<int> thisMode(1,i);
            tmpV.emplace_back( thisMode );
        }
        for (auto thisMode : tmpV )
        {
            vector<Item> myItemVector;
            for (int i = 0; i < thisMode.size(); ++i) {
                int theNum = thisMode[i];
                while( theNum-- )
                {
                    Item thisItem(std::to_string(groupOrderIndent[i].getIndex()), groupOrderIndent[i].getWidth(), groupOrderIndent[i].getHeight());
                    myItemVector.emplace_back( thisItem );
                }
            }
            SkyLinePacking skyLinePack(true, 1000 - HORIZONTALSPACING, 700 - VERTICALSPACING, myItemVector );
            auto thisSolution = skyLinePack.packing();
            if( thisSolution.getPlaceItemList().size() == myItemVector.size() )
            {
                theSelectMode.emplace_back( thisMode );
            } else
            {
                break;
            }
         }
    }
    GroupIndent ()
    {

    }

    double getRate() const
    {
        return groupRate;
    }
    int getSize()
    {
        cout << indentNum.size() << endl;
        return indentNum.size();
    }

    int theSelectModeFull( )
    {
        int totall = 0;
        for (int i = 0; i < theSelectMode[0].size(); ++i) {
            totall += theSelectMode[0][i];
        }
        return totall;
    }

    bool merge( RectIndent & thisIndent )
    {

//        if ( thisIndent.getArea() > 190000 && mergeLargeSecond )
//        {
//            return false;
//        }
//        if( mergeLarge && thisIndent.getArea() > 50000 )
//        {
//            return false;
//        }
//

        if( groupindent.size() == 12 )
        {
            mergeFull = true;
            return false;
        }

        if( theSelectModeFull() == 12 )
        {
            mergeFull = true;
            return false;
        }


        auto tmpMergeGroup = tryNextMode( thisIndent );
        if ( tmpMergeGroup.mergeNumFlag == false )
        {
            return false;
        }
        tryNextIndentArea( tmpMergeGroup );
        if ( tmpMergeGroup.mergeNumFlag )
        {
            groupindent.emplace_back( thisIndent );
            indentNum.emplace_back(thisIndent.getQuantity() );
            setGroupOrderIndent( tmpMergeGroup );
            setGroupMode( tmpMergeGroup );
//            if ( thisIndent.getArea() > 190000 )
//            {
//                mergeLarge = true;
////                if( secondLargeFlag )
////                {
////                    mergeLargeSecond = true;
////                }
//            }

//            if ( mergeLarge && thisIndent.getArea() > 50000 )
//            {
//                mergeLargeSecond = true;
//            }

            return true;
        }
        return false;

    }

    double findSmallArea( RectIndentPool & listSample)
    {
        double tmpArea = listSample.indentPool[0].getArea();
        for( auto & thisSample : listSample.indentPool )
        {
            if( thisSample.getArea() < tmpArea )
            {
                        tmpArea = thisSample.getArea();
            }
        }
        return tmpArea;
    }

    double findSmallestEdge( RectIndentPool & listSample )
    {
        double smallEdge = listSample.indentPool[0].getSmallEdge();
        for( auto & thisSample : listSample.indentPool )
        {
            if ( thisSample.getSmallEdge() < smallEdge )
            {
                smallEdge = thisSample.getSmallEdge();
            }
        }
        return smallEdge;
    }

    void detach( double smallArea )
    {
        double originalArea = getGroupArea();
        if( ( smallArea + originalArea ) > ( 1000*700*0.7 ) )
            mergeFull = true;
    }



    std::pair<int,int> properSize( double & width, double & height , const vector<double> & cuttingSize)
    {
        double widthDif;
        double widthProper;
        double heithDif;
        double heightProper;
        for (int i = 0; i < cuttingSize.size(); ++i) {
            if ( width > cuttingSize[i] )
                continue;
            widthDif = cuttingSize[i] - width;
            widthProper = cuttingSize[i];
            break;
        }
        for (int i = 0; i < cuttingSize.size(); ++i) {
            if ( height > cuttingSize[i] )
                continue;
            heithDif = cuttingSize[i] - height;
            heightProper = cuttingSize[i];
            break;
        }
        if( widthDif > heithDif )
        {
            std::pair<double, double> result{ width, heightProper };
            return result;
        } else
        {
            std::pair<double, double> result{ widthProper, height };
            return result;
        }

    }

    bool chooseFour( double max, double min, const vector<vector<double>> thisMachin )
    {
        for( auto & thesize : thisMachin )
        {
            if( max <= thesize[0] && min >= thesize[1] )
                return true;
        }
        return false;
    }

    OpenMachineFee getFlatPrize( const vector<int> & thisMode )
    {
        double thisPrintNum = getPrintNum(thisMode );
        double losePaper = 150 + 50 * (::ceil( thisPrintNum / 1000 ) - 1 );
        thisPrintNum += losePaper;
        double totallArea = getGroupArea(thisMode );
        double height = getHight( totallArea );
        double width = getWidth( totallArea );
        double totalPaperSize = width * height * 1e-6 * thisPrintNum;
        double basePrize = 330.0;
        double abovePrize = 0.07;
        BasePlate thisbaseplate ;
        double max = properSize(width, height, thisbaseplate.cuttingPaper ).first;
        double min = properSize(width, height, thisbaseplate.cuttingPaper ).second;

        if( chooseFour(max, min, thisbaseplate.fourMachineSize) )
        {
            basePrize = 230;
            abovePrize = 0.05;
        }

        double printPrice = basePrize + abovePrize * 1000 * (::ceil( thisPrintNum / 1000 ) - 1 );
        double paperPrice = 7000 * totalPaperSize * 350 * 1e-6;
        double surfPrice =  ( (0.35 * totalPaperSize) > 250 ) ? (0.35 * totalPaperSize) : 250;
        double biePrice = (( 0.1 * thisPrintNum ) > 150) ? ( 0.1 * thisPrintNum ) : 150 ;
        double dieCutPrice = 200;

        double nianPriceTotall = 0;

        for (int i = 0; i < thisMode.size(); ++i) {
            double nianPrice = 0.07 * thisMode[i] * thisPrintNum;
            nianPriceTotall += nianPrice > 80 ? nianPrice : 80 ;
        }


        double totallPrice = printPrice + paperPrice + surfPrice + biePrice + dieCutPrice + nianPriceTotall;
//        cout << "总价： " << totallPrice << " 面积：" << max << " " << min << " 数量：" << thisPrintNum-losePaper << " 宽: " << width << " 高： " << height <<
//        " paperPrice ： " << paperPrice << " surfPrice： " << surfPrice << endl;
        OpenMachineFee thisFee( printPrice, paperPrice, surfPrice, biePrice, dieCutPrice, nianPriceTotall, totallPrice, max, min);
        return thisFee;

    }
    pair<double, vector<int>> getLowestCost(  )
    {
        ModeSet thisSet( indentNum.size() );
        auto & thismodeset = thisSet.modeSet;
        auto firstV = *(thismodeset.begin());
        OpenMachineFee thisFee = getFlatPrize( firstV );
        double theFee = thisFee.totallPrice;
        vector<int> theMode( (thismodeset.begin())->size() );

        for( auto & thisMode : thismodeset )
        {
            double tatallArea = 0;
            for (int i = 0; i < thisMode.size(); ++i) {
                tatallArea += groupindent[i].getArea()*thisMode[i];
            }
            if( tatallArea > 490000 )
            {
                continue;
            }
            OpenMachineFee otherFee = getFlatPrize( thisMode );
            if( theFee >= otherFee.totallPrice )
            {
                theFee = otherFee.totallPrice;
                for (int i = 0; i < theMode.size(); ++i) {
                    theMode[i] = thisMode[i];

                }
            }
        }
        return pair<double,vector<int>> { theFee, theMode};
    }

    // 确定模数，确定长宽
    OpenMachineFee getFlatPrizeBeta( const vector<int> & thisMode )
    {
        double thisPrintNum = getPrintNum(thisMode );
        double losePaper = 150 + 50 * (::ceil( thisPrintNum / 1000 ) - 1 );
        thisPrintNum += losePaper;
        // 需要改

//        double totallArea = getGroupArea(thisMode );
//        double height = getHight( totallArea );
//        double width = getWidth( totallArea );

        pair<double, double> thisPir = getGroupAreaBeta( thisMode );
        double width = thisPir.first;
        double height = thisPir.second;


        double totalPaperSize = width * height * 1e-6 * thisPrintNum;
        double basePrize = 330.0;
        double abovePrize = 0.07;
        BasePlate thisbaseplate ;
        double max = properSize(width, height, thisbaseplate.cuttingPaper ).first;
        double min = properSize(width, height, thisbaseplate.cuttingPaper ).second;
//        double max = width;
//        double min = height;
        if( chooseFour(max, min, thisbaseplate.fourMachineSize) )
        {
//            cout << " choose four " << endl;
            basePrize = 230;
            abovePrize = 0.05;
        }

        double printPrice = basePrize + abovePrize * 1000 * (::ceil( thisPrintNum / 1000 ) - 1 );
        double paperPrice = 7000 * totalPaperSize * 350 * 1e-6;
//        if (paperPrice == 0 )
//        {
//            paperPrice = INT64_MAX;
//        }
        double surfPrice =  ( (0.35 * totalPaperSize) > 250 ) ? (0.35 * totalPaperSize) : 250;
        double biePrice = (( 0.1 * thisPrintNum ) > 150) ? ( 0.1 * thisPrintNum ) : 150 ;
        double dieCutPrice = 200;

        double nianPriceTotall = 0;

        for (int i = 0; i < thisMode.size(); ++i) {
            double nianPrice = 0.07 * thisMode[i] * thisPrintNum;
            nianPriceTotall += nianPrice > 80 ? nianPrice : 80 ;
        }


        double totallPrice = printPrice + paperPrice + surfPrice + biePrice + dieCutPrice + nianPriceTotall;
//        cout << "总价： " << totallPrice << " 面积：" << max << " " << min << " 数量：" << thisPrintNum-losePaper << " 宽: " << width << " 高： " << height <<
//        " paperPrice ： " << paperPrice << " surfPrice： " << surfPrice << endl;
        OpenMachineFee thisFee( printPrice, paperPrice, surfPrice, biePrice, dieCutPrice, nianPriceTotall, totallPrice, max, min);
        return thisFee;

    }

    pair<double, vector<int>> getLowestCostBeta(  )
    {
//        ModeSet thisSet( indentNum.size() );
//        auto & thismodeset = thisSet.modeSet;
        auto & thismodeset = theSelectMode;
        auto firstV = *(thismodeset.begin());
        OpenMachineFee thisFee = getFlatPrizeBeta( firstV );
        double theFee = thisFee.totallPrice;
        plateWidth = thisFee.getWidth();
        plateHight = thisFee.getHeight();
        groupArea = getGroupArea(firstV);
        groupRate = groupArea/(plateHight*plateWidth);
        vector<int> theMode( (thismodeset.begin())->size(), 1);
        if( theSelectMode.size() == 1 )
        {
//            cout << theSelectMode.size() << endl;
            return pair<double, vector<int>> { theFee, *theSelectMode.begin()};
        }

        for( auto & thisMode : thismodeset )
        {
            OpenMachineFee otherFee = getFlatPrizeBeta( thisMode );
            if( theFee >= otherFee.totallPrice )
            {
                theFee = otherFee.totallPrice;
                plateWidth = otherFee.getWidth();
                plateHight = otherFee.getHeight();
                groupArea = getGroupArea(thisMode);
                groupRate = groupArea/(plateHight*plateWidth);
                for (int i = 0; i < theMode.size(); ++i) {
                    theMode[i] = thisMode[i];
                }
            }
        }
        return pair<double,vector<int>> { theFee, theMode};
    }

    double getPrintNum( const vector<int> & thisMode )
    {
        double thisPrintNum = 0;
        for (int i = 0; i < thisMode.size(); ++i) {
            int thisNum = ::ceil( groupOrderIndent[i].getQuantity() / thisMode[i] );
            if( thisNum > thisPrintNum )
                thisPrintNum = thisNum;
        }
        return thisPrintNum;
    }

    void setGroupOrderIndent( MergeClass & tmpMergeGroup )
    {
        groupOrderIndent.clear();
        for (int i = 0; i < tmpMergeGroup.thisGroupIndent.size(); ++i) {
            groupOrderIndent.emplace_back( tmpMergeGroup.thisGroupIndent[i]);
        }
    };
    void setGroupMode( MergeClass & tmpMergeGroup )
    {
        theSelectMode.clear();
        for (int i = 0; i < tmpMergeGroup.theModeSet.size(); ++i) {
            theSelectMode.emplace_back( tmpMergeGroup.theModeSet[i]);
        }
    }
};


bool compareRate(const GroupIndent & a, const GroupIndent & b) {
    return a.getRate() > b.getRate();
}
#endif //UNTITLED9_GROUPINDENT_H
