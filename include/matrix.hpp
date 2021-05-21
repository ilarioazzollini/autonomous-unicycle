#pragma once

struct Matrix {
public:
    Matrix(size_t rows_n, size_t columns_n){
        m_rows_n = rows_n;
        m_columns_n = columns_n;

        for (size_t i=0;i<rows_n;i++) {
            std::vector<double> row_vec;

            for (size_t j=0;j<columns_n;j++){
                row_vec.push_back(0);
            }
            m_matrix.push_back(row_vec);
        }
    }

    std::vector<double>& operator[](size_t row_index)
    {
        return m_matrix[row_index];
    }

    size_t rows()
    {
        return m_rows_n;
    }

    size_t columns()
    {
        return m_columns_n;
    }

    double get(size_t row, size_t column){
        double element = m_matrix[row][column];
        return element;
    }

    void set(size_t row, size_t column, double entry){
        m_matrix[row][column] = entry;
    }

    void fill(double entry){
        for (size_t i=0;i<m_rows_n;i++) {
            for (size_t j=0;j<m_columns_n;j++){
                this->set(i,j,entry);
            }
        }
    }

private:
    size_t m_rows_n;
    size_t m_columns_n;
    std::vector<std::vector<double>> m_matrix;
};

inline std::ostream &operator<<(std::ostream &outstr, Matrix matrix)
{
    for (size_t i = 0; i < matrix.rows(); i++) {
        outstr << "[";
        for (size_t j = 0; j < matrix.columns(); j++){
            outstr<<" " << matrix[i][j];
        }
        outstr << " ]";
    }

    return outstr;
};
