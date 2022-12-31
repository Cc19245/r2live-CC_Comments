#pragma once
#include <eigen3/Eigen/Dense>
#include <iostream>
#include "../factor/imu_factor.h"
#include "../utility/utility.h"
#include <ros/ros.h>
#include <map>
#include "../feature_manager.h"

using namespace Eigen;
using namespace std;

/*
    ImageFrame 图像帧
    图像帧类可由图像帧的特征点与时间戳构造，
    此外还保存了位姿Rt，预积分对象pre_integration，是否是关键帧。
*/
class ImageFrame
{
public:
    ImageFrame(){};
    ImageFrame(const map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> &_points, double _t) : t{_t}, is_key_frame{false}
    {
        points = _points;
    };

    map<int, vector<pair<int, Eigen::Matrix<double, 7, 1>>>> points;
    double t;
    Matrix3d R;
    Vector3d T;
    bool is_key_frame;
    StatesGroup m_state_prior;
    IntegrationBase *pre_integration;

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

bool VisualIMUAlignment(map<double, ImageFrame> &all_image_frame, Vector3d *Bgs, Vector3d &g, VectorXd &x);