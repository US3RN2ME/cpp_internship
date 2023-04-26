#include "Matrix.hpp"
#include "ConstMatrix.hpp"
#include <iostream>

using namespace Lab3;

template class Matrix<std::string>;
template class Matrix<int>;
template class ConstMatrix<int, 4, 4>;


int main()
{
	return 0;
}
