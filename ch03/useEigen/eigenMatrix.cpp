#include <iostream>
#include <ctime>
using namespace std;

// for Eigen
#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

/*
* Demo of basic use for Eigen
*/
int main(int argc, char** argv)
{
	// The basic unit in Eigen is matrix, which is a template class,
	// the first 3 parameters: data type, row, column
	Eigen::Matrix<float, 2, 3> matrix_23;

	// with typedef, Eigen provides many embedded types, but behind
	// it's still Eigen::Matrix
	// e.g. Vector3d is Eigen::Matrix<double, 3, 1>
	// e.g. Matrix3d is Eigen::Matrix<double, 3, 3>
	Eigen::Vector3d v_3d;
	Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero(); // 0-initialization

	// If not sure about matrix size, it can be dynamically allocated
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
	// or simplier
	Eigen::MatrixXd matrix_x;

	matrix_23 << 1, 2, 3, 4, 5, 6;
	cout << matrix_23 << endl;

	// use () to access matrix element
	for (int i = 0; i < 1; ++i)
		for (int j = 0; j < 2; ++j)
			cout << matrix_23(i, j) << endl;

	v_3d << 3, 2, 1;

	// multiply matrix and vector - type mixing is wrong
    //Eigen::Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;

	// should cast
	Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
	cout << result << endl;

	// size shouldn't be wrong
    //Eigen::Matrix<double, 3, 1> result_wrong_dimension = matrix_23.cast<double>() * v_3d;

	// some typical matrix operation
    matrix_33 = Eigen::Matrix3d::Random();
	cout << matrix_33 << endl << endl;

	cout << matrix_33.transpose() << endl;
	cout << matrix_33.sum() << endl;
	cout << matrix_33.trace() << endl;
	cout << 10*matrix_33 << endl;
	cout << matrix_33.inverse() << endl;
	cout << matrix_33.determinant() << endl;

	// Eigen
	// real symmetric matrix coudl be guaranteed being diagonalized
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose()
		*matrix_33);
	cout << "Eigen values: " << eigen_solver.eigenvalues() << endl;
	cout << "Eigen vectors: " << eigen_solver.eigenvectors() << endl;

	// solve Ax = b
	Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
	matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
	Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd;
	v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

	clock_t time_stt = clock();
	// solve directly, but inverse calculation is consuming
	Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
	cout << "time used in normal inverse is: " << 1000*(clock() - time_stt)/
	(double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "Result with normal inverse: " << x.transpose() << endl;

	// matrix decomposition is faster
	time_stt = clock();
	x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
	cout << "time used in QR decomposition is: " << 1000*(clock() - time_stt)/
	(double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "Result with Qr: " << x.transpose() << endl;

	return 0;
}
