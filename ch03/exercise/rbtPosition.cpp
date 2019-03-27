/*
 * p61, exercise 07 for chap 03
 * rbt01, rbt02 poses are known in unnormalized Quaternion form
 * of transformation from world frame to camera frame
 * the goal is find a point position expressed in rbt02 frame with
 * known coordinate in rbt01 frame
*/
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>

int main(int argc, char** argv)
{
    Eigen::Vector4d q1(0.35, 0.2, 0.3, 0.1);
    q1.normalize();
    // quaternion from 4d vector with order (w, x, y, z)
    Eigen::Quaterniond Q1 = Eigen::Quaterniond(q1);
    // Tij represents the transformation from frame j to frame i
    // 0 usually represents the world frame
    Eigen::Isometry3d T10 = Eigen::Isometry3d::Identity();
    T10.rotate(Q1);
    T10.pretranslate(Eigen::Vector3d(0.3, 0.1, 0.1));

    Eigen::Vector4d q2(-0.5, 0.4, -0.1, 0.2);
    q2.normalize();
    // quaternion from 4d vector with order (w, x, y, z)
    Eigen::Quaterniond Q2 = Eigen::Quaterniond(q2);

    Eigen::Isometry3d T20 = Eigen::Isometry3d::Identity();
    T20.rotate(Q2);
    T20.pretranslate(Eigen::Vector3d(-0.1, 0.5, 0.3));

    Eigen::Vector3d p_in1(0.5, 0, 0.2);
    Eigen::Vector3d p_in2 = T20*T10.inverse()*p_in1;

    std::cout << "the point observed in robo 2 frame is: " << p_in2.transpose() << std::endl;
    return 0;
}
