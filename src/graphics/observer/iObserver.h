//#pragma once

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <iostream>
#include <assert.h>

template<class T>
struct Node
{
  Node(T* data, Node* next): _data(data), _next(next){}
  T* _data;
  Node* _next;
};

class iObserver
{
public:

  //=========================
  //BIG 3
  //=========================

  iObserver(){
    _no = _static_number++;
  }
  
  virtual ~iObserver(){}
  
  //=========================
  //INFO TRANSMIT
  //=========================
  
  virtual void onNotify() {assert(false);};
  
  //=========================
  //DEBUG MSG
  //=========================

  virtual void Detach_msg(){
      std::cout << "iObserver " << _no << " is Detaching from iSubject\n";
  }
  
  virtual void Attach_msg(){
      std::cout << "iObserver " << _no << " is Attaching to iSubject\n";
  }

protected:
  int _no;
  static int  _static_number;
  static bool _obs_debug;
};

class iSubject {
public:
  //=========================
  //BIG 3
  //=========================

  virtual ~iSubject(){
    Node<iObserver>* here;
    while(_head !=nullptr){
      Detach(_head->_data);
    }
  }
  
  //=========================
  //
  //=========================

  virtual void Attach(iObserver *observer){
    ++_no_observer;
    if(_sub_debug)
      observer->Attach_msg();
    Node<iObserver>* new_n = new Node<iObserver>(observer, _head);
    _head = new_n;
  }
  
  virtual void Detach(iObserver *observer){
    if(_head == nullptr) return;
    if(_head->_data == observer){
      Node<iObserver>* here = _head;
      if(_sub_debug)
        observer->Detach_msg();
      --_no_observer;
      _head = _head->_next;
      delete here;
      return;
    }

    Node<iObserver>* last = _head, *current = _head->_next;
    
    while ( current != nullptr )
    { 
      if( current->_data == observer ){
        if(_sub_debug)
          observer->Detach_msg();
        --_no_observer;
        last->_next = current->_next;
        delete current;
        return;
      }

      last = current;
      current = last->_next;
    }
  }
  
  virtual void Notify() {assert(false);}

  //=========================
  //DEBUG MSG
  //=========================

  void How_many_observer(){
    std::cout << "There are " << _no_observer << " observers in the list\n";
  }

protected:
  typedef int size_t;
  static bool _sub_debug;
  Node<iObserver>* _head = nullptr;
  size_t _no_observer = 0;
  
};


//#include "iObserver.cpp"
#endif