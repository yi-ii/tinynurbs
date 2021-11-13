#include <tinynurbs/tinynurbs.h>
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <cmath>
#include "catch.hpp"
#include <iostream>
#include<string>
#include<sstream>
using namespace std;


int main()
{
    int degree;//度数
    double point_x = 0.0, point_y = 0.0, point_z = 0.0;//用于临时存储控制点的三个坐标
    double weight;//存储权重的临时变量
    tinynurbs::RationalCurve3d crv;//其中d指代double
    vector<glm::vec3> control_points;//控制点数组
    vector<double> weights;//各控制点权重
    vector<double> knots;//结点矢量

    //读取控制点
    ifstream fin;
    fin.open("control_point.txt");
    assert(fin.is_open());//若失败，则输出作物消息
    //通过fin读取txt中的点坐标
    string line;
    while(getline(fin, line))//从文件流中读取一行
    {
        istringstream points(line);//进行绑定
        points >> point_x;//string->double
        points >> point_y;
        points >> point_z;
        control_points.push_back(glm::vec3(point_x, point_y, point_z));
    }

    //读取权重
    fin.open("weight.txt");
    assert(fin.is_open());
    getline(fin, line);
    istringstream weightFile(line);
    while(weightFile >> weight)
    {
        weights.push_back(weight);
    }

    //计算结点矢量
}
