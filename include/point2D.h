#ifndef __GEOM_POINT2D__
#define __GEOM_POINT2D__

#include <ostream>
#include <opencv2/opencv.hpp>
#include <vec2D.h>

namespace gfeat
{
	
	/*! \struct point2D
	 * 
	 * \brief Stores an homogeneous representation of a 2D point.
	 * 
	 * This struct extends the struct gfeat::vec2D to include \f$(cx, cy)\f$, the cartesian coordinates of the homogeneous
	 * 2D point, and a boolean flag to indicate if the point is at the infinity.
	*/
	struct point2D: public vec2D
	{
		float cx; //!< One of the floating number that encodes the horizontal componente of the cartesian coordinate \f$(cx, cy)\f$.
		float cy; //!< One of the floating number that encodes the vertical componente of the cartesian coordinate \f$(cx, cy)\f$.
		bool infinity; //!< boolean attribute that indicate if the point is at the infinity.

		/*!
		 * \fn point2D()
		 * \brief Object default constructor. 
		 * 
		 * After invoking vec2D default constructor initializes cartesian ccordinates (cx, cy) to (0, 0) and the attribute infinity to false.
		 */
		point2D();

		/*!
		 * \fn point2D(float _x, float _y, float _w = 1)
		 * \brief Object constructor with line parameters. 
		 * \param _x -> The first parameter of the point defined as \f$[_x,_y,_w]^\top\f$.
		 * \param _y -> The second parameter of the point defined as \f$[_x,_y,_w]^\top\f$.
		 * \param _w -> The third parameter of the point defined as \f$[_x,_y,_w]^\top\f$.
		 * 
		 * After invoking vec2D constructor with the parameters _x, _y and _w, if _w is different to 0, the cartesian
		 * coordinates are initialized as follows: cx=_x/_w, cy=_y/_w and the attribute infinity is set to false.
		 * Otherwise cx=_x/1e12, cy=_y/1e12 and the attribute infinity is set to true.
		 * 
		 */
		point2D(float _x, float _y, float _w = 1);

		/*!
		 * \fn point2D(cv::Vec3f &v)
		 * \brief Object constructor. Initialize the object using a openCV 3-element float vector.
		 * \param v -> openCV 3-element float vector.
		 * 
		 * After invoking vec2D constructor with the parameter v, if v[2] is different to 0, the cartesian
		 * coordinates are initialized as follows: cx=v[0]/v[2], cy=v[1]/v[2] and the attribute infinity is set to false.
		 * Otherwise cx=v[0]/1e12, cy=v[1]/1e12 and the attribute infinity is set to true.
		 */
		point2D(cv::Vec3f &v);

		/*!
		 * \fn point2D(cv::Vec3f &v)
		 * \brief Object constructor. Initialize the object using a openCV 3-element float vector.
		 * \param v -> openCV 3-element float vector.
		 * 
		 * After invoking vec2D constructor with the parameter v, if v[2] is different to 0, the cartesian
		 * coordinates are initialized as follows: cx=v[0]/v[2], cy=v[1]/v[2] and the attribute infinity is set to false.
		 * Otherwise cx=v[0]/1e12, cy=v[1]/1e12 and the attribute infinity is set to true.
		 */
		point2D(cv::Vec2f &v);

		/*!
		 * \fn void intersect(gfeat::vec2D &l1, gfeat::vec2D &l2)
		 * \brief Defines the point as the intersection of two lines in the plane, represented as homogeneous 2D vectors, l1 and l2.
		 * \param l1 -> vec2D object that contains the homogeneous representation of a 2D line.
		 * \param l2 -> vec2D object that contains the homogeneous representation of a 2D line.
		 * 
		 * The intersection of two homogeneous lines in the plane is computed as the cross products of those lines.
		 * The cartesian coordinates are defined accordingly.
		 * if the lines l1 and l2 are parallel, the boolean attribute infinity is set to true.
		 * 
		 */
		void intersect(vec2D &l1, vec2D &l2);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, gfeat::point2D p)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param p A point2D object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a point2D object p and writes it into an output stream.
	* 
	* The output takes the following form:
	* 
	* * if the point is at not at infinity, i.e. attribute infinity is equal to false, the  takes the form:
	* \f$(cx, cy)\f$, oterwise it takes the forms \f$(cx,cy, \infty)\f$.
	* 
	* if not it just returns the output of the overloaded vec2D ostream operator.
	* 
	*/
	std::ostream &operator<< (std::ostream &s, point2D p);
}

#endif