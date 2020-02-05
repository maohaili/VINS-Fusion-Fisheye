#include <opencv/cv.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/core/eigen.hpp>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <opencv2/cudastereo.hpp>

class DepthEstimator {
    Eigen::Vector3d t01;
    Eigen::Matrix3d R01;
    cv::Mat cameraMatrix;
    bool show = false;
    int num_disp = 16;
    bool use_sgbm_cpu = true;
    cv::Mat _map11, _map12, _map21, _map22;
    cv::cuda::GpuMat map11, map12, map21, map22;
    bool first_init = true;
    cv::Mat R, T, R1, R2, P1, P2, Q;
    double baseline = 0;

    int block_size = 9;
    int min_disparity = 2;
    int disp12Maxdiff = 28;
    int prefilterCap = 39;
    int uniquenessRatio = 25;
    int speckleWindowSize = 300;
    int speckleRange = 5;
    int mode = cv::StereoSGBM::MODE_HH;
public:
    DepthEstimator(Eigen::Vector3d t01, Eigen::Matrix3d R01, cv::Mat camera_mat,
    bool _show):
        cameraMatrix(camera_mat),show(_show)
    {
        cv::eigen2cv(R01, R);
        cv::eigen2cv(t01, T);
    }

    cv::Mat ComputeDispartiyMap(cv::cuda::GpuMat & left, cv::cuda::GpuMat & right);
    cv::Mat ComputeDispartiyMapVisionWorks(cv::cuda::GpuMat & left, cv::cuda::GpuMat & right);
    cv::Mat ComputeDepthCloud(cv::cuda::GpuMat & left, cv::cuda::GpuMat & right);
};