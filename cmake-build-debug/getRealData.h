//
// Created by Admin on 2023/6/29.
//
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include <fstream>

#ifndef TESTSKYLINEINGROUP_GETREALDATA_H
#define TESTSKYLINEINGROUP_GETREALDATA_H
vector<vector<int>>  getSimulateData( string theFilePath , int indSize)
{
    std::ifstream file( theFilePath, std::ios::in );
    vector<vector<int>> selectPo;

    if ( !file.is_open())
    {
        std::cout << " Please check the address, can't open the file!! " << std::endl;
        terminate();
    }
    std::vector<std::vector<std::string>> data;
    std::string line;
    while ( std::getline( file, line ))
    {
        std::vector<std::string> row;
        std::string cell;

        for( char c : line )
        {
            if ( c != ',' )
            {
                cell += c;
            } else {
                row.emplace_back( cell );
                cell.clear();
            }
        }

        row.push_back( cell );
        data.push_back( row );

    }
    file.close();
    int ii = 0;
    for( const auto & row : data )
    {
        int width = std::stoi( row[1] );
        int height = std::stoi( row[2] );
        if ( width < 80 || height < 80 )
        {
            continue;
        }
        if ( width > 988 || height > 988 )
        {
            continue;
        }
        if( height > 685 && width > 685 )
        {
            continue;
        }
        vector<int> thisPo;
        for ( const auto & cell : row )
        {
//            std::cout << cell <<  " ";
            thisPo.emplace_back(stoi( cell ) );
        }
        selectPo.emplace_back( thisPo );
        if ( selectPo.size() > indSize )
        {
            break;
        }

        ii++;
//        std::cout << std::endl << " 个数为 ： " << ii << std::endl;
    }
    return selectPo;


}

/*
RectIndentPool data(){
    int num=0;
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;
    ifstream f_read;
    f_read.open("D:\\workFile\\data.txt", ios::in);  //生成的n个quantity数据 自带库里的随机性不好
    for(int a=0; a<400; a++){
        for(int b=0; b<4; b++){
            f_read >> num;
            if(b==0)
                v1.emplace_back(num);
            else if(b==1)
                v2.emplace_back(num);
            else if(b==2)
                v3.emplace_back(num);
            else if(b==3)
                v4.emplace_back(num);
        }
    }
    int i=0;
//    auto testpool = newrandom(time(NULL));
    RectIndentPool testpool;
    for(i=0;i<400;i++){
        RectIndent temp(v2[i],v1[i],v3[i],v4[i]);
        testpool.indentPool.emplace_back(temp);
    }
    return testpool;
}
*/

#endif //TESTSKYLINEINGROUP_GETREALDATA_H
