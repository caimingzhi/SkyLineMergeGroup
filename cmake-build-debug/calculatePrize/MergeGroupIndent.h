//
// Created by Admin on 2023/5/23.
//
#include<E:\\code\\testSkyLineInGroup\\cmake-build-debug\\calculatePrize\\groupIndent.h>
#include "E:\code\testSkyLineInGroup\cmake-build-debug\listMutex.h"
#include "E:\code\testSkyLineInGroup\cmake-build-debug\threadPool02.h"

#include "groupIndent.h"
#include "future"
#define IND_MAX_WASTE 1
#define IND_MAX_WASTE_OTHER 1
#ifndef UNTITLED9_MERGEGROUPINDENT_H
#define UNTITLED9_MERGEGROUPINDENT_H
class CountWaste
{
public:
    double waste;
    vector<vector<int>> thisGroup;
    vector<vector<int>> thisGroupNum;
    list<GroupIndent> allGroup;
    CountWaste( double waste, vector<vector<int>> & thisGroup, vector<vector<int>> & thisGroupNum, list<GroupIndent> allGrooup )
    {
        this -> waste = waste;
        this -> thisGroup = thisGroup;
        this -> thisGroupNum = thisGroupNum;
        this -> allGroup = allGrooup;
    }
    CountWaste(){};

    ~CountWaste(){};

};

