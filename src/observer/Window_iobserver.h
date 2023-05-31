#pragma once

#include <SFML/Graphics.hpp>

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
    virtual ~Window_Observer(){}
    virtual void Update(sf::RenderWindow& window, int event) = 0;

};


class Window_Subject {
public:
  virtual ~Window_Subject(){
    Node<Window_Observer>* here;
    while(_head !=nullptr){
      here = _head;
      _head = _head->_next;
      delete here;
    }
  }
  virtual void Attach(Window_Observer *observer){
    Node<Window_Observer>* new_n = new Node<Window_Observer>(observer, _head);
    _head = new_n;
  }
  virtual void Detach(Window_Observer *observer){
    if(_head == nullptr) return;
    if(_head->_data == observer){
      Node<Window_Observer>* here = _head;
      _head = _head->_next;
      delete here;
      return;
    }

    Node<Window_Observer>* last = _head, *current = _head->_next;
    while (current != nullptr)
    { 
      if(current->_data == observer){
        last->_next = current->_next;
        delete current;
        return;
      }

      last = current;
      current = last->_next;
    }
  }
  virtual void Notify(sf::RenderWindow& window, int event){
    auto w = _head;
    while(w !=nullptr){
      w->_data->Update(window, event);
      w = w->_next;
    }

  }

private:
  Node<Window_Observer>* _head = nullptr;
};