#include <tinynurbs/tinynurbs.h>
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <cmath>
#include "catch.hpp"
#include "Compute_node_vector.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tinynurbs/util/util.h"
#include "outPoints.h"
using namespace std;

int main()
{
    //cout << "请输入曲线的阶数：...(无符号整形)" << endl;
    unsigned int degree = 5;
    //cin >> degree;
    double weight;//存储权重的临时变量
    vector<glm::vec<3, double>> control_points;//控制点数组
    vector<double> weights;//各控制点权重
    vector<double> knots;//结点矢量
    int pointsNumber = 1000;//设置曲线上点个个数
    vector<glm::vec<3, double>> Points, firstDerVec, secondDerVec, thirdDerVec;

    //读取控制点
    ifstream CP_in;
    string controlsPointPath("control_point.dat");
    cout << "读取控制点..." << endl;
    CP_in.open(controlsPointPath, fstream::in);
    if (!CP_in.is_open()) { //若失败，则输出作物消息
        cout << "can not open this file" << endl;
        return 0;
    }
    //通过fin读取txt中的点坐标
    string line;
    while (getline(CP_in, line)) {//从文件流中读取一行
        istringstream points(line);//进行绑定
        glm::vec<3, double> tempVec3;
        points >> tempVec3.x;//string->double
        points >> tempVec3.y;
        points >> tempVec3.z;
        if (tempVec3.length() > 0) {
            control_points.push_back(tempVec3);
        }
        else {
            cout << "错误：输入控制点大小为0" << endl;
            return 0;
        }
    }
    cout << "输出点的个数：" << control_points.size() << endl;
    CP_in.close();

    //读取权重
    ifstream We_in;
    string weightsPath("weights.dat");
    cout << "读取权重..." << endl;
    We_in.open(weightsPath, fstream::in);
    if (!We_in.is_open()) {
        cout << "can not open this file" << endl;
        return 0;
    }
    getline(We_in, line);
    istringstream weightFile(line);
    while (weightFile >> weight) {
        weights.push_back(weight);
    }
    cout << "输出权重点的个数：" << weights.size() << endl;
    We_in.close();

    //计算结点矢量
    cout << "计算节点矢量..." << endl;
    vector<double> knotsVec = CalKnotVec(control_points, degree);

    //读取信息后，对曲线进行赋值
    tinynurbs::RationalCurve3d crv(degree, knotsVec, control_points, weights);

    //检查曲线是否有效
    cout << "检查曲线是否有效..." << endl;
    if (!tinynurbs::curveIsValid(crv)) {
        cerr << "曲线无效" << endl;
    }
    else {
        cout << "曲线有效" << endl;
    }

    //计算曲线上的点
    cout << "计算曲线上的点、一阶导数..." << endl;
    for (int i = 0; i <= pointsNumber; ++i) {
        std::vector<glm::vec<3, double>> tempDer = tinynurbs::curveDerivatives(crv, 4, (double)i / pointsNumber);
        Points.push_back(glm::vec<3, double>(tempDer[0].x, tempDer[0].y, tempDer[0].z));
        firstDerVec.push_back(glm::vec<3, double>(tempDer[1].x, tempDer[1].y, tempDer[1].z));// dx / du,  dy / du
        secondDerVec.push_back(glm::vec<3, double>(tempDer[2].x, tempDer[2].y, tempDer[2].z));// d^2x/ du^2 注意转换
        thirdDerVec.push_back(glm::vec<3, double>(tempDer[3].x, tempDer[3].y, tempDer[3].z));
    }

    //输出曲线上的点
    string pointOutPath("Points.txt");
    string firstDerOutPath("FirstDer.txt"), secondDerOutPath("SecondDer.txt"), thirdDerOutPath("ThirdDer.txt");
    cout << "输出曲线一、二和三阶导数" << endl;
    if (!OutputPoints(Points, pointOutPath)) {
        cout << "Points输出失败" << endl;
    }
    if (!OutputPoints(firstDerVec, firstDerOutPath)) {
        cout << "firstDerVec输出失败" << endl;
    }
    if (!OutputPoints(secondDerVec, secondDerOutPath)) {
        cout << "firstDerVec输出失败" << endl;
    }
    if (!OutputPoints(thirdDerVec, thirdDerOutPath)) {
        cout << "firstDerVec输出失败" << endl;
    }
    return 0;
}
