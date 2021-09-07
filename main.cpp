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
	Matrix(int _row_no, int _col_no);
	Matrix(int _row_no, int _col_no, vector< vector<int> >& _elements);
	void set_element(int i, int j, int x);
	Matrix operator+(const Matrix& m2) const;
	Matrix operator-(const Matrix& m2) const;
	Matrix operator*(const Matrix& m2) const;
	friend ostream& operator<<(ostream& os, Matrix& m);

	//getters:
	int get_row_no() { return row_no; }
	int get_col_no() { return col_no; }
	vector< vector<int> > get_elements() {return elements;}
};

Matrix::Matrix() //default constructor
{
	row_no = ROW_NO;
	col_no = COL_NO;
	elements = { {0,0} , {0,0} };
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

//we take the vector by reference for better performance
Matrix::Matrix(int _row_no, int _col_no, vector< vector<int> >& _elements)
{
	row_no = _row_no;
	col_no = _col_no;
	elements = _elements;
}

void Matrix::set_element(int i, int j, int x) { elements[i][j] = x; }

Matrix Matrix::operator+(const Matrix& m) const
{
	//TODO: handle size issues with m
	Matrix sum;
	for (int i = 0; i < row_no; ++i)
	{
		for (int j = 0; j < col_no; ++j)
			sum.elements[i][j] = elements[i][j] + m.elements[i][j];
	}

	return sum;
}

Matrix Matrix::operator-(const Matrix& m) const
{
	//TODO: handle size issues with m
	Matrix sum;
	for (int i = 0; i < row_no; ++i)
	{
		for (int j = 0; j < col_no; ++j)
			sum.elements[i][j] = elements[i][j] - m.elements[i][j];
	}

	return sum;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	// If all Matrix have 2rows and cols
	Matrix product; // By default its elements are all 0
	for (int i = 0; i < row_no; ++i)
		for (int j = 0; j < col_no; ++j)
			for (int k = 0; k < row_no; ++k)
				product.elements[i][j] += elements[i][k] * m.elements[k][j];				

	return product;
}

ostream& operator<<(ostream& os, Matrix& m)
{
	vector< vector<int> >  elements = m.get_elements();
	int row_no = m.get_row_no();
	int col_no = m.get_col_no();

	for (int i = 0; i < row_no; ++i)
	{
		for (int j = 0; j < col_no; ++j)
		{
			if (elements[i][j] < 10)
				os << ' ';
			os << elements[i][j] << ' ';
		}
		os << endl;
	}
	// cout << endl;
	return os;
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

	Matrix answer1(row, col), answer2(row, col), answer3(row, col);

	answer1 = a + b;
	answer2 = a - b;
	answer3 = a * b;

	cout << answer1 << endl << answer2 << endl << answer3 << endl;

	
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