double calculateThisGroup( GroupIndent & theGroup );
void plotfileClear()
{
    std::vector<std::ofstream> fileClear;
    fileClear.emplace_back( std::ofstream( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt", std::ios::trunc ));
    fileClear.emplace_back( std::ofstream( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt", std::ios::trunc ));
    fileClear.emplace_back( std::ofstream( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt", std::ios::trunc ));
    fileClear.emplace_back( std::ofstream( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt", std::ios::trunc ));
    fileClear.emplace_back( std::ofstream( "E:\\code\\testSkyLineInGroup\\workFiles\\name.txt", std::ios::trunc ));
    fileClear.emplace_back( std::ofstream( "E:\\code\\testSkyLineInGroup\\workFiles\\quantity.txt", std::ios::trunc ));
    for( auto & fileStream : fileClear )
    {
        if ( fileStream.is_open() )
        {
            fileStream.close();
        }
    }
    return;
}
double calcWaste( RectIndentPool & myPool , list<int> & firstGeneration )
{
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );
//    double smallestEdge = theGroup.findSmallestEdge( myPool );

    list<GroupIndent> allGroup;
    while( !firstGeneration.empty() )
    {
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
        for( ; iter != firstGeneration.end(); )
        {
            if( thisGroup.mergeFull )
            {
                break;
            }
            if( thisGroup.merge( myPool.indentPool[*iter], IND_MAX_WASTE ))
            {
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );

            } else
            {
                ++iter;
            }
        }
        iter = firstGeneration.begin();
        allGroup.push_back( thisGroup );

    }

    double allWaste = 0;
    for( auto & thisGroup : allGroup )
    {

        auto thefee = thisGroup.getLowestCost();
        allWaste += thefee.first;
    }

    return allWaste;

}
double calcWasteBeta( RectIndentPool & myPool , list<int> & firstGeneration )
//void calcWasteBeta( RectIndentPool & myPool , list<int> & firstGeneration , double & waste )
{
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );
//    double smallestEdge = theGroup.findSmallestEdge( myPool );

    list<GroupIndent> allGroup;
//    double timeTotall = 0;
    while( !firstGeneration.empty() )
    {
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
//        auto t1 = ::clock();
        for( ; iter != firstGeneration.end(); )
        {
            if( thisGroup.mergeFull )
            {
                break;
            }
//            if( thisGroup.merge( myPool.indentPool[*iter] , IND_MAX_WASTE_OTHER ))
            if( thisGroup.mergeGamma( myPool.indentPool[*iter] , IND_MAX_WASTE_OTHER ))
            {
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );

            } else
            {
                ++iter;
            }
        }
        iter = firstGeneration.begin();
        allGroup.push_back( thisGroup );
//        auto t2 = ::clock();
//        timeTotall += t2 - t1;
//        cout << " the time of merging a group is : " << t2 - t1 << endl;
//        cout << " the group size is : " <<  thisGroup.getSize() << endl;
//        auto theFee = thisGroup.getGroupAreaBetaplot( thisGroup.theSelectMode[0]);
//        cout << " ----- " << endl;
    }
//    cout << " 总时间是： " << timeTotall << endl;

    double allWaste = 0;
    for( auto & thisGroup : allGroup )
    {
//        cout << ii++ << endl;
        auto thefee = thisGroup.getLowestCostBeta();
//        cout << thefee.first << endl;
        allWaste += thefee.first;
    }

    return allWaste;
//    waste = allWaste;
}
void calcWasteGamma( RectIndentPool & myPool , list<int> & firstGeneration , vector<double> & thisIndividualWaste , int i )
{
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );
//    double smallestEdge = theGroup.findSmallestEdge( myPool );

    list<GroupIndent> allGroup;
//    auto t001 = ::clock();
    while( !firstGeneration.empty() )
    {
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
        for( ; iter != firstGeneration.end(); )
        {
            if( thisGroup.mergeFull )
            {
                break;
            }
            if( thisGroup.merge( myPool.indentPool[*iter], IND_MAX_WASTE))
            {
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );
            } else
            {
                ++iter;
            }
        }
        iter = firstGeneration.begin();
        allGroup.push_back( thisGroup );

    }
//    auto t002 = ::clock();
//    cout << " the running time required to merge group is : " << t002 - t001 << endl;

    double allWaste = 0;
//    auto t1 = ::clock();
    for( auto & thisGroup : allGroup )
    {
        auto thefee = thisGroup.getLowestCostBeta();
        allWaste += thefee.first;
    }
//    auto t2 = ::clock();
//    cout << " the running time required to calculate the waste is : " << t2 - t1 << endl;

    thisIndividualWaste[i] = allWaste;

}
double calcWasteDelta( RectIndentPool & myPool, list<int> & firstGeneration , ThreadPool * threadPool )
{
    List numberlist;
    for( auto & thisF : firstGeneration )
    {
        numberlist.push_back( thisF );
    }
    firstGeneration.clear();
    listMutix<GroupIndent> allGroup;
    auto iter = numberlist.begin();
    int threadNum = 5;
    std::vector<std::future<void>> theFutureVoid( threadPool -> getThreadNum() );
    for (int i = 0; i < theFutureVoid.size(); ++i) {
        theFutureVoid[i] = threadPool -> submit(mergeG, std::ref(allGroup), std::ref( numberlist) , std::ref( myPool));
    }
    for (int i = 0; i < theFutureVoid.size(); ++i) {
        theFutureVoid[i].get();
    }


//    std::vector<std::thread> threads;
//    for (int i = 0; i < 5; ++i) {
//        threads.push_back( std::thread(mergeG, std::ref(allGroup), std::ref( numberlist) , std::ref( myPool)) );
//    }
//    for( auto & thisThread : threads )
//    {
//        thisThread.join();
//    }


    double allWaste = 0;
//    vector<int> theM;

    std::vector<std::future<double>> theF;

    for( auto & thisGroup : allGroup.allgroup )
    {
        auto thef =  threadPool -> submit(calculateThisGroup, std::ref( thisGroup) );
        theF.emplace_back(move(thef));
    }
    for( auto & thefuture : theF )
    {
        allWaste += thefuture.get();
    }




//    for( auto & thisGroup : allGroup.allgroup )
//    {
//
//        auto thefee = thisGroup.getLowestCostBeta();
//        allWaste += thefee.first;
//    }

    return allWaste;

}

double calcWasteDeltaPrint( RectIndentPool & myPool, list<int> & firstGeneration  )
{
    List numberlist;
    for( auto & thisF : firstGeneration )
    {
        numberlist.push_back( thisF );
    }
    listMutix<GroupIndent> allGroup;
//    auto iter = numberlist.begin();
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.push_back( std::thread(mergeG, std::ref(allGroup), std::ref( numberlist) , std::ref( myPool)) );
    }
    for( auto & thisThread : threads )
    {
        thisThread.join();
    }


    double allWaste = 0;
//    vector<int> theM;
    int ii = 0;
    for( auto & thisGroup : allGroup.allgroup )
    {

        auto thefee = thisGroup.getLowestCostBeta();
        allWaste += thefee.first;
        cout << " 第 " << ii++ << "组的数量和模数信息为：" << endl;
        for ( auto thisI : thisGroup.groupOrderIndent ) {
            cout << thisI.getQuantity() << " ";
        }
        cout << endl;
        for( auto thisM : thefee.second )
        {
            cout << thisM << " " ;
        }
        cout << endl;
    }
//    cout << " hello " << endl;

    return allWaste;
//    mergeG( allGroup, numberlist , myPool);


}

double calculateThisGroup( GroupIndent & theGroup )
{
    auto theFee = theGroup.getLowestCostBeta();
    return theFee.first;
}

pair<double, vector<vector<int>>> calcWaste1( RectIndentPool & myPool , list<int> & firstGeneration )
{
    vector<vector<int>> generatGroup;
    vector<vector<int>> generatGroupNum;
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );
//    double smallestEdge = theGroup.findSmallestEdge( myPool );

    list<GroupIndent> allGroup;
    while( !firstGeneration.empty() )
    {
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
        for( ; iter != firstGeneration.end(); )
        {
            if( thisGroup.mergeFull )
            {
                break;
            }
            if( thisGroup.merge( myPool.indentPool[*iter], IND_MAX_WASTE))
            {
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );

            } else
            {
                ++iter;
            }
        }
        iter = firstGeneration.begin();
        allGroup.push_back( thisGroup );

    }

    double allWaste = 0;
    for( auto & thisGroup : allGroup )
    {
        auto thefee = thisGroup.getLowestCost();
        allWaste += thefee.first;
        generatGroup.emplace_back( thefee.second );
        generatGroupNum.emplace_back( thisGroup.indentNum );
    }

    pair<double, vector<vector<int>>> wasteMessage( allWaste, generatGroup );
    return  wasteMessage;

}

