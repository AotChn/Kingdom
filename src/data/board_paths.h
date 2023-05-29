#ifndef BOARD_PATHS_H
#define BOARD_PATHS_H

#include <vector>
#include <queue>
#include <iostream>
#include <cmath>
#include "../graphics/tile.h"
#include "../graphics/board.h"

struct path_node{
    path_node() : parent(nullptr){}
    path_node(tile T) : t(T), parent(nullptr){}
    path_node(tile T,  path_node P) : t(T), parent(&P){}
    path_node(tile T, tile s, tile e, path_node *P) : t(T), parent(P){set_g_cost(s);set_h_cost(e);}

    tile get_parent(){return parent->get_tile();}
    tile get_tile(){return t;}
    int get_g_cost(){return g_cost;}
    int get_h_cost(){return h_cost;}
    int get_f_cost(){return f_cost;}
    
    void set_tile(tile T){t = T;} 
    void set_parent(path_node P){parent = &P;}
    void set_g_cost(tile src){g_cost = t.find_distance(t,src);}
    void set_h_cost(tile dest) {h_cost = t.find_distance(t, dest);}
    void set_f_cost(){f_cost = g_cost + h_cost;}

    int f_cost;
    int g_cost;
    int h_cost;
    tile t;
    path_node* parent; 

    path_node& operator=(const path_node& rhs){
        t = rhs.t;
        f_cost = rhs.f_cost;
        g_cost = rhs.g_cost;
        h_cost = rhs.h_cost;
        return *this;
    }

    bool operator<(const path_node& rhs) const{
        return f_cost < rhs.f_cost;
    }

    friend bool operator <(const path_node& lhs, path_node& rhs){
        return lhs.f_cost < rhs.f_cost;
    }
    friend bool operator >(const path_node& lhs, path_node& rhs){
        return lhs.f_cost > rhs.f_cost;
    }
    friend bool operator ==(const path_node& lhs, path_node& rhs){
        return lhs.f_cost == rhs.f_cost;
    }
    friend bool operator !=(const path_node& lhs, path_node& rhs){
        return lhs.f_cost != rhs.f_cost;
    }
};


int index(tile t,int i=0, int j=0, int col=0){
    return (((t.y+j)*col)+(t.x+i))+1;
} 

class board_paths{
    public:
    board_paths(){};
    void set_board(const std::vector<int> &graph);
    bool find_path(tile, tile);
    std::vector<tile> get_path(){return path;}

    int get_closed_size(){return closed.size();}
    void print_bool_graph(int col, std::vector<bool> graph);
    void print_bool(){print_bool_graph(10,closed);}

    private:
    std::vector<tile> path; 
    std::vector<bool> closed; 

};

void board_paths::set_board(const std::vector<int> &graph){
    std::cout << "size of graph : "<< graph.size() << std::endl;
    for(int i=0; i<graph.size(); i++){
        if(graph[i] < 1)
            closed.push_back(true);
        else
            closed.push_back(false);
    }
}

//temp col = 6
const int llop = 10;
bool board_paths::find_path(tile src, tile dest){
    std::priority_queue<path_node, std::vector<path_node>, std::less<path_node>> open;
    path_node start(src, src, dest,nullptr);
    open.emplace(start);
    int count = 0;
    while(!open.empty()){
        count++;
        std::cout<< "count" << count << std::endl;
        path_node cur = open.top();
        if(cur.t == dest)
            return true;
        closed.at(index(cur.t,0,0,llop)) = true;
        std::cout<< "check index" << index(cur.t,0,1,llop) << std::endl;
        if(closed.at(index(cur.t,0,1,llop)) == false){
            tile temp(cur.t.x+0, cur.t.y+1);
            path_node * p = &cur;
            open.emplace(path_node(temp, src, dest, p));
            std::cout<< "up" << "|";
        } // pos y
        // if(closed.at(index(cur.t,1,0,llop)) == false){
        //     tile temp(cur.t.x+1, cur.t.y+1);
        //     path_node * p = &cur;
        //     open.emplace(path_node(src, src, dest, p));
        //     std::cout<< "right" << "|";
        // } // pos x
        if(closed.at(index(cur.t,0,-1,llop)) == false){
            tile temp(cur.t.x+0, cur.t.y-1);
            path_node * p = &cur;
            open.emplace(path_node(temp, src, dest, p));
            std::cout<< "down" << "|";
        } // pos y
        // if(closed.at(index(cur.t,-1,0,llop)) == false){
        //     tile temp(cur.t.x-1, cur.t.y);
        //     path_node * p = &cur;
        //     open.emplace(path_node(src, src, dest, p));
        //     std::cout<< "left" << "|";
        // } // pos x
        open.pop();
    }
    return false;
}


void board_paths::print_bool_graph(int col, std::vector<bool> graph){
    for(int i=0; i<graph.size(); i++){
        if(i%col==0 && i!=0){
            std::cout<< std::endl;
        }
        if(graph[i] == false)
            std::cout<<"["<<i<<"]"<< "X ";
        if(graph[i] == true)
            std::cout<< "["<<i<<"]" << "O ";
    }
    std::cout<<"done";
}



#endif