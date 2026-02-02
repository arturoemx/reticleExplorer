#ifndef __GEOM_VEC2D__
#define __GEOM_VEC2D__

#include <ostream>
#include <opencv2/opencv.hpp>

/*! 
 \namespace gfeat
 \brief A namespace for geometric features.
*/
namespace gfeat
{
	/*!
	\struct vec2D
	\brief This structure allow to define 2-dimensional homogeneous vectors, suitable
	       to represent points and lines in the image plane. An 2D homogeneos vector \f$v \in \mathcal{R}^3, v \neq [0,0,0]^\top\f$.
	*/
	struct vec2D
	{

		float p[3]; //!< float array that hold the values that define a 2D homogeneous vector.

		/*!
		 * \fn vec2D ()
		 * \brief Object constructor.
		 */
		vec2D ();

		/*!
		 * \fn vec2D (float _x, float _y, float _w = 1)
		 * \brief Object constructor.
		 * \param _x -> value assigned to the first vector element.
		 * \param _y -> value assigned to the second vector element.
		 * \param _w -> value assigned to the third vector element.
		 */		
		vec2D (float _x, float _y, float _w = 1);

		/*!
		 * \fn vec2D (cv::Vec3f &v)
		 * \brief Object constructor. Initialize the object using a openCV 3-element float vector.
		 * \param v -> openCV 3-element float vector.
		 */
		vec2D (cv::Vec3f &v);

		/*!
		 * \fn vec2D (cv::Vec2f &v)
		 * \brief Object constructor. Initialize the object using a openCV 2-element float vector. It sets the third element of attribute p with 1.
		 * \param v -> openCV 2-element float vector.
		 */
		vec2D (cv::Vec2f &v);

		/*!
		 * \fn vec2D (vec2D &v)
		 * \brief Object copy constructor. Initalizes the object woth another object of the same class.
		 * \param v -> vec2D object.
		 */
		vec2D (vec2D &v);

		/*!
		 * \fn vec2D &operator= (const vec2D &v)
		 * \brief Overloads the assignment operator.
		 * \param v -> vector to be copied into de calling object.
		 * \return The calling object.
		 */
		vec2D &operator= (const vec2D &v);

		/*!
		 * \fn vec2D operator + (const vec2D &v)
		 * \brief Overloads the addition operator.
		 * \param v -> vector to be added to de calling object
		 * \return A new object that contain the addition of the calling object and the object v.
		 */
		vec2D operator + (const vec2D &v);

		/*!
		 * \fn vec2D operator - (const vec2D &v)
		 * \brief Overloads the substraction operator.
		 * \param v -> vector to be substracted to de calling object
		 * \return A new object that contain the substraction of the object v to the calling object.
		 */
		vec2D operator - (const vec2D &v);

		/*!
		 * \fn template <typename X> vec2D operator + (X val)
		 * \brief Overloads the addition operator.
		 * \param val -> value to be added to each element of the vector stored in the calling object.
		 * \return A new object that contain the addition of a scalar value to each element of the vector stored in the calling object.
		 */
		template <typename X>
		vec2D operator + (X val)
		{
			vec2D vo(p[0]+val, p[1]+val, p[2]+val);

			return vo;
		}

		/*!
		 * \fn template <typename X> vec2D operator - (X val)
		 * \brief Overloads the substraction operator for a scalar value.
		 * \param val -> value to be substracted to each element of the vector stored in the calling object.
		 * \return A new object that contain the substraction of a scalar value to each element of the vector stored in the calling object.
		 */
		template <typename X>
		vec2D operator - (X val)
		{
			vec2D vo(p[0]-val, p[1]-val, p[2]-val);

			return vo;
		}

		/*!
		 * \fn template <typename X> vec2D operator * (X val)
		 * \brief Overloads the multiplication operator for a scalar value.
		 * \param val -> value to be multiplied to each element of the vector stored in the calling object.
		 * \return A new object that contain the multiplication of a scalar value to each element of the vector stored in the calling object.
		 */
		template <typename X>
		vec2D operator * (X val)
		{
			vec2D vo(p[0]*val, p[1]*val, p[2]*val);

			return vo;
		}

		/*!
		 * \fn template <typename X> vec2D operator / (X val)
		 * \brief Overloads the division operator for a scalar value.
		 * \param val -> value used to divide each element of the vector stored in the calling object.
		 * \return A new object that contain the division of each element of the vector stored in the calling object by a scalar value.
		 */
		template <typename X>
		vec2D operator / (X val)
		{
			vec2D vo(p[0]/val, p[1]/val, p[2]/val);

			return vo;
		}

