#ifndef COMPUTE_KNOT_VEC
#define COMPUTE_KNOT_VEC

#include "glm/glm.hpp"
#include<vector>
#include<cmath>
using namespace std;


vector<double> CalKnotVec(const vector<glm::vec<3, double>>& control_points, int degree)
{
    vector<double> temp;
    int n = control_points.size() - 1;
    vector<double> KnotVec(n + degree + 2);
    double sum = 0.0;
    for(int i = 1; i <= n; i++){
        double tempL = pow(control_points[i].x - control_points[i - 1].x, 2) + 
                        pow(control_points[i].y - control_points[i - 1].y, 2) + 
                        pow(control_points[i].z - control_points[i - 1].z, 2);
        temp.push_back(sqrt(tempL));
    }

    for(int i = 0; i <= degree; ++i)
        KnotVec[i] = 0.0;

    for(int i = degree + 1; i <= n + 1; ++i){
        for(int j = i - degree; j <= i - 1; ++j){
            sum = sum + temp[j - 1];
        }
    }
    //cout << sum << endl;

    for(int i = degree + 1; i <= n + 1; ++i){
        double x = 0.0;
        for(int j = i - degree; j <= i - 1; ++j){
            x += temp[j - 1];
        }
        KnotVec[i] = KnotVec[i - 1] + x / sum;
    }

    for(int i = n + 1 ; i <= n + degree + 1; ++i)
        KnotVec[i] = 1.0;

    return KnotVec;
}

#endif