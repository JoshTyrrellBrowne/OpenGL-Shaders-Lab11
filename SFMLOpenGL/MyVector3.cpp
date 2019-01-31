/// <summary>
/// Vector 3 class
/// Josh Tyrrell Browne
/// </summary>
#include "MyVector3.h"
#include <string.h>
#define PI           3.14159265358979323846

/// <summary>
/// Defautl constructor set all 3 values to zero
/// </summary>
MyVector3::MyVector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyVector3::~MyVector3()
{
}

/// <summary>
/// 
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and seperated by commas</returns>
std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return output;
}

MyVector3::MyVector3(double t_x, double t_y, double t_z)
{
	x = t_x;
	y = t_y;
	z = t_z;
}

MyVector3::MyVector3(sf::Vector3f t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = static_cast<double>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector3i t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = static_cast<double>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector2i t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	// has no z because Vector2
	z = { 0.0 };
}

MyVector3::MyVector3(sf::Vector2u t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	// has no z because Vector2
	z = { 0.0 };
}

MyVector3::MyVector3(sf::Vector2f t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	// has no z because Vector2
	z = { 0.0 };
}

bool MyVector3::operator == (const MyVector3 t_right) const
{
	// if x, y & z are equal then is equal
	if (x == t_right.x && y == t_right.y && z == t_right.z)
	{
		return true;
	}
	return false;
}

bool MyVector3::operator != (const MyVector3 t_right) const
{
	// is the opposite of equality
	// return !this->operator==(t_right);
	const bool result{ x != t_right.x || y != t_right.y || z != t_right.z };        // true if vectors are not equal
	return result;
}

MyVector3 MyVector3::operator +(const MyVector3 t_right) const
{
	return MyVector3{ x + t_right.x, y + t_right.y, z + t_right.z };      // add the two vectors and return result
}

MyVector3 MyVector3::operator -(const MyVector3 t_right) const
{
	return MyVector3{ x - t_right.x, y - t_right.y, z - t_right.z };      // subtract a vector from the other
}

MyVector3 MyVector3::operator *(const double t_scalar) const
{
	return MyVector3{ x * t_scalar, y * t_scalar, z * t_scalar };
}

MyVector3 MyVector3::operator /(const double t_divisor) const
{
	if (t_divisor != 0) // don't divide by zero
	{
		return MyVector3{ x / t_divisor, y / t_divisor, z / t_divisor };
	}
	else
	{
		return MyVector3{}; // dividing by zero has no effect
	}
	return MyVector3{};
}

MyVector3 MyVector3::operator +=(const MyVector3 t_right)
{
	x += t_right.x; // update current vector as well as returning answer
	y += t_right.y;
	z += t_right.z;
	return MyVector3{ x, y, z };
}

MyVector3 MyVector3::operator -=(const MyVector3 t_right)
{
	x -= t_right.x;
	y -= t_right.y;
	z -= t_right.z;
	return MyVector3{ x, y, z };
}

MyVector3 MyVector3::operator -()
{
	return MyVector3{ -x, -y, -z };
}

double MyVector3::length()const
{
	/// get the lenght of vector using square root of components squared
	const double result = std::sqrt(x * x + y * y + z * z);
	return result;
}

double MyVector3::lengthSquared()const
{
	const double result = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2); //(x * x) + (y * y) + (z * z);
	return result;
}

double MyVector3::dot(const MyVector3 t_other) const
{
	const double result = (x * t_other.x) + (y * t_other.y) + (z * t_other.z);
	return result;
}

MyVector3 MyVector3::crossProduct(const MyVector3 t_other)const
{
	const double newX = y * t_other.z - z * t_other.y;
	const double newY = z * t_other.x - x * t_other.z;
	const double newZ = x * t_other.y - y * t_other.x;
	return MyVector3{ newX, newY, newZ };
}

double MyVector3::angleBetween(const MyVector3 t_other)const
{
	/*const double cosine = unit().dot(t_other.unit());
	const double angleInRadians = std::acos(cosine);
	const double angleInDegrees = angleInRadians * 180 / PI;
	return angleInDegrees;*/

	double top = dot(t_other);
	double under = length() * t_other.length();
	double angleRadians;

	if (under != 0)
	{
		double answer = top / under;
		if (answer > 1) answer = 1;
		if (answer < -1) answer = -1;
		angleRadians = std::acos(answer);
		const double angleDegrees = angleRadians * 180.0 / PI;
		return angleDegrees;
	}
	return 0.0; // angle with null vector is zero 
}

MyVector3 MyVector3::unit() const
{
	double returnX{ 0.0 };
	double returnY{ 0.0 };
	double returnZ{ 0.0 };
	double vectorLength = length();
	if (vectorLength != 0.0) // never divide zero 
	{
		returnX = x / vectorLength;
		returnY = y / vectorLength;
		returnZ = z / vectorLength;
	}
	return MyVector3{ returnX, returnY, returnZ };
}

void  MyVector3::normalise()
{
	double vectorLength = this->length(); // lenght changes after changing x so need to store 
	if (vectorLength != 0.0)
	{
		x = x / vectorLength;
		y = y / vectorLength;
		z = z / vectorLength;
	}
}

MyVector3 MyVector3::projection(const MyVector3 t_other)const
{
	double lengthSq = lengthSquared();
	double dotProduct = dot(t_other);
	double scale = 1.0; // default for null vector involvement
	if (lengthSq != 0)
	{
		scale = dotProduct / lengthSq;
	}
	return this->operator*(scale);
}

MyVector3 MyVector3::rejection(const MyVector3 t_other)const
{
	return MyVector3(t_other - projection(t_other));
}

MyVector3::operator sf::Vector2u()
{
	double newX{ x };
	double newY{ y };
	if (newX < 0)
	{
		newX = -newX;
	}
	if (newY < 0)
	{
		newY = -newY;
	}
	return sf::Vector2u{ static_cast<unsigned>(newX), static_cast<unsigned>(newY) };
}

// negate x so ball bounces off side cushoins
void  MyVector3::reverseX()
{
	x = -x;
}

// negate y so ball bounces off top and bottom cushions
void  MyVector3::reverseY()
{
	y = -y;
}