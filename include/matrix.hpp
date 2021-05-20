#pragma once

struct Matrix {
    public:
    Matrix(int rows_n,int columns_n){
        m_rows_n = rows_n;
        m_columns_n = columns_n;

        for (int i=0;i<rows_n;i++) {
            std::vector<double> row_vec;

            for (int j=0;j<columns_n;j++){
                row_vec.push_back(0);
            }
            m_matrix.push_back(row_vec);
        }
    }

    double get(int row,int column){
        double element = m_matrix[row][column];
        return element;
    }

    void set(int row,int column,double entry){
        m_matrix[row][column] = entry;
    }

    void fill(double entry){
        for (int i=0;i<m_rows_n;i++) {
            for (int j=0;j<m_columns_n;j++){
                this->set(i,j,entry);
            }
        }
    }

    private:
    int m_rows_n;
    int m_columns_n;
    std::vector<std::vector<double>> m_matrix;
};