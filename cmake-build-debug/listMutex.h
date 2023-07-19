//
// Created by Admin on 2023/6/17.
//
//#include "E:\code\testSkyLineInGroup\cmake-build-debug\calculatePrize\groupIndent.h"

#include<mutex>
#include<list>
#include <random>
#include <list>
#include <memory>
#include <iostream>
using namespace std;
#include<thread>
#ifndef TESTSKYLINEINGROUP_LISTMUTEX_H
#define TESTSKYLINEINGROUP_LISTMUTEX_H
struct Node
{
public:
    int data;
    Node * next;
    Node * prev;
    std::mutex m;

public:
    Node( int i , Node * n = nullptr )
    {
        data = i;
        next = n;
        prev = n;
    }

    int readData()
    {
        return data;
    }
    Node * toNext( )
    {
        return next;
    }
    Node * toPrev( )
    {
        return prev;
    }


};
class List
{
private:
    Node * head;
    Node * tail;
    int size = 0;

public:
    std::mutex m;
    List( )
    {
        tail = new Node( 0, nullptr );
        head = new Node( 0, nullptr );
        head -> next = tail;
        tail -> prev = head;

    }
    ~List()
    {
//        cout << "hello" << endl;
        delete tail;
        delete head;
    }

    void push_back( int val )
    {
        Node * newNode = new Node( val );
        std::unique_lock<mutex> pre_m( tail -> prev -> m );
        std::unique_lock<mutex> tail_m( tail -> m );
        newNode -> prev = tail -> prev;
        newNode -> next = tail;
        tail -> prev -> next = newNode;
        tail -> prev = newNode;
        size++;
    }
    Node * erase( Node * thisNode )
    {
//        std::unique_lock<mutex> pre_m( thisNode -> prev -> m );
//        std::unique_lock<mutex> next_m( thisNode -> next -> m );
        thisNode -> prev -> next = thisNode -> next;
        thisNode -> next -> prev = thisNode -> prev;
        Node * nextNode = thisNode -> next;
        delete thisNode;
        size--;
        return nextNode;
    }

    Node * begin( )
    {
        std::unique_lock<mutex> lk( head -> m );
        std::unique_lock<mutex> nk( head -> next -> m );
        return head -> next;
    }
    Node * end()
    {
        return tail;
    }
    bool empty()
    {
        return head -> next == tail;
    }

    Node * getTail()
    {
        return tail;
    }
    int getSize( )
    {
//        std::unique_lock<mutex> um( m );
        return size;
    }



};
template<class T>
class listMutix
{
private:
    std::mutex m;
    int size = 0;
public:
    list<T> allgroup;
    void push_back( T & other )
    {
        std::unique_lock<mutex> thisLock( m );
        size++;
        allgroup.push_back( other );
    }
    int getSize()
    {
        return size;
    }
    listMutix( )
    {
        allgroup = list<T>();
    };
    void printMessage( )
    {
        for( auto & thisM : allgroup )
        {
            thisM.printM();
        }
    }

};

//template<class GroupIndent>
void mergeG( listMutix<GroupIndent> & allGroup,  List & numberlist , RectIndentPool & myPool )
{
//        cout << " this thread " << this_thread::get_id() << " Hello" << endl;
    double a = 0;
    while( !numberlist.empty() )
    {
//        cout << "Hello " << endl;
//        numberlist.m.lock();
        std::unique_lock<mutex> list_lk( numberlist.m );
        auto iter = numberlist.begin();
        if( iter == numberlist.getTail() )
            break;
//        T thisGroup( iter -> data );
        GroupIndent thisGroup( myPool.indentPool[ iter -> data ] );
        iter = numberlist.erase( iter );
        if( iter == numberlist.getTail() )
        {
            allGroup.push_back( thisGroup );
//            numberlist.m.unlock();
            break;
        }
        std::unique_lock<mutex> prev_lk( iter -> prev -> m );
        std::unique_lock<mutex> this_lk( iter -> m );
        std::unique_lock<mutex> next_lk( iter -> next ->m );
        list_lk.unlock();
//        numberlist.m.unlock();
        int jj = 0;
        for( ; iter != numberlist.end(); )
        {
            if ( thisGroup.mergeFull )
            {
                break;
            }

//            if( thisGroup.tryNext( iter -> data ))
            if( thisGroup.merge( myPool.indentPool[ iter -> data ], 1000))
            {
                this_lk.release();
                this_lk = move( next_lk );
                iter = numberlist.erase( iter );
                if( iter == numberlist.getTail() )
                {
                    next_lk.release();
                } else
                {
                    next_lk = unique_lock<mutex> ( iter -> next ->m );
                }
                thisGroup.testFull();
            } else
            {
                prev_lk = move( this_lk );
                this_lk = move( next_lk );
                iter = iter -> next;
                if( iter == numberlist.getTail() )
                {
                    break;
//                    this_lk.release();
                } else
                {
                    next_lk = unique_lock<mutex> ( iter -> next ->m );
                }
            }
        }

        allGroup.push_back( thisGroup );
//        cout <<  allGroup.getSize() << endl;
//        if( allGroup.getSize() == 85347 )
//        {
//            cout << endl;
//        }
//        this_lk.lock();
//        if( allGroup.getSize() == )
//        cout << " 剩余列表大小 " << numberlist.getSize() << endl;
    }
//    cout << allGroup.getSize() << endl;
    return;
}


#endif //TESTSKYLINEINGROUP_LISTMUTEX_H
