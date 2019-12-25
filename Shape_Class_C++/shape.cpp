
// Partners: weustis2, rmohta2

// Introduction:

// This MP was our first MP that used C++. There was a base class called Shape,
// and Shape had 4 derived classes (which were types of shapes): Rectangle, Circle, Sphere, and
// RectPrism. For the bass class and each of the derived classes, we had to first create a constructor,
// which makes a new instance of that class. For each class, we had to implement functions to get the
// area and volume of that particular shape (derived class). We also had to implement the overloading
// operations for addition and subtraction. Another function we implemented was the CreateShapes function,
// which took in a text file as an input. The text file contained information like the number of shapes,
// and the type of shape and the parameters for each of the shapes. We read the information from the file
// and stored it in a vector, which contained a list of all the shapes and their information. Finally, the
// maxVolume and maxArea functions would go through all the shapes in the vector list we returned in CreateShapes
// to determine which shape has the maximum area and which shape has the maximum volume.






#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 

Shape::Shape(string name)
{
	name_ = name;
}

string Shape::getName()
{
	return name_;
}	


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//constructor for rectangle
Rectangle::Rectangle(double width, double length):Shape("Rectangle")
{
	width_ = width;
	length_ = length;
}

//area of rectangle
double Rectangle::getArea() const
{
	return width_ * length_;
}

//volume of rectangle is 0
double Rectangle::getVolume() const
{
	return 0;
}

//add two lengths and widths of two rectangles
Rectangle Rectangle::operator + (const Rectangle& rec)
{
	Rectangle my_rectangle;
	my_rectangle.length_ = length_ + rec.length_;
	my_rectangle.width_ = width_ + rec.width_;
	return my_rectangle;
}

