//
// Created by Admin on 2023/5/22.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include<random>
#include <thread>
#include <set>
#ifndef UNTITLED9_SIMULATEBETA_H
#define UNTITLED9_SIMULATEBETA_H

using namespace std;
// 生成模拟数据
// 生成随机数，长和宽
void randSbeta( vector<double> & a , const double & size , int seed = 0 )
{
    if( seed == 0 )
    {
        std::random_device rd;
        std::mt19937 gen( rd() );
        std::uniform_int_distribution<int> dist( 100, 500 );
        for (int i = 0; i < size; ++i) {
            a[ i ] = dist( gen );
        }
    }else
    {
        std::mt19937 gen( seed );
        std::uniform_int_distribution<int> dist( 100, 500 );
        for (int i = 0; i < size; ++i) {
            a[ i ] = dist( gen );
        }
    }


}

void otherSideBeta( vector<double> & width, vector<double> & height, int seed = 0 )
{
    if( seed == 0 )
    {
        std::random_device rd;
        std::mt19937  gen( rd() );
        std::uniform_int_distribution dist( -10, 50 );
        for (int i = 0; i < width.size(); ++i) {
            height[i] = width[i] + dist( gen );
        }
    } else
    {
        std::mt19937  gen( seed );
        std::uniform_int_distribution dist( -10, 50 );
        for (int i = 0; i < width.size(); ++i) {
            height[i] = width[i] + dist( gen );
        }
    }
}

void quantitySet( vector<double> & quantityList , int seed = 0 )
{
    if( seed == 0 )
    {
        std::random_device rd;
        std::mt19937 gen( rd() );
        std::uniform_int_distribution dist( 1000, 20000 );
        std::uniform_int_distribution dist1( 10, 100);
        std::uniform_int_distribution dist2( 1, 3);
        int i = 0;
        while( i < quantityList.size() )
        {
            int rand = dist2( gen );
            int randNum = dist( gen ) / 100 * 100;
            int randNum1 = dist1( gen ) / 10 * 10;
            switch ( rand ) {
                case 1 :
                    quantityList[ i++ ] = randNum;
                    break;
                case 2 :
                    quantityList[ i++ ] = randNum + randNum1;
                    break;
            }

        }

    } else
    {
        std::mt19937 gen( seed );
        std::uniform_int_distribution dist( 1000, 20000 );
        std::uniform_int_distribution dist1( 10, 100);
        std::uniform_int_distribution dist2( 1, 3);
        int i = 0;
        while( i < quantityList.size() )
        {
            int rand = dist2( gen );
            int randNum = dist( gen ) / 100 * 100;
            int randNum1 = dist1( gen ) / 10 * 10;
            switch ( rand ) {
                case 1 :
                    quantityList[ i++ ] = randNum;
                    break;
                case 2 :
                    quantityList[ i++ ] = randNum + randNum1;
                    break;
            }

        }

    }

}

void areaCount( vector<double> & width, vector<double> & height, vector<double> & area )
{
    for (int i = 0; i < width.size(); ++i) {
        area[ i ] = width[ i ] * height[ i ];
    }
}

void randList( list<int> & thisList, vector<int> & thisVector )
{
    random_device rd;
    mt19937 gen( rd() );
    std::shuffle( thisVector.begin(), thisVector.end(), gen );
    for (int i = 0; i < thisVector.size(); ++i) {
        thisList.emplace_back( thisVector[i] );
    }
}

void randList( vector<list<int>> & thisList, int size )
{
    vector<int> thisVector;
    for (int i = 0; i < size; ++i) {
        thisVector.emplace_back( i );
    }
    int listSize = thisList.size();
    random_device rd;
    mt19937 gen( rd() );

    for (int i = 0; i < listSize; ++i) {
        std::shuffle( thisVector.begin(), thisVector.end(), gen );
        for (int j = 0; j < thisVector.size(); ++j) {
            thisList[j].emplace_back( thisVector[i] );
        }
    }
}


void getFirstGeneration(  vector<list<int>> & individualGroup,  vector<vector<int>> & individualVector, int & baseSize, int & seed)
{
    vector<int> baseSequence( baseSize );
    for (int i = 0; i < baseSequence.size(); ++i) {
        baseSequence[i] = i;
    }
    mt19937 gen( seed );
    for (int i = 0; i < individualGroup.size(); ++i) {
        shuffle( baseSequence.begin(), baseSequence.end(), gen );
        individualVector.emplace_back( baseSequence );
        for (int j = 0; j < baseSequence.size(); ++j) {
            individualGroup[i].emplace_back( baseSequence[j] );
        }
    }
}

void vectorTolist( vector<list<int>> & individualGroup,  vector<vector<int>> & individualVector )
{
    for (int i = 0; i < individualVector.size(); ++i) {
        for (int j = 0; j < individualVector[i].size(); ++j) {
            individualGroup[i].emplace_back( individualVector[i][j]);
        }
    }
}

