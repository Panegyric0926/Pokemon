#include <iostream>
#include <math.h>
#include <stdlib.h>

#define PI acos(-1)

using namespace std;

class Matrix
{
private:
	int matrix[4][5];
public:
	Matrix()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				matrix[i][j] = 0;
		}
	}
	~Matrix(){}
	void input() 
	{
		cout << "�����������ֵ��" << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				cin >> matrix[i][j];
		}
	}
	void output()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				cout << matrix[i][j] << " ";
			cout << endl;
		}
	}
	Matrix operator+(Matrix& A2)
	{
		Matrix sum;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				sum.matrix[i][j] = matrix[i][j] + A2.matrix[i][j];
		}
		return sum;
	}
	Matrix operator-(Matrix& A2)
	{
		Matrix differ;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				differ.matrix[i][j] = matrix[i][j] - A2.matrix[i][j];
		}
		return differ;
	}
};

class Point
{
private:
	double x; double y;
public:
	Point(double a = 0, double b = 0)
	{
		x = a; y = b;
	}
	~Point()
	{
		cout << "Class Point's destructor is called." << endl;
	}
	void output()
	{
		cout << "��" << x << "," << y << ")" << endl;
	}
	double getDistance(Point& p2)
	{
		return sqrt(pow((x - p2.x), 2) + pow((y - p2.y), 2));
	}
};

class Circle
{
private:
	Point centre;
	double radius;
public:
	Circle()
	{
		double a, b, r;
		cout << "������Բ�����꣺" << endl;
		cin >> a >> b;
		cout << "������뾶��" << endl;
		cin >> r;
		centre = Point(a, b);
		radius = r;
	}
	~Circle()
	{
		cout << "Class Circle's destructor is called." << endl;
	}
	bool isIntersect(Circle& c2)
	{
		double distance = centre.getDistance(c2.centre);
		if (distance == 0)
			return false;
		return (distance < (radius + c2.radius)) ? true : false;
	}
};

class Matrix2
{
private:
	int line; int row;
	int** matrix;
public:
	Matrix2(int a, int b)
	{
		line = a; row = b;
		matrix = new int* [line];
		for (int i = 0; i < line; i++)
			matrix[i] = new int[row];
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				matrix[i][j] = 0;
		}
	}
	Matrix2(Matrix2& A2)
	{
		line = A2.line; row = A2.row;
		matrix = new int* [line];
		for (int i = 0; i < line; i++)
			matrix[i] = new int[row];
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				matrix[i][j] = A2.matrix[i][j];
		}
	}
	~Matrix2()
	{
		for (int i = 0; i < line; i++)
			delete[]matrix[i];
		delete[]matrix;
	}
	void input()
	{
		cout << "�����������ֵ��" << endl;
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				cin >> matrix[i][j];
		}
	}
	void output()
	{
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				cout << matrix[i][j] << " ";
			cout << endl;
		}
	}
	Matrix2 operator+(Matrix2& A2)
	{
		Matrix2 sum = Matrix2(line,row);
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				sum.matrix[i][j] = matrix[i][j] + A2.matrix[i][j];
		}
		return sum;
	}
	Matrix2 operator-(Matrix2& A2)
	{
		Matrix2 differ = Matrix2(line, row);
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				differ.matrix[i][j] = matrix[i][j] - A2.matrix[i][j];
		}
		return differ;
	}
	void operator=(Matrix2& A2)
	{
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < row; j++)
				matrix[i][j] = A2.matrix[i][j];
		}
	}
};

class Shape
{
public:
	Shape(){}
	~Shape()
	{
		cout << "Class Shape's destructor is called." << endl;
	}
	virtual double getArea() = 0;
};

class Rectangle : public Shape
{
private:
	double length; double width;
public:
	Rectangle(double l = 0, double w = 0)
	{
		length = l; width = w;
	}
	~Rectangle()
	{
		cout << "Class Rectangle's destructor is called." << endl;
	}
	double getArea()
	{
		return length * width;
	}
};

