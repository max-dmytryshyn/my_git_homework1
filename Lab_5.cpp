#include "iostream"
#include "vector"
#include "iomanip"
using Matrix = std::vector<std::vector<int>>;

std::ostream& operator<<(std::ostream& os, std::vector<int>& vec) {
    int size = vec.size();
    for (int i = 0; i < size; i++) {
            os << std::setw(3) << vec[i];
            os << ' ';
    }
    os << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            is >> matrix[i][j];
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Matrix& matrix) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    for (int i = 0; i < rows; i++) {
        os << matrix[i];
    }
    return os;
}

void merge_halves_of_vector(std::vector<int>& vec, int start_of_vector, int middle_of_vector, int end_of_vector) {
    int first_half_of_vector_size = middle_of_vector - start_of_vector + 1;
    int second_half_of_vector_size = end_of_vector - middle_of_vector;
    std::vector<int> first_half_of_vector(first_half_of_vector_size);
    std::vector<int> second_half_of_vector(second_half_of_vector_size);
    for (int i = 0; i < first_half_of_vector_size; i++) {
        first_half_of_vector[i] = vec[start_of_vector + i];
    }
    for (int i = 0; i < second_half_of_vector_size; i++) {
        second_half_of_vector[i] = vec[i + middle_of_vector + 1];
    }
    int index_of_element_in_first_half = 0,
    index_of_element_in_second_half = 0;
    for (int i = start_of_vector; i <= end_of_vector; i++) {
        if (index_of_element_in_first_half >= first_half_of_vector_size) {
            vec[i] = second_half_of_vector[index_of_element_in_second_half];
            index_of_element_in_second_half++;
            continue;
        }
        if(index_of_element_in_second_half >= second_half_of_vector_size){
            vec[i] = first_half_of_vector[index_of_element_in_first_half];
            index_of_element_in_first_half++;
            continue;
        }
        if (first_half_of_vector[index_of_element_in_first_half] <= second_half_of_vector[index_of_element_in_second_half]) {
            vec[i] = first_half_of_vector[index_of_element_in_first_half];
            index_of_element_in_first_half++;
        }
        else {
            vec[i] = second_half_of_vector[index_of_element_in_second_half];
            index_of_element_in_second_half++;
        }
    }
}

void merge_sort_vector(std::vector<int>& vec, int start_of_vector, int end_of_vector) {
    if (start_of_vector < end_of_vector) {
        int middle_of_vector = start_of_vector + (end_of_vector - start_of_vector) / 2;
        merge_sort_vector(vec, start_of_vector, middle_of_vector);
        merge_sort_vector(vec, middle_of_vector + 1, end_of_vector);
        merge_halves_of_vector(vec, start_of_vector, middle_of_vector, end_of_vector);
    }
}

void merge_sort_matrix_in_rows(Matrix& matrix){
    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        merge_sort_vector(matrix[i], 0, size - 1);
    }
}

std::vector<int> calculate_sums_of_elements_over_side_diagonal_in_rows(Matrix matrix) {
    int size = matrix.size();
    std::vector<int> result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            result[i] += matrix[j][i];
        }
    }
    return result;
}
double geometric_mean_of_vector_elements(std::vector<int> vec) {
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
    merge_sort_matrix_in_rows(matrix);
    std::cout << matrix << '\n';
    std::vector<int> sums_of_elements_over_side_diagonal = calculate_sums_of_elements_over_side_diagonal_in_rows(matrix);
    std::cout << sums_of_elements_over_side_diagonal << '\n';
    std::cout << geometric_mean_of_vector_elements(sums_of_elements_over_side_diagonal) << '\n';
    return 0;
}
