/// <summary>
/// Matrix3 class
/// Josh Tyrrell Browne
/// </summary>
#include "Matrix3.h"

/// <summary>
/// Defautl constructor set all values to zero
/// </summary>
MyMatrix3::MyMatrix3()
{
	m_11 = 0;
	m_12 = 0;
	m_13 = 0;
	m_21 = 0;
	m_22 = 0;
	m_23 = 0;
	m_31 = 0;
	m_32 = 0;
	m_33 = 0;
}

//asign passed variables
MyMatrix3::MyMatrix3(
	double t_a11, double t_a12, double t_a13,
	double t_a21, double t_a22, double t_a23,
	double t_a31, double t_a32, double t_a33)
{
	m_11 = t_a11;
	m_12 = t_a12;
	m_13 = t_a13;
	m_21 = t_a21;
	m_22 = t_a22;
	m_23 = t_a23;
	m_31 = t_a31;
	m_32 = t_a32;
	m_33 = t_a33;
}

//asign variables to rows
MyMatrix3::MyMatrix3(MyVector3 t_row1, MyVector3 t_row2, MyVector3 t_row3)
{
	m_11 = t_row1.x;
	m_12 = t_row1.y;
	m_13 = t_row1.z;
	m_21 = t_row2.x;
	m_22 = t_row2.y;
	m_23 = t_row2.z;
	m_31 = t_row3.x;
	m_32 = t_row3.y;
	m_33 = t_row3.z;
}


/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyMatrix3::~MyMatrix3()
{
}

// output variables
std::string MyMatrix3::toString() const
{
	const std::string output = "[" + std::to_string(m_11) + "," + std::to_string(m_12) + "," + std::to_string(m_13) + "\n"
									+ std::to_string(m_21) + "," + std::to_string(m_22) + "," + std::to_string(m_23) + "\n"
									+ std::to_string(m_31) + "," + std::to_string(m_32) + "," + std::to_string(m_33) + "]";

	return output;
}

//equals check
bool MyMatrix3::operator ==(const MyMatrix3 t_other)const
{
	if (m_11 == t_other.m_11 && m_12 == t_other.m_12 && m_13 == t_other.m_13 &&
		m_21 == t_other.m_21 && m_22 == t_other.m_22 && m_23 == t_other.m_23 &&
		m_31 == t_other.m_31 && m_32 == t_other.m_32 && m_33 == t_other.m_33)
	{
		return true;
	}
	return false;
}

// check for inequality
bool MyMatrix3::operator !=(const MyMatrix3 t_other)const
{
	if (m_11 != t_other.m_11 || m_12 != t_other.m_12 || m_13 != t_other.m_13 ||
		m_21 != t_other.m_21 || m_22 != t_other.m_22 || m_13 != t_other.m_23 ||
		m_31 != t_other.m_31 || m_32 != t_other.m_32 || m_33 != t_other.m_33)
	{
		return true;
	}
	return false;
}

// adding matrix'
MyMatrix3 MyMatrix3::operator +(const MyMatrix3 t_other) const
{
	return MyMatrix3{ m_11 + t_other.m_11, m_12 + t_other.m_12, m_13 + t_other.m_13,
					 m_21 + t_other.m_21, m_22 + t_other.m_22, m_23 + t_other.m_23,
					 m_31 + t_other.m_31, m_32 + t_other.m_32, m_33 + t_other.m_33 };
}

// subtracting matrix'
MyMatrix3 MyMatrix3::operator -(const MyMatrix3 t_other) const
{
	return MyMatrix3{ m_11 - t_other.m_11, m_12 - t_other.m_12, m_13 - t_other.m_13,
				      m_21 - t_other.m_21, m_22 - t_other.m_22, m_23 - t_other.m_23,
					  m_31 - t_other.m_31, m_32 - t_other.m_32, m_33 - t_other.m_33 };
}

// multiplication matrix'
MyMatrix3 MyMatrix3::operator *(const MyMatrix3 t_other) const
{
	return MyMatrix3{ ((m_11 * t_other.m_11) + (m_12 * t_other.m_21) + (m_13 * t_other.m_31)) , ((m_11 * t_other.m_12) + (m_12 * t_other.m_22) + (m_13 * t_other.m_32)) , ((m_11 * t_other.m_13) + (m_12 * t_other.m_23) + (m_13 * t_other.m_33)) ,
					  ((m_21 * t_other.m_11) + (m_22 * t_other.m_21) + (m_23 * t_other.m_31)) , ((m_21 * t_other.m_12) + (m_22 * t_other.m_22) + (m_23 * t_other.m_32)) , ((m_21 * t_other.m_13) + (m_22 * t_other.m_23) + (m_23 * t_other.m_33)) ,
					  ((m_31 * t_other.m_11) + (m_32 * t_other.m_21) + (m_33 * t_other.m_31)) , ((m_31 * t_other.m_12) + (m_32 * t_other.m_22) + (m_33 * t_other.m_32)) , ((m_31 * t_other.m_13) + (m_32 * t_other.m_23) + (m_33 * t_other.m_33)) };
}

