#include <iostream>
#include <vector>

using namespace std;

//DEFAULT SIZE:
const int ROW_NO = 2;
const int COL_NO = 2;

class Matrix
{
	int row_no;
	int col_no;
	vector< vector<int> > elements;
public:
	Matrix();
	Matrix(int _row_no, int _col_no, vector< vector<int> >& _elements);
	Matrix(int _row_no, int _col_no);
	int get_row_no() { return row_no; }
	int get_col_no() { return col_no; }
	void set_element(int i, int j, int x);
	Matrix operator+(const Matrix& m2) const;
	Matrix operator-(const Matrix& m2) const;
	Matrix operator*(const Matrix& m2) const;
	void print();
};

Matrix::Matrix() //default constructor
{
	row_no = ROW_NO;
	col_no = COL_NO;
	elements = { {0,0} , {0,0} };
}

//we take the vector by reference for better performance
Matrix::Matrix(int _row_no, int _col_no, vector< vector<int> >& _elements)
{
	row_no = _row_no;
	col_no = _col_no;
	elements = _elements;
}

Matrix::Matrix(int _row_no, int _col_no)
{
	row_no = _row_no;
	col_no = _col_no;

	// To prevent segmentation fault
	vector<vector<int> > temp(row_no);
	elements = temp;

	for (int i = 0; i < row_no; ++i)
	{
		for (int i = 0; i < col_no; ++i)
		{
			elements[i].push_back(0);
		}
	}
}

void Matrix::set_element(int i, int j, int x) { elements[i][j] = x; }

Matrix Matrix::operator+(const Matrix& m2) const
{
	//TODO: handle size issues with m2
	Matrix sum;
	for (int i = 0; i < row_no; ++i)
	{
		for (int j = 0; j < col_no; ++j)
			sum.elements[i][j] = elements[i][j] + m2.elements[i][j];
	}

	return sum;
}

Matrix Matrix::operator-(const Matrix& m2) const
{
	//TODO: handle size issues with m2
	Matrix sum;
	for (int i = 0; i < row_no; ++i)
	{
		for (int j = 0; j < col_no; ++j)
			sum.elements[i][j] = elements[i][j] - m2.elements[i][j];
	}

	return sum;
}

Matrix Matrix::operator*(const Matrix& m2) const
{
	 //if all Matrix have 2rows and cols
	Matrix product; //by default its elements are all 0
	for (int i = 0; i < row_no; ++i)
		for (int j = 0; j < col_no; ++j)
			for (int k = 0; k < row_no; ++k)
				product.elements[i][j] += elements[i][k] * m2.elements[k][j];				

	return product;
}

void Matrix::print()
{
	for (int i = 0; i < row_no; ++i)
	{
		for (int j = 0; j < col_no; ++j)
		{
			if (elements[i][j] < 10)
				cout << ' ';
			cout << elements[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void input_elements(int r, int c, vector< vector<int> >& v);
Matrix build_matrix(int row_no, int col_no);

int main() 
{
	cout << "***MATRICES!***\n";
	int row, col;

	cout << "Size of matrix1:\n";	cin >> row >> col;
	Matrix a = build_matrix(row, col);

	cout << "Size of matrix2:\n";	cin >> row >> col;
	Matrix b = build_matrix(row, col);

	Matrix answer(row, col);

	answer = a + b;
	answer.print();

	answer = a - b;
	answer.print();

	answer = a * b;
	answer.print();

	
	return 0;
}

Matrix build_matrix(int row_no, int col_no)
{
	cout << "Enter the elements of first matrix:\n";
	vector< vector<int> > els(row_no);
	input_elements(row_no, col_no, els);

	Matrix t(row_no, col_no, els);
	return t;
}

void input_elements(int r, int c, vector< vector<int> >& v)
{
	int x;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			cin >> x;
			v[i].push_back(x);
		}
	}
	return;
}