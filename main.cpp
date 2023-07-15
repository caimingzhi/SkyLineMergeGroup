#include<iostream>
#include<vector>
#include<list>
#include<E:\\code\\testSkyLineInGroup\\cmake-build-debug\\calculatePrize\\groupIndent.h>
#include<D:\\workSoftware\\worktools\\clion\\CLion 2022.3.2\\bin\\mingw\\include\\mylib\\ModeSet.h>
#include<E:\\code\\testSkyLineInGroup\\cmake-build-debug\\calculatePrize\\MergeGroupIndent.h>

#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "E:\code\testSkyLineInGroup\cmake-build-debug\threadPool02.h"
#include "E:\code\testSkyLineInGroup\cmake-build-debug\getRealData.h"
//#include <E:\code\testSkyLineInGroup\cmake-build-debug\skyLine.h>
#include <E:\code\skyLine\cmake-build-debug\SkyLine.h>
#include <fstream>
//#include <E:\code\testSkyLineInGroup\cmake-build-debug\ctlp.h>
//#include <E:\code\testSkyLineInGroup\cmake-build-debug\threadPool.h>
//#include<E:\code\testSkyLineInGroup\cmake-build-debug\calculatePrize\simulRect.h>
using  namespace std;
void calcuParallel( ThreadPool & pool,  void(  *calcWasteGamma )( RectIndentPool &, list<int> & , vector<double>& , int) ,
RectIndentPool & myPool, vector<list<int>> & individualGroup, vector<double>& wasteP , int individualSize )
{
    for (int i = 0; i < (individualSize); ++i) {
        pool.submit(calcWasteGamma, std::ref( myPool ), std::ref( individualGroup[i] ) , std::ref(wasteP), i);
    }
    pool.waitAll( wasteP );
//    cout << " hello " << endl;

}

void getList( vector<list<int>> & thisList )
{
    vector<int> theV;
    for (int i = 0; i < thisList.size(); ++i) {
        theV.emplace_back( i );
    }

    random_device rd;
    mt19937 gen( rd() );

    for (int i = 0; i < thisList.size(); ++i) {
        std::shuffle( theV.begin(), theV.end(), gen );
        for (int j = 0; j < theV.size(); ++j) {
            thisList[j].emplace_back( theV[i] );
        }
    }

}




