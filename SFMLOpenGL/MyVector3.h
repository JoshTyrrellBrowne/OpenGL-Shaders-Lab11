#ifndef MYVECTOR3 
#define MYVECTOR3


/// <summary>
/// Josh Tyrrell Browne
/// 

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector3
{
public:
	double x;
	double y;
	double z;

	MyVector3();
	~MyVector3();
	std::string toString();

	// Constructor taking three doubles
	MyVector3(double x, double y, double z);

	// Constructor taking a SFML vector3f
	MyVector3(sf::Vector3f t_sfVector);

	// Constructor taking a SFML vector3i
	MyVector3(sf::Vector3i t_sfVector);

	// Constructor taking a SFML vector2i
	MyVector3(sf::Vector2i t_sfVector);

	// Constructor taking a SFML vector2i
	MyVector3(sf::Vector2u t_sfVector);

	// Constructor taking a SFML vector2f
	MyVector3(sf::Vector2f t_sfVector);

	// Equality operater (true if same vectors)
	bool operator == (const MyVector3 t_right) const;

	// Inequality operater (true if vectors are not the same)
	bool operator != (const MyVector3 t_right) const;

	// overload for plus operator add the x component of the current vector 
	// with the operand on the right and return a new myVector2 using the sums
	// this a const operation becuase the orignal vector never changes
	MyVector3 operator +(const MyVector3 t_right) const;

	// overload for subtraction of Vectors
	MyVector3 operator -(const MyVector3 t_right) const;

	//Multiply by double
	MyVector3 operator *(const double t_scalar) const;

	//Divide by double
	MyVector3 operator /(const double t_divisor) const;

	// plus equals operator
	MyVector3 operator +=(const MyVector3 t_right);

	// minus equals operator
	MyVector3 operator -=(const MyVector3 t_right);


	// negative of a vector 
	MyVector3 operator -();

	// length of vector
	double length()const;

	// lenght squared of vector
	double lengthSquared()const;

	// dot product of two vectors
	double dot(const MyVector3 t_other) const;

	// cross product of two vectors
	MyVector3 crossProduct(const MyVector3 t_other)const;   // not finished

															// angle between two vectors
	double angleBetween(const MyVector3 t_other)const;

	// unit
	// get a normal vector for the current vector
	// null vector in null vector out : cause Pete said so
	MyVector3 unit() const;      //a new vector of lenght 1

								 // Change the lenght of this vector to 1
								 // Null vector in null vector out : cause Pete said so
	void normalise();

	// Project the other vector onto this vector
	MyVector3 projection(const MyVector3 t_other)const;


	// projection of other onto the current vector so answer will parralell to current vector.
	MyVector3 rejection(const MyVector3 t_other)const;




	operator sf::Vector2f() { return sf::Vector2f{ static_cast<float>(x), static_cast<float>(y) }; };
	operator sf::Vector2i() { return sf::Vector2i{ static_cast<int>(x), static_cast<int>(y) }; };
	operator sf::Vector2u();
	operator sf::Vector3i() { return sf::Vector3i{ static_cast<int>(x), static_cast<int>(y), static_cast<int>(z) }; };
	operator sf::Vector3f() { return sf::Vector3f{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) }; };

	// new methods for bouncing off cushions on billiards
	void reverseX();
	void reverseY();

};



#endif // !MYVECTOR3
