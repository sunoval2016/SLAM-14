#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

int main()
{
    // Eigen/Geometry provides various representation for rotation and translation
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // rotation vector with AngleAxis, it's not matrix in bottom, but could be calculated as matrix due to overloading
    // rotate 45 deg about z
    Eigen::AngleAxisd rotation_vector(M_PI/4, Eigen::Vector3d(0, 0, 1));
    cout.precision(3);
    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;
    rotation_matrix = rotation_vector.toRotationMatrix();
    // coordinate transformation with AngleAxis
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_vector * v;  // can do this directly?
    cout << "(1, 0, 0) after rotation: " << v_rotated.transpose() << endl;
    // or use rotation matrix
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation: " << v_rotated.transpose() << endl;

    // Euler angles
    // ZYX order, i.e. yaw pitch roll
    // R = Rz*Ry*Rx from body to fixed frame
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "yaw pitch roll: " << euler_angles.transpose() << endl;
    // Euler transformation with Isometry
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();  // called 3d, actually 4x4
    T.rotate(rotation_vector);  // rotate about rotation_vector
    cout << "Transformation matrix: \n" << T.matrix() << endl;
    T.pretranslate(Eigen::Vector3d(1, 3, 4));  // translate by (1, 3, 4);
    cout << "Transformation matrix: \n" << T.matrix() << endl;

    // coordinate transformation with Transformation matrix
    Eigen::Vector3d v_transformed = T*v; // Notice we don't need T.matrix()*v; nor need extend v to be 4x1
    cout << "v transformed: " << v_transformed.transpose() << endl;

    // Eigen::Affine3d and Eigen::Projective3d
    // TODO

    // Quaternion
    // from AngleAxis
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    cout << "quaternions: \n" << q.coeffs().transpose() << endl;
    // notice, this order is (x, y, z, w) with imaginary coefficients first
    // while in constructing Quaternion from coefficients the required order is (w, x, y, z)
    // based on Eigen doc; but internally the stored coefficients are in oder of (x, y, z, w) - annoying
    // from rotation matrix
    q = Eigen::Quaterniond(rotation_matrix);
    cout << "quaternions: \n" << q.coeffs().transpose() << endl;
    // use quaternion to rotate one vector
    v_rotated = q*v;  // mathematically, qvq^{-1}
    cout << "(1, 0, 0) after rotation: " << v_rotated.transpose() << endl;

    return 0;

    /* Summary of various transformation expression in Eigen
     * rotation matrix (3x3):            Eigen::Matrix3d
     * angle-axis (3x1):                 Eigen::AngleAxisd - interesting one
     * euler angles (3x1):               Eigen::Vector3d
     * quaternion (3x1):                 Eigen::Quaterniond
     * homogeneous transformation (4x4): Eigen::Isometry3d
     * affine (4x4):                     Eigen::Affine3d
     * projection (4x4):                 Eigen::Projective3d
     */
}