CountWaste calcWaste2( RectIndentPool & myPool , list<int> & firstGeneration )
{
    vector<vector<int>> generatGroup;
    vector<vector<int>> generatGroupNum;
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );
//    auto t1 = ::clock();
//    double smallestEdge = theGroup.findSmallestEdge( myPool );
//    auto t2 = ::clock();
//    cout << " finding time is : " << t2 - t1 << endl;
//    double smallestEdge = 0;
    list<GroupIndent> allGroup;
    plotfileClear();
    int index = 0;
    while( !firstGeneration.empty() )
    {
        auto t1 = ::clock();
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
        int ii = 1;
        for( ; iter != firstGeneration.end(); )
        {
//            cout << " 序号为： " <<  myPool.indentPool[*iter].getIndex() << endl;
            if( thisGroup.mergeFull )
            {
                break;
            }
//            if( thisGroup.merge( myPool.indentPool[*iter], IND_MAX_WASTE))
            if( thisGroup.mergeGamma( myPool.indentPool[*iter], IND_MAX_WASTE))
            {
                ii++;
//                cout << " 第 " << ii << "个数加入分组中！" << endl;
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );

            } else
            {
                ++iter;
            }
        }
        index++;
//        cout << " 这是第 " << index << " 组！！" << endl;
        iter = firstGeneration.begin();
//        allGroup.push_back( thisGroup );
        allGroup.emplace_back( thisGroup );
        auto  t2 = ::clock();