//subtract 2 different lengths and widths
//if statement used to make sure width or length isn't negative
Rectangle Rectangle::operator - (const Rectangle& rec)
{
	Rectangle my_rectangle;

	if(length_ - rec.length_ > 0)
		my_rectangle.length_ = length_ - rec.length_;
	else
		my_rectangle.length_ = 0;

	if(width_ - rec.width_ > 0)
		my_rectangle.width_ = width_ - rec.width_;
	else
		my_rectangle.width_ = 0;

	return my_rectangle;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//constructor for circle
Circle::Circle(double radius):Shape("Circle")
{
	radius_ = radius;
}

//area of circle
double Circle::getArea() const
{
	return M_PI*radius_*radius_;
}

//volume of circle is 0
double Circle::getVolume() const
{
	return 0;
}

//add 2 radii of 2 circles
Circle Circle::operator + (const Circle& cir)
{
	Circle my_circle = Circle(0.0);
	
	my_circle.radius_ = radius_ + cir.radius_;
	return my_circle;
}

//subtract 2 radii of 2 circles
//if statement used to make sure radius isn't negative
Circle Circle::operator - (const Circle& cir)
{
	Circle my_circle = Circle(0.0);
	
	if(radius_ - cir.radius_ > 0.0)
		my_circle.radius_ = radius_ - cir.radius_;
	else
		my_circle.radius_ = 0.0;
	
	return my_circle;
}


double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//constructor for sphere
Sphere::Sphere(double radius):Shape("Sphere")
{
	radius_ = radius;
}

//surface area of sphere
double Sphere::getArea() const
{
	return 4.0*M_PI*radius_*radius_;
}

//volume of sphere
double Sphere::getVolume() const
{
	return (4.0*M_PI*radius_*radius_*radius_)/3.0;
}

//add 2 radii of 2 spheres
Sphere Sphere::operator + (const Sphere& sph)
{
	Sphere my_sphere = Sphere(0.0);
	my_sphere.radius_ = radius_ + sph.radius_;
	return my_sphere;
}

//subtract 2 radii of 2 spheres
//if statement used to make sure radius isn't negative
Sphere Sphere::operator - (const Sphere& sph)
{
	Sphere my_sphere = Sphere(0.0);

	if(radius_ - sph.radius_ > 0.0)
		my_sphere.radius_ = radius_ - sph.radius_;
	else
		my_sphere.radius_ = 0.0;
	
	return my_sphere;
}


double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//constructor for rectprism
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism")
{
	width_ = width;
	length_ = length;
	height_ = height;
}

//surface area of RectPrism
double RectPrism::getArea() const
{
	return 2.0*length_*width_ + 2.0*length_*height_ + 2.0*width_*height_;
}

//volume of RectPrism
double RectPrism::getVolume() const
{
	return length_*width_*height_;
}

//add 2 lengths, widths, and heights of 2 RectPrisms
RectPrism RectPrism::operator + (const RectPrism& rectp)
{
	RectPrism my_prism = RectPrism(0.0, 0.0, 0.0);
	my_prism.length_ = length_ + rectp.length_;
	my_prism.width_ = width_ + rectp.width_;
	my_prism.height_ = height_ + rectp.height_;
	return my_prism;
}

//subtract 2 lengths, widths, and heights of 2 RectPrisms
//if statements used to make sure resulting length, width, and height isn't negative
RectPrism RectPrism::operator - (const RectPrism& rectp)
{
	RectPrism my_prism = RectPrism(0.0, 0.0, 0.0);
	
	if(length_ - rectp.length_ > 0.0)
		my_prism.length_ = length_ - rectp.length_;
	else
		my_prism.length_ = 0.0;
	if(width_ - rectp.width_ > 0.0)
		my_prism.width_ = width_ - rectp.width_;
	else
		my_prism.width_ = 0.0;
	if(height_ - rectp.height_ > 0.0)
		my_prism.height_ = height_ - rectp.height_;
	else
		my_prism.height_ = 0.0;

	return my_prism;
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	
	vector<Shape*> list_of_shapes; // will contain info of all the shapes
	string type_of_shape; // either "Rectangle", "Circle", "Sphere", or "RectPrism"
	int number_of_shapes; // read this from file to set up for loop
	double length = 0.0, width = 0.0, height = 0.0, radius = 0.0; // initialize to zero

	ifstream ifs (file_name, std::ifstream::in);
	ifs >> number_of_shapes; // get number of shapes from file, store it in this variable

	int i;
	for (i = 0; i < number_of_shapes; i++)
		{
			Shape *new_shape; // make a pointer to a type Shape
			ifs >> type_of_shape; // get type of shape from file, store it in this variable
			if (type_of_shape == "Rectangle")
				{
					ifs >> width >> length; // get length and width of rectangle
					new_shape = new Rectangle(width, length); // create new instance of rectangle
				}
			if (type_of_shape == "Circle")
				{
					ifs >> radius; // get radius of circle
					new_shape = new Circle(radius); // create new instance of circle
				}
			if (type_of_shape == "Sphere")
				{
					ifs >> radius; // get radius of sphere
					new_shape = new Sphere(radius); // create new instance of sphere
				}
			if (type_of_shape == "RectPrism")
				{
					ifs >> width >> length >> height; // get dimensions of rect prism
					new_shape = new RectPrism(width, length, height); // create new instance of rect prism
				}
			list_of_shapes.push_back(new_shape); // put this info in the vector, create another space for next shape
		}
	ifs.close(); // got all info from the file, we can close it
	return list_of_shapes; // return the vector that contains all the shape info
}


// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	
	int number_of_shapes = shapes.size(); //get number of shapes from vector
	int i;
	for(i = 0; i < number_of_shapes; i++)
		{
			if(shapes[i]->getArea() > max_area)
				{
					max_area = shapes[i]->getArea(); //overwrite max area if current shape is bigger
				}
		}

	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;

	int number_of_shapes = shapes.size(); //get number of shapes from vector
	int i;
	for(i = 0; i < number_of_shapes; i++)
		{
			if(shapes[i]->getVolume() > max_volume)
				{
					max_volume = shapes[i]->getVolume(); //overwrite max volume is current shape is bigger
				}
		}	

	return max_volume;
}

