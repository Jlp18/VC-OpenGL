class Point2
{
public:
	Point2();
	Point2(float, float);
public:
	float x;
	float y;
};

Point2::Point2() :x(0), y(0){}
Point2::Point2(float xx, float yy) : x(xx), y(yy){}