#ifndef OUTPUT_DER
#define OUTPUT_DER

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "glm/glm.hpp"
using namespace std;

template<typename T>
int OutputPoints(const vector<glm::vec<3, T>>& Points, string outPath){
    ofstream outStream;
    outStream.open(outPath, fstream::out);
    if(!outStream.is_open()){
        cout << outPath << "打开出错。" << endl;
        return 0;
    }
    int n = Points.size();
    int m = Points[0].length();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            outStream << Points[i][j] << "    ";
        }
        outStream << endl;
    }
    outStream.close();

    return 1;
}


#endif