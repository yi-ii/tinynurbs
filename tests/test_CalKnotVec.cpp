#include<iostream>
#include<vector>
#include<glm/glm.hpp>
#include"Compute_node_vector.h"
using namespace std;

int main()
{
    int degree = 2;
    vector<glm::vec<3,double>> control_points {{-80.0, -60.0, 0.0}, {-40.0, 20.0, 0.0}, 
    {-20.0, 10.0, 0.0}, {-10.0, 20.0, 0.0}, {30.0, -20.0, 0.0}};
    std::vector<double> KnotVec;
    KnotVec = CalKnotVec(control_points, degree);
    for(auto i:KnotVec)
        cout << i << " ";
    cout<<endl;

    return 0;
}