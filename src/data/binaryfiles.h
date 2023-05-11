#ifndef BINARY_FILES
#define BINARY_FILES

#include <iostream>
#include <fstream>

using namespace std;

int wrote(){
    ofstream wf("map-data.bin", ios::out | ios::binary);
    if(!wf) {
        cout << "Cannot open file!" << endl;
        return 1;
    }
    int y[5] = {1,2,3,4,5};
    for(int i = 0; i < 5; i++)
        wf.write((char *) &y[i], sizeof(int));
    wf.close();

    if(!wf.good()) {
        cout << "Error occurred at writing time!" << endl;
        return 1;
    }
    // ifstream rf("map-data.bin", ios::out | ios::binary);
    // if(!rf) {
    //     cout << "Cannot open file!" << endl;
    //     return 1;
    // }
    // int Y[5];
    // for(int i = 0; i < 5; i++)
    //     rf.read((char *) &Y[i], sizeof(int));
    // rf.close();
    // if(!rf.good()) {
    //     cout << "Error occurred at reading time!" << endl;
    //     return 1;
    // }
    // cout<<"Student's Details:"<<endl;
    // for(int i=0; i < 5; i++) {
    //     cout << "Roll No: " << Y[i] << endl;
    //     cout << endl;
    // }
    // return 0;
}

int unit_sample(int idx){
    // ofstream w("map-data.bin", ios::out | ios::binary);
    // if(!w){
    //     cout<< "no file opened idiot" <<endl;
    //     return 1
    // }
    // int sample[6] = {1,0,0,1,1,0};
    // for(int i=0 ;i<5; i++)
    //     w.write(&sample[i], sizeof(int));
    // w.close;
}


#endif