//        cout << " the time of merging a group is : " << t2 - t1 << endl;
//        cout << " the group size is : " <<  thisGroup.getSize() << endl;
//        auto thefee = thisGroup.getLowestCostBeta();
//        auto theFee = thisGroup.getGroupAreaBetaplot( thefee.second );
//        cout << " ----- " << endl;

    }

    double allWaste = 0;
    int index01 = 0;
    plotfileClear();
    for( auto & thisGroup : allGroup )
    {
        index01++;
        auto thefee = thisGroup.getLowestCostBeta();
        auto theFee = thisGroup.getGroupAreaBetaplot( thefee.second );
        allWaste += thefee.first;
        generatGroup.emplace_back( thefee.second );
        vector<int> theNumSequence;
        for (int i = 0; i < thisGroup.groupOrderIndent.size(); ++i) {
            theNumSequence.emplace_back(thisGroup.groupOrderIndent[i].getQuantity());
        }
        generatGroupNum.emplace_back( theNumSequence );
    }

    CountWaste thisCountWaste( allWaste, generatGroup, generatGroupNum , allGroup);

    return  thisCountWaste;

}

CountWaste calcWaste3( RectIndentPool & myPool , list<int> & firstGeneration )
{
    vector<vector<int>> generatGroup;
    vector<vector<int>> generatGroupNum;
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );
//    auto t1 = ::clock();
//    double smallestEdge = theGroup.findSmallestEdge( myPool );
//    auto t2 = ::clock();
//    cout << " finding time is : " << t2 - t1 << endl;
//    double smallestEdge = 0;
    list<GroupIndent> allGroup;
//    plotfileClear();
    int index = 0;
    while( !firstGeneration.empty() )
    {
        auto t1 = ::clock();
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
        int ii = 1;
        for( ; iter != firstGeneration.end(); )
        {

//            cout << " 序号为： " <<  myPool.indentPool[*iter].getIndex() + 1 << endl;
//            if ( myPool.indentPool[*iter].getIndex() == 194 )
//                cout << " index 194 " << endl;
            if( thisGroup.mergeFull )
            {
                break;
            }
//            if( thisGroup.merge( myPool.indentPool[*iter], IND_MAX_WASTE))
            if( thisGroup.mergeGamma( myPool.indentPool[*iter], IND_MAX_WASTE))
            {
                ii++;
//                cout << " 第 " << ii << "个数加入分组中！" << endl;
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );

            } else
            {
                ++iter;
            }
        }
        index++;
//        cout << " 这是第 " << index << " 组！！" << endl;
        iter = firstGeneration.begin();
//        allGroup.push_back( thisGroup );
        allGroup.emplace_back( thisGroup );
//        auto  t2 = ::clock();

//        cout << " the time of merging a group is : " << t2 - t1 << endl;
//        cout << " the group size is : " <<  thisGroup.getSize() << endl;
        auto thefee = thisGroup.getLowestCostBeta();
//        auto theFee = thisGroup.getGroupAreaBetaplot( thefee.second );
//        cout << " ----- " << endl;

    }

    double allWaste = 0;
    int index01 = 0;
//    std::ofstream  outW( "E:\\code\\testSkyLineInGroup\\workFiles\\waste.csv", std::ios::app);

    for( auto & thisGroup : allGroup )
    {
        index01++;
        auto thefee = thisGroup.getLowestCostBeta();
//        outW << thefee.first << "," << 1 << endl;
//        cout << "第" << index01 << "组成本：" << thefee.first << " ";
        allWaste += thefee.first;
        generatGroup.emplace_back( thefee.second );
        vector<int> theNumSequence;
        for (int i = 0; i < thisGroup.groupOrderIndent.size(); ++i) {
            theNumSequence.emplace_back(thisGroup.groupOrderIndent[i].getQuantity());
        }
        generatGroupNum.emplace_back( theNumSequence );
    }

    CountWaste thisCountWaste( allWaste, generatGroup, generatGroupNum , allGroup);
    return  thisCountWaste;

}

