#include "Matrix.hpp"
#include "ConstMatrix.hpp"
#include <iostream>

using namespace Lab3;

template class Matrix<std::string>;
template class Matrix<int>;
template class ConstMatrix<int, 4, 4>;

void constMatrixTest() {
	std::cout << "\nConst matrix test:\n";

	ConstMatrix<int, 4, 4> matrix{
		1, 2, 3, 4,
		4, 2, 3, 4,
		3, 0, 3, 4,
		1, 2, 1, 4
	};
	std::cout << "\nBefore rows sort:\n" << matrix;
	matrix.sortRows();
	std::cout << "\nAfter rows sort:\n" << matrix << '\n';

	ConstMatrix<int, 4, 4> matrix1{
		1, 2, 3, 4,
		4, 2, 3
	};

	std::cout << "\nMatrix1:\n" << matrix;
	std::cout << "\nMatrix2:\n" << matrix1;
	std::cout << "\nSum:\n" << matrix + matrix1 << '\n';

}

void matrixTest() {
	std::cout << "\nMatrix test:\n";

	srand(time(0));

	Matrix<int> matrix(3, 4);
	for (size_t i = 0; i < matrix.rows(); ++i)
		for (size_t j = 0; j < matrix.cols(); ++j)
			matrix[i][j] = rand() % 20;

	std::cout << "\nBefore cols sort:\n" << matrix;
	matrix.sortCols();
	std::cout << "\nAfter cols sort:\n" << matrix << '\n';

	Matrix<int> matrix1(3, 4);
	for (size_t i = 0; i < matrix1.rows(); ++i)
		for (size_t j = 0; j < matrix1.cols(); ++j)
			matrix1[i][j] = rand() % 10;

	std::cout << "\nMatrix1:\n" << matrix;
	std::cout << "\nMatrix2:\n" << matrix1;

	Matrix<int> diff{ std::move(matrix - matrix1) };
	std::cout << "\nDiff:\n"	<< diff << '\n';

	diff.resize(2, 2);
	diff[0][0] = 3;
	diff[1][1] = 4;

	std::cout << "\nResized:\n" << diff << '\n';
}

int main()
{
	matrixTest();
	constMatrixTest();
	return 0;
}