void listToVector( vector<list<int>> & individualGroup,  vector<vector<int>> & individualVector )
{
    for (int i = 0; i < individualGroup.size(); ++i) {
        for( auto & thisV : individualGroup[i] )
        {
            individualVector[i].emplace_back( thisV );
        }
    }
}


void changeBase( vector<int> & lfInd, vector<int> & rgInd, int & index, vector<int> & son )
{
    if( son[index] ==  lfInd[index] )
        return;
    double temp = son[index];
    son[index] = lfInd[ index ];
    for (int i = 0; i < son.size(); ++i) {
        if( son[i] == lfInd[index] )
        {
            son[i] = temp;
            break;
        }
    }
//    int temp = lfInd[ index ];
//    for (int i = 0; i < son.size(); ++i) {
//        if( son[i] == temp )
//        {
//            son[i] = rgInd[index];
//            break;
//        }
//    }
//    son[index] = temp;
}

void variation( vector<int> & son )
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0, 1);
    double randNum =  distribution( generator);
    for (int i = 0; i < son.size()/100; ++i) {
        if( randNum < 0.01 )
        {
            std::uniform_int_distribution<int> dist(0, son.size() - 30 );
            std::uniform_int_distribution<int> dist2(10, 30);
            int pitch = dist( generator );
            int pitch2 = pitch + dist2( generator );
            reverse( son.begin()+pitch, son.begin()+pitch2 );
        }
    }

}
void printV( vector<int> thiV )
{
    for (int i = 0; i < thiV.size(); ++i) {
        cout << thiV[i] << " ";
    }
    cout << endl;
}

vector<int>  crossOver( int id1, int id2, vector<vector<int>> & individualGroup, int seed = 0 )
{
    vector<int>  & lfInd = individualGroup[ id1 ];
    vector<int>  & rgInd = individualGroup[ id2 ];
//    printV( lfInd );
//    printV( rgInd );
//    cout << endl;
    vector<int>   son = rgInd;
    vector<int>  choosenList = rgInd;
    random_device rd;
    mt19937 gen( rd() );
    shuffle( choosenList.begin(), choosenList.end(), gen );

    for (int i = 0; i < ( choosenList.size() / 3 ); ++i) {
        changeBase( lfInd, rgInd, choosenList[i], son );
//        int temp = lfInd[ choosenList[i] ];
    }
    return son;
}

vector<int> chooseParent( vector<double> & cum_probs )
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1);
    vector<int> lengthInt( 5 );
    vector<int> parentSeq;
    for ( int i = 0; i < 2; ++i )
    {
        double rnd = dist(rng);
        auto indexItr = upper_bound(cum_probs.begin(), cum_probs.end(), rnd);
        // 按照概率选出的系数
        int indexii = static_cast<int>(std::distance(cum_probs.begin(), indexItr));
        parentSeq.push_back( indexii );
    }
    return parentSeq;
}

vector<double> cum_probability( vector<double> & wasteList )
{
    double individualSize = wasteList.size();
    // 按照每个个体浪费量大小排序，从低到高
    vector<int> indexOrder;
    vector<double> wasteListCopy = wasteList;
    sort(wasteListCopy.begin(), wasteListCopy.end());
    int originate = 0;
    while( originate < wasteList.size() )
    {
        for (int i = 0; i < wasteList.size(); ++i) {
            if( wasteList[originate] == wasteListCopy[i] )
            {
                indexOrder.push_back( i );
                originate++;
            }
        }
    }

    // 设置加权
    vector<double> probWeigth;
    double tatolWeight = 0;
    for (int i = 0; i < individualSize; ++i) {
        probWeigth.push_back( (individualSize - indexOrder[i])*wasteList[i] );
        tatolWeight += (individualSize - indexOrder[i])*wasteList[i];
    }
    //设置每个个体保留下来产生后代的概率
    vector<double> probability;
    for (int i = 0; i < individualSize; ++i) {
        probability.push_back( probWeigth[i] / tatolWeight );
    }

    vector<double> cum_probs( probability.size() );
    partial_sum(probability.begin(), probability.end(), cum_probs.begin());
    return cum_probs;

}

void exchange( vector<int> & son, list<int> & sonlist )
{

    for( auto & thisbase : son )
    {
        sonlist.emplace_back(thisbase);
    }
}





vector<list<int>> donminantIndividual( vector<list<int>> & parentCopy,
                                       vector<list<int>> & sonCopy,
                                       vector<double> & parentWasteList,
                                       vector<double> & sonWasteList )
{
    vector<double> pcopy = parentWasteList;
    pcopy.insert(pcopy.end(), sonWasteList.begin(), sonWasteList.end() );
    vector<double> ppcopy = pcopy;
    vector<list<int>> &plist = parentCopy;
    vector<list<int>> dominantGroup;
    plist.insert(plist.begin(), sonCopy.begin(), sonCopy.end());
    std::sort(pcopy.begin(), pcopy.end());
    for (int i = 0; i < parentCopy.size()/2; ++i) {
        for (int j = 0; j < ppcopy.size(); ++j) {
            if( pcopy[i] == ppcopy[j] )
            {
                dominantGroup.push_back(plist[j]);
                break;
            }
        }
    }
//    cout << " ===== " << dominantGroup.size() << endl;
    return dominantGroup;

}


