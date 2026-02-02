#ifndef __GEOM_CIRCLE__
#define __GEOM_CIRCLE__

#include <ostream>
#include <opencv2/opencv.hpp>

namespace gfeat
{
	/*! \struct circle
	 * 
	 * \brief Stores the parameters that define a circle in the plane.
	 * 
	 * A circle in the plane is define by the equation: \f$(x-h)^2+(y-k)^2=r^2\f$,
	 * where \f$(h,k)\f$ are the circle center coordinates and \f$r\f$  is the circle radius.
	 */
	struct circle
	{
		float h; //!< The attribute that stores the circle horizontal component of its center coordinate.
		float k; //!< The attribute that stores the circle vertical component of its center coordinate.
		float r; //!< The attribute that stores the circle radius.

	   /*!
		* \fn circle()
		* \brief Object default constructor. 
		* 
		* It intialize all the attributes with 0.
		*/
		circle();
	
		/*!
		* \fn circle(float _h, float _k, float _r)
		* \brief Object constructor. 
		* \param _h parameter that is copied to the object attribute h.
		* \param _k parameter that is copied to the object attribute k.
		* \param _r parameter that is copied to the object attribute r.
		*
		*/
		circle (float _h, float _k, float _r);

		/*!
		 * \fn circle(cv::Vec3f &c)
		 * \brief Object constructor. Initialize the object using a openCV 3-element float vector.
		 * \param c openCV 3-element float vector.
		 * 
		 * if assigns c[0], c[1] and c[2] to attributes h, k and r, respectively.
		 * 
		 */
		circle (cv::Vec3f &c);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, circle c)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param c A circle object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a circle object c and writes it into an output stream.
	* 
	* The output takes the following form:
	* 
	* Circ{(h,k):r}
	* 
	*/
	std::ostream &operator<< (std::ostream &s, circle c);
}

#endif