		/*!
		 * \fn vec2D operator += (const vec2D &v)
		 * \brief Overloads the addition and then assignment operator.
		 * \param v -> vector to be added to the calling object
		 * \return The calling object which now contains the addition of the object v to itself.
		 */
		vec2D &operator += (const vec2D &v);

		/*!
		 * \fn vec2D operator -= (const vec2D &v)
		 * \brief Overloads the substraction and then assignment operator.
		 * \param v -> vector to be substracted to the calling object
		 * \return The calling object which now contains the substraction of the object v to itself.
		 */
		vec2D &operator -= (const vec2D &v);

		/*!
		 * \fn template <typename X> vec2D operator += (X val)
		 * \brief Overloads the addition and then assignment operator for a scalar value.
		 * \param val -> scalar value to be added to each element of the vector stored in the calling object
		 * \return The calling object which now contains the addition of the scalar val to itself.
		 */
		template <typename X>
		vec2D operator += (X val)
		{
			p[0] += (float)val;
			p[1] += (float)val;
			p[2] += (float)val;

			return *this;
		}

		/*!
		 * \fn template <typename X> vec2D operator -= (X val)
		 * \brief Overloads the substraction and then assignment operator for a scalar value.
		 * \param val -> scalar value to be substracted to each element of the vector stored in the calling object
		 * \return The calling object which now contains the result of substracting the scalar val to itself.
		 */
		template <typename X>
		vec2D operator -= (X val)
		{
			p[0] -= (float)val;
			p[1] -= (float)val;
			p[2] -= (float)val;

			return *this;
		}

		/*!
		 * \fn template <typename X> vec2D operator *= (X val)
		 * \brief Overloads the multiplication and then assignment operator for a scalar value.
		 * \param val -> scalar value to be multiplied to each element of the vector stored in the calling object
		 * \return The calling object which now contains the result of multiplying the scalar val to itself.
		 */
		template <typename X>
		vec2D operator *= (X val)
		{
			p[0] *= (float)val;
			p[1] *= (float)val;
			p[2] *= (float)val;

			return *this;
		}

		/*!
		 * \fn template <typename X> vec2D operator /= (X val)
		 * \brief Overloads the division and then assignment operator for a scalar value.
		 * \param val -> scalar value to be used to divide each element of the vector stored in the calling object
		 * \return The calling object which now contains the result of dividing itself by the scalar val.
		 */
		template <typename X>
		vec2D operator /= (X val)
		{
			p[0] /= (float)val;
			p[1] /= (float)val;
			p[2] /= (float)val;

			return *this;
		}

		/*!
		 * \fn float operator[](int idx)
		 * \brief Overload the operator[] to access each element of the vector by an index.
		 * \param idx -> The index used to access eache element of the array attribute p.
		 * \return The element stored in the idx position of the array attribute p.
		 */
		float operator[](int idx);
		
		/*!
		 * \fn vec2D cross(vec2D &s, vec2D &t)
		 * \brief Computes the cross product of two vec2D objects
		 * \param s -> the first vec2D vector.
		 * \param t -> the second vec2D vector.
		 * \return A vector that contains the cross producto of the vectors s and t.
		 */
		vec2D cross(vec2D &s, vec2D &t);

		/*!
		 * \fn vec2D cross(vec2D &t)
		 * \brief Computes the cross product of the calling object and another vec2D object.
		 * \param t -> vec2D vector.
		 */
		void cross(vec2D &t);
		
		/*!
		 * \fn void norm()
		 * \brief Normalizes the calling object. Namely it divides each element of the calling object by its L2-norm.
		 */
		void norm();
		
	};

	/*!
		 * \fn std::ostream &operator<< (std::ostream &s, vec2D v)
		 * \brief Overload the stream output operator.
		 * \param s -> the object at the left of the operator <<. It is the output stream where the output will be written.
		 * \param v -> A vec2D object whose attributes are formated and written into the stream s.
		 * \return the stream s.
		 * 
		 * This methods formats a vector v and writes it into an output stream.
		 * 
		 * The output takes the following form:
		 * [ p[0], p[1], p[2] ]
		 * 
		 */
	std::ostream &operator<< (std::ostream &s, vec2D v);
}

#endif