class Circle2 : public Shape
{
private:
	double radius;
public:
	Circle2(double r = 0)
	{
		radius = r;
	}
	~Circle2()
	{
		cout << "Class Circle2's destructor is called." << endl;
	}
	double getArea()
	{
		return PI * pow(radius, 2);
	}
};

class Square : public Rectangle
{
private:
	double length;
public:
	Square(double l = 0)
	{
		length = l;
	}
	~Square()
	{
		cout << "Class Square's destructor is called." << endl;
	}
	double getArea()
	{
		return length * length;
	}
};

class Point2
{
private:
	double x; double y;
public:
	Point2(double a = 0, double b = 0)
	{
		x = a; y = b;
	}
	~Point2(){}
	void output()
	{
		cout << "��" << x << "," << y << ")" << endl;
	}
	Point2 operator--()
	{
		x--; y--;
		return *this;
	}
	Point2 operator--(int)
	{
		Point2 tempt = Point2(x, y);
		x--; y--;
		return tempt;
	}
	Point2 operator++()
	{
		x++; y++;
		return *this;
	}
	Point2 operator++(int)
	{
		Point2 tempt = Point2(x, y);
		x++; y++;
		return tempt;
	}
};

int main()
{
	cout << "C++����֪ʶʵ��" << endl;
	Matrix* A1, * A2, * A3;
	A1 = new Matrix; A2 = new Matrix; A3 = new Matrix;
	A1->input(); A2->input();
	cout << endl; A1->output();
	cout << endl; A2->output();
	*A3 = *A1 + *A2;
	cout << endl; A3->output();
	*A3 = *A1 - *A2;
	cout << endl; A3->output();
	delete A1; delete A2; delete A3;
	cout << endl;

	cout << "�������ʵ��" << endl;
	Circle C1 = Circle();
	Circle C2 = Circle();
	cout << "��Բ�ཻ��״̬Ϊ��" << C1.isIntersect(C2) << endl << endl;

	Matrix2 A21 = Matrix2(3, 4); A21.input();
	Matrix2 A22 = Matrix2(3, 4); A22.input();
	cout << endl; A21.output();
	cout << endl; A22.output();
	Matrix2 A23 = Matrix2(3, 4);
	A23 = A21 + A22;
	cout << endl; A23.output();
	A23 = A21 - A22;
	cout << endl; A23.output(); cout << endl;

	cout << "�̳�������ʵ��" << endl;
	Rectangle *R1 = new Rectangle(3, 4);
	cout << "�����ε�����ǣ�" << R1->getArea() << endl;
	Circle2 *C21 = new Circle2(1);
	cout << "Բ�ε�����ǣ�" << C21->getArea() << endl;
	Square *S1 = new Square(2);
	cout << "�����ε�����ǣ�" << S1->getArea() << endl;
	delete R1; delete C21; delete S1; cout << endl;

	cout << "I/O ��ʵ��" << endl;
	cout << "��������1-1000���������һ��������" << endl;
	cout << "����Ҫ������ʾ�³��������ֵĴ�С��" << endl;
	int random = rand() % 1000 + 1;
	double guess = 0;
	while (true)
	{
		cout << "�����������²�����֣�" << endl;
		cin >> guess;
		if (guess != (int)guess)
		{
			cout << "������������" << endl;
			continue;
		}
		else if (guess < 1 || guess>1000)
		{
			cout << "�����뷶Χ��1-1000֮�������" << endl;
			continue;
		}
		if (guess < random)
			cout << "���ź�������С�ˡ�" << endl;
		else if(guess > random)
			cout << "���ź������´��ˡ�" << endl;
		else
		{
			cout << "��ϲ�����¶��ˣ�" << endl;
			break;
		}
	}
	cout << endl;

	cout << "����ʵ��" << endl;
	Point2 P1 = Point2(3, 4);
	P1.output();
	P1++; P1.output();
	++P1; P1.output();
	P1--; P1.output();
	--P1; P1.output();

	return 0;
}