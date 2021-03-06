#include <iostream>
#include <vector>

using namespace std;

// DEFAULT SIZE:
const int ROW_NO = 2;
const int COL_NO = 2;

// Should the user input an out-of-bound index to access elements of matrices, this exception will be thrown
class BadRangeInput {};

class Matrix
{
	int row_no;
	int col_no;
	vector< vector<int> > elements;
public:
	Matrix(int _row_no, int _col_no);
	Matrix(int _row_no, int _col_no, vector< vector<int> >& _elements);
	void set_element(int i, int j, int x);

	Matrix operator+(const Matrix& m2) const;
	Matrix operator-(const Matrix& m2) const;
	Matrix operator*(const Matrix& m2) const;
	Matrix operator*(int a) const;
	friend ostream& operator<<(ostream& os, Matrix& m);
	Matrix transpose();	//operator!() for inverse or transpose

	vector<int> operator[](int i);	//returns row
	int operator()(int i, int j); //returns element m[i][j]

	// Checkers:
	friend bool out_of_bound_row(int r, Matrix* m);
	friend bool out_of_bound_col(int c, Matrix* m);

	// Getters:
	int get_row_no() { return row_no; }
	int get_col_no() { return col_no; }
	vector< vector<int> > get_elements() {return elements;}
};

bool out_of_bound_row(int r, Matrix* m) {return (r < 0 || m->elements.size() - 1 < r) ? true : false;}
bool out_of_bound_col(int c, Matrix* m) {return (c < 0 || m->elements[0].size() - 1 < c) ? true : false;}

int Matrix::operator()(int i, int j)
{
	if (out_of_bound_row(i, this) || out_of_bound_col(j, this))
	{
		throw BadRangeInput();
	}
	return elements[i][j];
}

vector<int> Matrix::operator[](int i)
{
	if (out_of_bound_row(i, this))
	{
		throw BadRangeInput();
	}
	return elements[i];
}

void input_elements(int r, int c, vector< vector<int> >& v);
Matrix build_matrix(int row_no, int col_no);

int main()
{
	cout << "***MATRICES!***\n";
	int row, col;

	cout << "Size of matrix1:\n";
	cin >> row >> col;
	Matrix a = build_matrix(row, col);

		cout << "Size of matrix2:\n";
		cin >> row >> col;
		Matrix b = build_matrix(row, col);

		Matrix answer1 = a + b;
		Matrix answer2 = a - b;
		Matrix answer3 = a * b;

		cout << answer1 << endl << answer2 << endl << answer3 << endl;

		// Matrix transpose(row, col);
		Matrix transpose_a = a.transpose();
		Matrix transpose_b = b.transpose();

		cout << transpose_a << endl << transpose_b;

	int multiplier;
	cout << "Enter a multiplier: ";
	cin >> multiplier;
	Matrix product = a * multiplier;
	cout << product;

	cout << "What row wish you have?\n";
	int selected_row;
	cin >> selected_row;
	try
	{
		vector<int> sel_row = a[selected_row];
		cout << "Matrix1[" << selected_row << "]: ";
		for (size_t i = 0; i < sel_row.size(); i++) {
			cout << sel_row[i] << ' ';
		}
		cout << endl;
	}
	catch (BadRangeInput b)
	{
		cerr << "Only input ranges within the size of your matrix!\n";
	}

	cout << "Enter the row and then the column of the element you desire: \n";
	int i, j;
	cin >> i >> j;

	try
	{
		cout << "Matrix1[" << i << "][" << j << "]: " << a(i, j) << endl;
	}
	catch (BadRangeInput b)
	{
		cerr << "Only input ranges within the size of your matrix!\n";
	}
	return 0;
}

// Operations
	// TODO: Handle size issues with m
	Matrix Matrix::operator+(const Matrix& m) const
	{
		Matrix sum(row_no, col_no);
		for (int i = 0; i < row_no; ++i)
		{
			for (int j = 0; j < col_no; ++j)
			{
				sum.elements[i][j] = elements[i][j] + m.elements[i][j];
			}
		}
		return sum;
	}

	Matrix Matrix::operator-(const Matrix& m) const
	{
		//TODO: Handle size issues with m
		Matrix sum(row_no, col_no);
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
		Matrix product(row_no, col_no); // By default its elements are all 0
		for (int i = 0; i < row_no; ++i)
			for (int j = 0; j < col_no; ++j)
				for (int k = 0; k < row_no; ++k)
					product.elements[i][j] += elements[i][k] * m.elements[k][j];

		return product;
	}

	Matrix Matrix::operator*(int a) const
	{
		Matrix product(row_no, col_no); // By default its elements are all 0
		for (int i = 0; i < row_no; ++i)
			for (int j = 0; j < col_no; ++j)
				product.elements[i][j] += elements[i][j] * a;

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
			// For aligning all elements:
			if (0 <= elements[i][j] && elements[i][j] < 10)
				os << ' ';
			os << elements[i][j] << ' ';
		}
		os << endl;
	}
	return os;
}

Matrix Matrix::transpose()
{
	if (row_no != col_no)
	{
		cout << "Matrix has to be a square matrix in order to have a transpose matrix";
		exit(0);
	}

	vector<vector<int> > transpose_elements = elements;
	for (int i = 0; i < row_no; ++i)
	{
		for (int j = i + 1; j < col_no; ++j)
		{
			int temp = transpose_elements[i][j];
			transpose_elements[i][j] = transpose_elements[j][i];
			transpose_elements[j][i] = temp;
		}
	}
	return Matrix(row_no, col_no, transpose_elements);
}


// Other methods
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

Matrix::Matrix(int _row_no, int _col_no, vector< vector<int> >& _elements)
{
	row_no = _row_no;
	col_no = _col_no;
	elements = _elements;
}

void Matrix::set_element(int i, int j, int x)
{
	if (out_of_bound_row(i, this) || out_of_bound_col(j, this))
	{
		throw BadRangeInput();
	}
	elements[i][j] = x;
}

Matrix build_matrix(int row_no, int col_no)
{
	cout << "Enter the elements of matrix:\n";
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