int main() {
//    int totall1 = 0;
//    int totall = 0;
//    for (int i = 2; i < 12 ; ++i) {
//        ModeSetOrder thisSet(i );
//        totall1 += thisSet.modeSet.size();
//        ModeSet thisSet1(7 );
//        totall += thisSet1.modeSet.size();
//    }

//    cout << totall << endl;
//    cout << totall1 << endl;
//    cout << static_cast<double > (totall/totall1) << endl;
    int baseSize = 1000 ;
    const int individualSize = 50;
    int seed = 1235;
    vector<list<int>> individualGroup( individualSize );


    vector<vector<int>> individualVector;

    getFirstGeneration( individualGroup, individualVector, baseSize, seed );
//    RectIndentPool myPool = data();
//    RectIndentPool myPool( baseSize , seed );
    string filePath = "D:\\workFile\\data_test\\data_output1.csv";
    auto  mySample = getSimulateData( filePath, baseSize);
    RectIndentPool myPool( mySample );

    vector<int> countNum( 21 );
    int ii = 0;
    for (int i = 0; i < myPool.indentPool.size(); ++i) {
        int area =( myPool.indentPool[i].getWidth())*(myPool.indentPool[i].getHeight());
        if ( area > 175000 )
        {
            ii++;
            cout << myPool.indentPool[i].getHeight() << " " <<  myPool.indentPool[i].getWidth() << endl;
        }
//        if ( numCount < 10 )
//        {
//            cout << myPool.indentPool[i].getHeight() << " " << myPool.indentPool[i].getWidth() << endl;
//        }
//        countNum[numCount]++;
    }
    cout << " 面积大于175000的个数为： " << ii << endl;
    cout << " Hello " << endl;
/*
//    myPool.indentPool[1].getWidth();
//    myPool.indentPool[1].getHeight();
//    vector<Item> myItemVector;
//    for (int i = 0; i < myPool.indentPool.size(); ++i) {
//        myItemVector.emplace_back( Item(to_string( i ), myPool.indentPool[i].getWidth(), myPool.indentPool[i].getHeight() ) );
//    }
//    SkyLinePacking skyLinePack(true, 1000, 700, myItemVector);
//    Solution thisSolution = skyLinePack.packing();
//
//    cout << endl;
//    std::ofstream  outw( "E:\\code\\testSkyLineInGroup\\workFiles\\width.txt");
//    std::ofstream  outh( "E:\\code\\testSkyLineInGroup\\workFiles\\height.txt");
//    std::ofstream  outx( "E:\\code\\testSkyLineInGroup\\workFiles\\x.txt");
//    std::ofstream  outy( "E:\\code\\testSkyLineInGroup\\workFiles\\y.txt");
//
//    for( auto thisW : thisSolution.getPlaceItemList() )
//    {
//        outw << thisW.getW() << endl;
//        outh << thisW.getH() << endl;
//        outx << thisW.getX() << endl;
//        outy << thisW.getY() << endl;
//
//    }
    cout << thisSolution.getRate() << endl;

     */

    auto tt01 = ::clock();
//    auto allMessage = calcWaste3( myPool, individualGroup[1] );

//

    auto allMessage = calcWasteTryOtherWay( myPool, individualGroup[1] );
    cout << " 指针所指对象的大小为： " << sizeof( *allMessage.allGroup ) << endl;
    cout << " 指针的大小为： " << sizeof( allMessage.allGroup ) << endl;
    double allWaste = allMessage.waste;

    auto thisGroup = allMessage.thisGroup;
    for (int i = 0; i < thisGroup.size(); ++i) {
        cout << " 第" << i + 1 << " 组为：" << endl;
        for( auto thisG : thisGroup[i] )
        {
            cout << thisG << " ";
        }
        cout << endl;
    }
    cout << endl;
    auto thisGroupNum = allMessage.thisGroupNum;
    for (int i = 0; i < thisGroupNum.size(); ++i) {
        cout << " 第" << i +1 << " 组为：" << endl;
        for( auto thisG : thisGroupNum[i] )
        {
            cout << thisG << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << allWaste << endl;
//    cout << " 分组个数为 ： " << count << endl;
    auto tt02 = ::clock();
    cout << " the totall running time is : " << static_cast<double>  ( tt02 - tt01 ) / CLOCKS_PER_SEC << endl;
    cout << " the totall running time is : " <<  ( tt02 - tt01 )  << endl;



/*    int minRate =  calcWaste2( myPool, individualGroup[0] ).waste;
    for (int i = 1; i < individualSize; ++i) {
        auto allMessage = calcWaste2( myPool, individualGroup[i] );
        if ( minRate > allMessage.waste )
        {
            minRate = allMessage.waste;
            cout << "Holaholooooooooooo!!!!!" << endl;
            cout << " in the time of  " << i << ", the lesser waste is : " << minRate << endl;
        }
        int waste = allMessage.waste;
        cout << waste << endl;
    }*/




//
//    ThreadPool pool( 10 );
//    pool.init();
//
//    auto t1 = ::clock();
//    std::vector<std::future<double>> wasteP1( individualSize );
//    std::vector<double> wasteP( individualSize );
//    for (int i = 0; i < individualSize; ++i) {
//        wasteP1[i] = pool.submit(calcWasteBeta, std::ref(myPool), std::ref(individualGroup[i]) );
////        wasteP1[i] = pool.submit(calcWasteBeta, std::ref(myPool), std::ref(individualGroup[i]) );
//    }
//    for (int i = 0; i < individualSize; ++i) {
//         wasteP[i]= wasteP1[i].get();
//    }
//
//    for_each( wasteP.begin(), wasteP.end(), []( int a ) { cout << a << " "; } );
//    auto t2 = ::clock();
//    cout << endl << " the runing time of parent is  " <<  static_cast<double> ( t2 - t1 ) / CLOCKS_PER_SEC  << " seconds. " << endl;
//

    //    pool.shutdown();


//    cout << endl;
//    auto t1=clock();
//    int numThread = 5;
//    cout << " the number of thread is : " << numThread << endl;
//    ThreadPool pool( numThread );
//    pool.init();
//    ThreadPool poolList( 50 );
//    poolList.init();
//    ThreadPool * thisPool = & poolList;
////    cout << endl << " the thread id in the main funtion is : " << this_thread::get_id() << endl;
////    double * p = new double[ individualSize ];
//    auto t3 = ::clock();
////    calcuParallel( pool, calcWasteGamma, myPool, individualGroup, wasteP, individualSize );
//    std::vector<std::future<double>> wasteP1( individualSize );
//    std::vector<double> wasteP( individualSize );
//    for (int i = 0; i < individualSize; ++i) {
//        wasteP1[i] = pool.submit(calcWasteDelta, std::ref(myPool), std::ref(individualGroup[i]), std::ref( thisPool) );
//    }
//    for (int i = 0; i < individualSize; ++i) {
//        wasteP[i]= wasteP1[i].get();
//    }

//    auto t4 = ::clock();
//    cout << endl << " the runing time of parent is  " <<  static_cast<double> ( t4 - t3 ) / CLOCKS_PER_SEC  << " seconds. " << endl;
//    for_each( wasteP.begin(), wasteP.end(), []( int a ) { cout << a << " "; } );
//
//    pool.shutdown();
//    thisPool-> shutdown();
//



/*

    vector<double> cumPro = cum_probability( wasteP );
    vector<vector<int>> sonVector;
    auto timebegin = ::clock();
    while (sonVector.size() < individualSize )
    {
        vector<int> parentId = chooseParent( cumPro );
        if( parentId[0] == parentId[1] )
        {
            continue;
        }
        vector<int> son1 = crossOver( parentId[0], parentId[1], individualVector );
        variation(son1);
        sonVector.emplace_back( son1 );
    }
    auto timeend = ::clock();
    cout << " the running time required to produce children is : " << timeend - timebegin << endl;
    vector<list<int>> sonGroup( sonVector.size());
    vectorTolist(  sonGroup, sonVector );
    auto t31 = ::clock();
    vector<double> wasteS(individualSize);
//    calcuParallel( pool, calcWasteGamma, myPool, sonGroup, wasteS, individualSize );
//    calcuParallel( pool, calcWasteDelta, myPool, sonGroup, wasteS, individualSize );

    for (int i = 0; i < individualSize; ++i) {
        wasteP1[i] = pool.submit(calcWasteBeta, std::ref(myPool), std::ref(sonGroup[i]) );
    }
    for (int i = 0; i < individualSize; ++i) {
        wasteS[i]= wasteP1[i].get();
    }

    auto t41 = ::clock();
    cout << endl << " the runing time of son is  " <<  static_cast<double> ( t41 - t31 ) / CLOCKS_PER_SEC  << " seconds. " << endl;
    for_each( wasteS.begin(), wasteS.end(), []( int a ) { cout << a << " "; } );

    vector<list<int>> parentGroup( individualVector.size() );
    vectorTolist( parentGroup, individualVector );
    vectorTolist(  sonGroup, sonVector );

    vector<vector<list<int>>> population;
    vector<vector<double>> waste;
    population.emplace_back( parentGroup );
    population.emplace_back( sonGroup );
    waste.emplace_back( wasteP );
    waste.emplace_back( wasteS );
    int parentIndex = 0;
    int sonIndex = 1;
    int step = 20 ;
////    cout << "hello" << endl;
    while( step-- )
    {
        cout << endl << step << endl;
        vector<list<int>> nextGeneration;
        vector<double> nextGenerationWaste;
        topRankIndividual( nextGeneration, population[parentIndex], population[sonIndex], nextGenerationWaste, waste[parentIndex], waste[sonIndex], individualSize );
        vector<double> cumPro = cum_probability( nextGenerationWaste );
//        printAverage( nextGenerationWaste );

        for_each( nextGenerationWaste.begin(), nextGenerationWaste.end(), []( int a ) { cout << a << " ";});
        cout << endl << " 第" << step << "代最小为 ： "  << static_cast<int> ( *std::min_element(nextGenerationWaste.begin(), nextGenerationWaste.end()) ) << endl;


        for_each( nextGenerationWaste.begin(), nextGenerationWaste.end(), []( int a ) { cout << a << " ";});
        cout << endl;

        vector<vector<int>> nextParentVector(individualSize);
        listToVector( nextGeneration, nextParentVector);
        vector<vector<int>> sonVector;
        int sonSize = 0;
        while ( sonSize < individualSize )
        {
            vector<int> parentId = chooseParent( cumPro );
            if( parentId[0] == parentId[1] )
            {
                continue;
            }
            vector<int> son1 = crossOver( parentId[0], parentId[1], nextParentVector );
//            cout << son1.size() << endl;
            variation(son1);
            sonVector.emplace_back( son1 );
            sonSize++;
        }

        vector<list<int>> sonGroup( sonVector.size());
        vectorTolist(  sonGroup, sonVector );
        vector<double> wasteS( individualSize );
        calcuParallel( pool, calcWasteGamma, myPool, sonGroup, wasteS, individualSize );
//        calcuParallel( pool, calcWasteDelta, myPool, sonGroup, wasteS, individualSize );
//        for (int i = 0; i < individualSize; ++i) {
////            cout << i << "....." ;
//            wasteP1[i] = pool.submit(calcWasteBeta, std::ref(myPool), std::ref(sonGroup[i]) );
//        }
//        cout << endl;
//        for (int i = 0; i < individualSize; ++i) {
////            cout << i << "    " ;
//            wasteS[i]= wasteP1[i].get();
//        }
//        cout << endl;
//        for( auto & thisSon : sonGroup )
//        {
//            double allWaste = calcWasteBeta( myPool, thisSon ) ;
//            wasteS.emplace_back( allWaste );
//        }


        vector<list<int>> parentGroup( nextParentVector.size() );
        vectorTolist( parentGroup, nextParentVector );
        vectorTolist(  sonGroup, sonVector );
        population.emplace_back( parentGroup );
        waste.emplace_back( nextGenerationWaste );
        population.emplace_back( sonGroup );
        waste.emplace_back( wasteS );
        parentIndex += 2 ;
        sonIndex  += 2;
        if( population.size() > 12 && waste.size() > 12 )
        {
            population.erase(population.begin(), population.begin()+12 );
            waste.erase(waste.begin(), waste.begin() + 12 );
            parentIndex = 0;
            sonIndex = 1;
        }


        if( step == 0 )
        {
            auto minElement = std::min_element( nextGenerationWaste.begin(), nextGenerationWaste.end() );
            int minIndex = std::distance(nextGenerationWaste.begin(), minElement );


            std::sort(nextGenerationWaste.begin(), nextGenerationWaste.end());
            cout << nextGenerationWaste.front() << endl;
            double aa = nextGenerationWaste.front();
            int index = 0;
            for (int i = 0; i < nextGenerationWaste.size(); ++i) {
                if ( aa == waste.back()[i] )
                    index = i;
            }
            list<int> thisP = parentGroup[minIndex];
            for_each( thisP.begin(), thisP.end(), [ ]( int a) { cout << a << " ";});
            cout << endl;
            for ( auto & thes : thisP ) {
                cout << myPool.indentPool[thes].getQuantity() << " ";
            }
            cout << endl;
//            auto allMessage = calcWasteDeltaPrint( myPool, thisP );
//            cout << allMessage << endl;
//            auto allMessage = calcWaste2( myPool, thisP );
            auto allMessage = calcWaste3( myPool, thisP );

            double allWaste = allMessage.waste;

            auto thisGroup = allMessage.thisGroup;
            for (int i = 0; i < thisGroup.size(); ++i) {
                for( auto thisG : thisGroup[i] )
                {
                    cout << thisG << " ";
                }
                cout << " | " ;
            }
            cout << endl;
            auto thisGroupNum = allMessage.thisGroupNum;
            for (int i = 0; i < thisGroupNum.size(); ++i) {
                for( auto thisG : thisGroupNum[i] )
                {
                    cout << thisG << " ";
                }
                cout << " | " ;
            }


            cout << endl;
            cout << allWaste << endl;
            for_each(sonVector[1].begin(), sonVector[1].end(), [] ( int a ) { cout << a << " ";});

        }




    }
*/

//    pool.shutdown();

    return 0;
}