CountWaste calcWasteTryOtherWay( RectIndentPool & myPool , list<int> & firstGeneration )
//double calcWasteTryOtherWay( RectIndentPool & myPool , list<int> & firstGeneration )
{
    vector<vector<int>> generatGroup;
    vector<vector<int>> generatGroupNum;
    auto iter = firstGeneration.begin() ;
    GroupIndent theGroup( myPool.indentPool.front());
    double smallestArea = theGroup.findSmallArea( myPool );

    //合成包含较大的组
//    list<GroupIndent> * allGroup = new list<GroupIndent>();
    list<GroupIndent> allGroup;
    unique_ptr<vector<GroupIndent>> largeGroup = make_unique<vector<GroupIndent>>( );
    plotfileClear();
    int ii = 0;
    while( iter != firstGeneration.end() )
    {
        ii++;
        cout << " the time of " << ii << endl;
        if ( myPool.indentPool[*iter].getHeight() * myPool.indentPool[*iter].getWidth() > 175000 )
        {
            GroupIndent thisGroup( myPool.indentPool[*iter]);
            largeGroup ->emplace_back( thisGroup );
            iter = firstGeneration.erase( iter );
        } else
        {
            iter++;
        }
    }
    int index = 0;

    iter = firstGeneration.begin();
    for (int i = 0; i < largeGroup->size(); ++i) {
        GroupIndent thisGroup( largeGroup -> at( i ) );
        auto t1 = ::clock();
        while( iter != firstGeneration.end() )
        {
            if ( thisGroup.mergeFull )
            {
                break;
            }
            if ( thisGroup.merge( myPool.indentPool[*iter], 0 ))
            {
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );
            } else
            {
                ++iter;
            }
        }
        index++;
        auto t2 = ::clock();
        cout << " 这是第 " << index << " 组！！" << endl;
        cout << " the time of merging a group is : " << t2 - t1 << endl;
        cout << " the group size is : " <<  thisGroup.getSize() << endl;
        iter = firstGeneration.begin();
        allGroup.emplace_back( thisGroup );
        auto thefee = thisGroup.getLowestCostBeta();
        auto theFee = thisGroup.getGroupAreaBetaplot( thefee.second );

    }


    while( !firstGeneration.empty() )
    {
        auto t1 = ::clock();
        GroupIndent thisGroup( myPool.indentPool[*iter]);
        iter = firstGeneration.erase(iter);
        int ii = 1;
        for( ; iter != firstGeneration.end(); )
        {
//            cout << " 序号为： " <<  myPool.indentPool[*iter].getIndex() << endl;
            if( thisGroup.mergeFull )
            {
                break;
            }
            if( thisGroup.merge( myPool.indentPool[*iter], IND_MAX_WASTE))
            {
                ii++;
//                cout << " 第 " << ii << "个数加入分组中！" << endl;
                iter = firstGeneration.erase( iter );
                thisGroup.detach( smallestArea );

            } else
            {
                ++iter;
            }
        }
        index++;
        cout << " 这是第 " << index << " 组！！" << endl;
        iter = firstGeneration.begin();
//        allGroup.push_back( thisGroup );
        allGroup.emplace_back( thisGroup );
        auto  t2 = ::clock();
        cout << " the time of merging a group is : " << t2 - t1 << endl;
        cout << " the group size is : " <<  thisGroup.getSize() << endl;
        auto thefee = thisGroup.getLowestCostBeta();
        auto theFee = thisGroup.getGroupAreaBetaplot( thefee.second );
//        cout << " ----- " << endl;

    }

    double allWaste = 0;
    int index01 = 0;
    std::ofstream  outW( "E:\\code\\testSkyLineInGroup\\workFiles\\waste.csv", std::ios::app);

    for( auto & thisGroup : allGroup )
    {
        index01++;

        auto thefee = thisGroup.getLowestCostBeta();
        allWaste += thefee.first;
        outW << thefee.first << "," << 1 << endl;
        generatGroup.emplace_back( thefee.second );
        vector<int> theNumSequence;
        for (int i = 0; i < thisGroup.groupOrderIndent.size(); ++i) {
            theNumSequence.emplace_back(thisGroup.groupOrderIndent[i].getQuantity());
        }
        generatGroupNum.emplace_back( theNumSequence );
    }

    CountWaste thisCountWaste( allWaste, generatGroup, generatGroupNum , allGroup);

//    return  allWaste;
    return  thisCountWaste;

}




#endif //UNTITLED9_MERGEGROUPINDENT_H
