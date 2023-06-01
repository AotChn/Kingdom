#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

template<class T>
struct Node
{
  Node(T* data, Node* next): _data(data), _next(next){}
  T* _data;
  Node* _next;
};

class Window_Observer
{
public:

  //=========================
  //BIG 3
  //=========================

  Window_Observer(){
    _no = _static_number++;
  }
  
  virtual ~Window_Observer(){}
  
  //=========================
  //INFO TRANSMIT
  //=========================
  
  virtual void Update(sf::RenderWindow& window, int event) = 0;
  
  //=========================
  //DEBUG MSG
  //=========================

  void Detach_msg(){
      std::cout << "Window_Observer " << _no << " is Detaching from Window_Subject\n";
  }
  
  void Attach_msg(){
      std::cout << "Window_Observer " << _no << " is Attaching to Window_Subject\n";
  }

private:
  int _no;
  static int  _static_number;
};

class Window_Subject {
public:
  //=========================
  //BIG 3
  //=========================

  virtual ~Window_Subject(){
    Node<Window_Observer>* here;
    while(_head !=nullptr){
      here = _head;
      _head = _head->_next;
      delete here;
    }
  }
  
  //=========================
  //INFO MANIP
  //=========================

  virtual void Attach(Window_Observer *observer){
    ++_no_observer;
    if(_debug)
      observer->Attach_msg();
    Node<Window_Observer>* new_n = new Node<Window_Observer>(observer, _head);
    _head = new_n;
  }
  
  virtual void Detach(Window_Observer *observer){
    if(_head == nullptr) return;
    if(_head->_data == observer){
      Node<Window_Observer>* here = _head;
      if(_debug)
        observer->Detach_msg();
      --_no_observer;
      _head = _head->_next;
      delete here;
      return;
    }

    Node<Window_Observer>* last = _head, *current = _head->_next;
    
    while ( current != nullptr )
    { 
      if( current->_data == observer ){
        if(_debug)
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
  
  virtual void Notify(sf::RenderWindow& window, int event){
    if(_debug)
      How_many_observer();
    auto w = _head;
    while(w !=nullptr){
      w->_data->Update(window, event);
      w = w->_next;
    }

  }

  //=========================
  //DEBUG MSG
  //=========================

  void How_many_observer(){
    std::cout << "There are " << _no_observer << " observers in the list\n";
  }

private:
  typedef int size_t;
  
  Node<Window_Observer>* _head = nullptr;
  size_t _no_observer = 0;
  
  static bool _debug;
};



