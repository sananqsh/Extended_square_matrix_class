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
Matrix build_matrix();

int main() 
{
	cout << "***MATRICES!***\n";

	cout << "You can do the following opperations(type each to select):\n";
	cout << "**************************\n";
	cout << "**\tAdd\t\t**\n**	Substract	**\n**	Multiplate	**\n";
	cout << "**************************\n";
	string command;
	
	Matrix a, b, answer;
	
	while(true)
	{
		getline(cin, command);
		
		if (command == "Add")
		{
			cout << "Enter two matrices with size 2x2:\n";
			a = build_matrix();
			b = build_matrix();
			answer = a + b;
			answer.print();
			return 0;
		}

		else if (command == "Substract")
		{
			cout << "Enter two matrices with size 2x2:\n";
			a = build_matrix();
			b = build_matrix();
			answer = a - b;
			answer.print();
			return 0;
		}

		else if (command == "Multiplate")
		{
			cout << "Enter two matrices with size 2x2:\n";
			a = build_matrix();
			b = build_matrix();
			answer = a * b;
			answer.print();
			return 0;
		}

		else
		{
			cout << "Invalid command.\n";
		}
	}
	
	return 0;
}

Matrix build_matrix()
{
	// cout << "Enter the elements of first matrix:\n";
	vector< vector<int> > els(ROW_NO);
	input_elements(ROW_NO, COL_NO, els);

	Matrix t(ROW_NO, COL_NO, els);
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