// multiplying matrix3 by vector3
MyVector3 MyMatrix3::operator *(const MyVector3 t_vector)const
{
	return MyVector3{ ((m_11 * t_vector.x) + (m_12 * t_vector.y) + (m_13 * t_vector.z)),
					   ((m_21 * t_vector.x) + (m_22 * t_vector.y) + (m_23 * t_vector.z)),
					   ((m_31 * t_vector.x) + (m_32 * t_vector.y) + (m_33 * t_vector.z)) };
}

// multiplying matrix by scaler
MyMatrix3 MyMatrix3::operator *(const double t_scale)const
{
	return MyMatrix3{ m_11 * t_scale, m_12 * t_scale, m_13 * t_scale,
					  m_21 * t_scale, m_22 * t_scale, m_23 * t_scale,
					  m_31 * t_scale, m_32 * t_scale, m_33 * t_scale };
}

// find the transpose of matrix. (basically rows become collumns)
MyMatrix3 MyMatrix3::transpose()const
{
	MyMatrix3 transpose = { m_11, m_21, m_31,
							m_12, m_22, m_32,
							m_13, m_23, m_33 };
	return transpose;
}

//find the determinant of matrix.
double MyMatrix3::determinant() const
{
	double determinant = m_11 * ((m_22 * m_33) - (m_32 * m_23)) - m_21 * ((m_33 * m_12) - (m_32 * m_13)) + m_31 * ((m_23 * m_12) - (m_22 * m_13));
	return determinant;
}

MyMatrix3 MyMatrix3::inverse() const
{
	MyMatrix3 inverse;
	if (determinant() != 0)
	{
		inverse = { (m_33 * m_22) - (m_32 * m_23), (m_32 * m_13) - (m_33 * m_12), (m_23 * m_12) - (m_22 * m_13),
					(m_31 * m_23) - (m_33 * m_21), (m_33 * m_11) - (m_31 * m_13), (m_21 * m_13) - (m_23 * m_11),
					(m_32 * m_21) - (m_31 * m_22), (m_31 * m_12) - (m_32 * m_11), (m_22 * m_11) - (m_21 * m_12) };

		inverse = inverse * (1 / determinant());
	}
	return inverse;
}

// returns a matrix row 
MyVector3 MyMatrix3::row(const int t_row)const
{
	MyVector3 row;
	if (t_row == 0)
	{
		row = { m_11, m_12, m_13 };
	}
	if (t_row == 1)
	{
		row = { m_21, m_22, m_23 };
	}
	if (t_row == 2)
	{
		row = { m_31, m_32, m_33 };
	}
	return row;
}

// returns a matrix column
MyVector3 MyMatrix3::column(const int t_column) const
{
	MyVector3 col;
	if (t_column == 0)
	{
		col = { m_11, m_21, m_31 };
	}
	if (t_column == 1)
	{
		col = { m_12, m_22, m_32 };
	}
	if (t_column == 2)
	{
		col = { m_13, m_23, m_33 };
	}
	return col;
}

// rotate matrix about Z
MyMatrix3 MyMatrix3::rotationZ(const double t_angleRadians)
{
	// maybe change angle to radians?
	MyMatrix3 rotationZ = { cos(t_angleRadians), -sin(t_angleRadians), 0,
							sin(t_angleRadians), cos(t_angleRadians), 0,
							0,                   0,                   1 };

	return rotationZ;
}

// rotate matrix about Y
MyMatrix3 MyMatrix3::rotationY(const double t_angleRadians)
{
	MyMatrix3 rotationY = { cos(t_angleRadians), 0, sin(t_angleRadians),
							0,                   1,                   0,
						   -sin(t_angleRadians), 0, cos(t_angleRadians) };

	return rotationY;
}

// rotate matrix about Z
MyMatrix3 MyMatrix3::rotationX(const double t_angleRadians)
{
	MyMatrix3 rotationX = { 1,					 0,					   0,
							0, cos(t_angleRadians), -sin(t_angleRadians),
							0, sin(t_angleRadians), cos(t_angleRadians)  };

	return rotationX;
}

// translation 
MyMatrix3 MyMatrix3::translation(const MyVector3 t_displacement)
{
	MyMatrix3 translation = { 1, 0, t_displacement.x,
							  0, 1, t_displacement.y,
							  0, 0, 1 };       // z must equal 1 for 2d

	return translation;
}

// scale matrix
MyMatrix3 MyMatrix3::scale(const double t_scalingfactor)
{
	MyMatrix3 scale = { t_scalingfactor, 0, 0,
						0, t_scalingfactor, 0,
						0, 0, t_scalingfactor };

	return scale;
}