vector<int> chooseIndividual( vector<double> & parentWasteList,
                              vector<double> & sonWasteList )
{
    vector<double> pcopy;
    for( auto & thiswaste : parentWasteList )
    {
        if( thiswaste )
            pcopy.emplace_back( thiswaste );
    }
    for( auto & thiswaste : sonWasteList )
    {
        pcopy.emplace_back(thiswaste);
    }

    vector<double> ppcopy = pcopy;
//    for_each( pcopy.begin(), pcopy.end(), []( int a ){ cout << a << " "; });
//    cout << endl;

    vector<pair<int, double>> thisPair;
    for (int i = 0; i < ppcopy.size(); ++i) {
        pair<int, double> thePaire{ ppcopy[i], i };
        thisPair.emplace_back( thePaire );
    }
    std::sort( thisPair.begin(), thisPair.end() );

    vector<pair<int, int>> thisPair2;
    for (int i = 0; i < thisPair.size(); ++i) {
        pair<int, int> thePaire2{ thisPair[i].second, i };
        thisPair2.emplace_back( thePaire2 );
    }
    std::sort( thisPair2.begin(), thisPair2.end() );

//    std::sort(pcopy.begin(), pcopy.end());
    vector<int> choosIndex;
    for (int i = 0; i < thisPair2.size(); ++i) {
        choosIndex.emplace_back( thisPair2[i].second );
    }

//    for (int i = 0; i < pcopy.size(); ++i) {
//        for (int j = 0; j < ppcopy.size(); ++j) {
//            if( pcopy[j] == ppcopy[i] )
//            {
//                choosIndex.push_back( j );
//                break;
//            }
//        }
//    }
    return choosIndex;

}

void topRankIndividual( vector<list<int>> & backupDescedant,
                        vector<list<int>> & ancestor,
                        vector<list<int>> & sonIndividual,
                        vector<double> & backupDescentWaste,
                        vector<double> &wasteList,
                        vector<double> &sonWasteList,
                        const int & MaxIndividuals )
{
    vector<int> chooseIndex = chooseIndividual( wasteList, sonWasteList);
//    vector<double> theCopy = wasteList;
//    theCopy.insert(theCopy.end(), sonWasteList.begin(), sonWasteList.end() );
//    for_each( chooseIndex.begin(), chooseIndex.end(), []( int a ){ cout << a << " "; });
//    cout << endl;
//    for_each( theCopy.begin(), theCopy.end(), []( int a ){ cout << a << " "; });

    cout << endl;
    for (int i = 0; i < chooseIndex.size(); ++i) {
        if( i >= MaxIndividuals )
        {
            if( chooseIndex[i] < MaxIndividuals )
            {
                backupDescedant.push_back( sonIndividual[ i - MaxIndividuals ] );
                backupDescentWaste.push_back( sonWasteList[ i - MaxIndividuals ] );
            }
        }else if( i < MaxIndividuals )
        {
            if( chooseIndex[i] < MaxIndividuals )
            {
                backupDescedant.push_back( ancestor[i] );
                backupDescentWaste.push_back( wasteList[i] );
//                cout << wasteList[i] << endl;
            }
        }
    }



}


void printAverage( vector<double> & waste , vector<double> & wasteNext )
{
    double totall = 0;
    for( auto thisWaste : waste )
    {
        totall += thisWaste;
    }
//    cout << static_cast<int> (totall/waste.size()) <<  endl;

    double totall2 = 0;
    for( auto & thisWastNext : wasteNext )
    {
        totall2 += thisWastNext;
    }
    cout << static_cast<int>( (totall- totall2)/waste.size()) << endl;
}

void printAverage( vector<double> & waste  )
{
    double totall = 0;
    for( auto thisWaste : waste )
    {
        totall += thisWaste;
    }
    cout << static_cast<int> (totall/waste.size()) <<  endl;
//    cout << static_cast<int>( (totall- totall2)/waste.size()) << endl;
}


void printIndex( vector<list<int>> & parent )
{
        for( auto & thisP : parent[25] )
        {
            cout << thisP << " ";
        }
}


bool equal( vector<int> & lfs, vector<int> & rhs )
{
    for (int i = 0; i < lfs.size(); ++i) {
        if( lfs[i] != rhs[i] )
        {
            return true;
        }

    }
    return false;
}


#endif //UNTITLED9_SIMULATEBETA_H
