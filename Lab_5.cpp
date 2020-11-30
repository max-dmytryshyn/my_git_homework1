#include "iostream"
#include "vector"
#include "iomanip"
using Matrix = std::vector<std::vector<int>>;
std::istream& operator>>(std::istream& is, Matrix& m) {
	int rows = m.size();
	int columns = m[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			is >> m[i][j];
		}
	}
	return is;
}
std::ostream& operator<<(std::ostream& os, Matrix m) {
	int rows = m.size();
	int columns = m[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			os << std::setw(3) << m[i][j];

			os << ' ';
		}
		os << '\n';
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, std::vector<int> v) {
	int size = v.size();
	for (int i = 0; i < size; i++) {
			os << std::setw(3) << v[i];
			os << ' ';
	}
	os << '\n';
	return os;
}
void merge(std::vector<int>& vec, int start, int middle, int end) {
	int n1 = middle - start + 1;
	int n2 = end - middle;
	std::vector<int> a(n1);
	std::vector<int> b(n2);
	for (int i = 0; i < n1; i++) {
		a[i] = vec[start + i];
	}
	for (int i = 0; i < n2; i++) {
		b[i] = vec[i + middle + 1];
	}
	int k = 0, m = 0;
	for (int i = start; i <= end; i++) {
		if (k >= n1) {
			vec[i] = b[m];
			m++;
			continue;
		}
		if(m >= n2){
			vec[i] = a[k];
			k++;
			continue;
		}
		if (a[k] <= b[m]) {
			vec[i] = a[k];
			k++;
		}
		else {
			vec[i] = b[m];
			m++;
		}
	}
}
void merge_sort(std::vector<int>& vec, int start, int end) {
	if (start < end) {
		int m = start + (end - start) / 2;
		merge_sort(vec, start, m);
		merge_sort(vec, m + 1, end);
		merge(vec, start, m, end);
	}
}
std::vector<int> f(Matrix m) {
	int size = m.size();
	std::vector<int> result(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			result[i] += m[j][i];
		}
	}
	return result;
}
double F(std::vector<int> vec) {
	double product = 1;
	int size = vec.size() - 1;
	for (int i = 0; i < size; i++) {
		product = product*vec[i];
		if (vec[i] == 0)
			return 0;
	}
	if (product < 0) {
		return 0;
	}
	return pow(product, 1 / (double)size);
}
int main() {
	Matrix matrix(5, std::vector<int>(5));
	std::cin >> matrix;
	std::cout << '\n' << matrix << '\n';
	int size = matrix.size();
	for (int i = 0; i < size; i++) {
		merge_sort(matrix[i], 0, size - 1);
	}
	std::cout << matrix << '\n';
	std::cout << f(matrix) << '\n';
	std::cout << F(f(matrix));
	return 0;
}