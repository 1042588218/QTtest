#include <iostream>
#include <string>

class Shape
{
public:

	void SetColor(int c)
	{
		color = c;
	}
	int GetColor() const
	{
		return color;
	}

	virtual void Draw() const = 0;
	virtual ~Shape() = 0 { std::cout << "Shape::~Shape()" << std::endl; };
protected:
	int color;
};

class Triangle : public Shape
{
public:
	void Draw() const
	{
		std::cout << "绘制三角型" << std::endl;
	}

	~Triangle()
	{
		std::cout << "Triangle::~Triangle()" << std::endl;
	}
};

class Rect : public Shape
{
public:
	void Draw() const {
		std::cout << "绘制矩形" << std::endl;
	}
};

class Circular :public Shape
{
public:
	void Draw() const {
		std::cout << "绘制圆" << std::endl;
	}
};

class Square : public Shape
{
public:
	void Draw() const {
		std::cout << "Draw Square" << std::endl;
	} 
};


template <typename T>
void DrawShapeT(const T* psh)
{
	if (psh != nullptr)
		psh->Draw();
}

void DrawShape(Shape* *p, int size)
{
	if (p != nullptr)
	{
		for (int index = 0; index < size; ++index)
		{
			p[index]->Draw();
		}
	}
}

int main()
{
	/*Triangle t;
	Rect     r;
	Circular c;
	Square   s;

	Shape* array[4] = { &t, &r, &c, &s };

	DrawShape(array, 4);

	std::cout << "#########################################\n";

	DrawShapeT(&t);
	DrawShapeT(&r);
	DrawShapeT(&c);
	DrawShapeT(&s);*/

	Shape *pSh = new Triangle;

	pSh->Draw();

	delete pSh;
	
	Triangle t;

	std::cout << t << std::endl;
	//<<((<< (cout, t)), std::endl)
	
	return 0;
}