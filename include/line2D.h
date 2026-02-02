#ifndef __GEOM_LINE2D__
#define __GEOM_LINE2D__

#include <ostream>
#include <opencv2/opencv.hpp>
#include <vec2D.h>
#include <point2D.h>

namespace gfeat
{
	/*! \struct line2D
	 * 
	 * \brief Stores an homogeneous representation of a 2D line.
	 * 
	 * This struct extends the struct gfeat::vec2D to include atributes to represent a bound line in the plane.
	 * A bound line has a starting point and an ending point.
	*/
	struct line2D: public vec2D
	{
		float x1; //!< One of the floating number that encodes a bound line endpoints: (x1, y1), (x2, y2).
		float y1; //!< One of the floating number that encodes a bound line endpoints: (x1, y1), (x2, y2).
		float x2; //!< One of the floating number that encodes a bound line endpoints: (x1, y1), (x2, y2).
		float y2; //!< One of the floating number that encodes a bound line endpoints: (x1, y1), (x2, y2).

		bool unbound; //!< Boolean attributes that defines if the line is unbounded or not. The default value is true.

		/*!
		 * \fn line2D()
		 * \brief Object default constructor. 
		 * 
		 * After invoking vec2D default constructor initializes the line endpoints to 0, and the attribute unbound to true.
		 */
		line2D();
		
		/*!
		 * \fn line2D(float _A, float _B, float _C = 1)
		 * \brief Object constructor with line parameters. 
		 * \param _A -> The first parameter of the 2D line equation \f$Ax+By+C=0\f$.
		 * \param _B -> The second parameter of the 2D line equation \f$Ax+By+C=0\f$.
		 * \param _C -> The third parameter of the 2D line equation \f$Ax+By+C=0\f$.
		 * 
		 * After invoking vec2D constructor with the parameters _A, _B and _C it initializes the line endpoints to 0, and the attribute unbound to true.
		 */
		line2D(float _A, float _B, float _C = 1);

		/*!
		 * \fn line2D(float _x1, float _y1, float _x2, float _y2)
		 * \brief Object constructor with line endpoints. 
		 * \param _x1 -> the \f$x\f$ of the first endpoint coordinate.
		 * \param _y1 -> the \f$y\f$ of the first endpoint coordinate.
		 * \param _x2 -> the \f$x\f$ of the second endpoint coordinate.
		 * \param _y2 -> the \f$y\f$ of the second endpoint coordinate.
		 * 
		 * Define the object parameters that correspond to the 2D line that join the 2 endpoints and sets the attribute unbound to false.
		 */
		line2D(float _x1, float _y1, float _x2, float _y2);

		/*!
		 * \fn line2D(cv::Vec3f &v)
		 * \brief Object constructor. Initialize the object using a openCV 3-element float vector.
		 * \param v -> openCV 3-element float vector.
		 * 
		 * After invoking vec2D constructor with the parameter v, it initializes the line endpoints to 0, and the attribute unbound to true.
		 */
		line2D(cv::Vec3f &v);

		/*!
		 * \fn line2D(cv::Vec2f &v)
		 * \brief Object constructor. Initialize the object using a openCV 2-element float vector.
		 * \param v -> openCV 2-element float vector.
		 * 
		 * After invoking vec2D constructor with the parameter v, it initializes the line endpoints to 0, and the attribute unbound to true.
		 */
		line2D(cv::Vec2f &v);

		/*!
		 * \fn line2D(cv::Vec4f &v)
		 * \brief Object constructor. Initialize the object using a openCV 4-element float vector.
		 * \param v -> openCV 4-element float vector.
		 * 
		 * The parameter of this constructor contains the four floating numbers that define the line endpoints.
		 * It initializes the line endpoints with the vector v elements: (v[0], v[1]), (v[2], v[3]),
		 * and the attribute unbound is set to false. The three element vector that contain the line parameters
		 * are computed as the parameters that join the two endopints. 
		 */
		line2D(cv::Vec4f &v);
		
		/*!
		 * \fn void join(gfeat::vec2D &p1, gfeat::vec2D &p2)
		 * \brief Defines the lines as the join of two points in the plane, represented as homogeneous 2D vectors, p1 and p2.
		 * \param p1 -> vec2D object that contains the homogeneous representation of a 2D point.
		 * \param p2 -> vec2D object that contains the homogeneous representation of a 2D point.
		 * 
		 * The join of two homogeneous points in the plane is computed as the cross products of those points.
		 * Also the points p1 and p2 are set to define the line endpoints and obviously the unbound flag is set to false.
		 */
		void join(gfeat::vec2D &p1, gfeat::vec2D &p2);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, gfeat::line2D l)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param l A line2D object to be formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a line2D object l and writes it into an output stream.
	* 
	* The output takes the following form:
	* 
	* if the line is bounded the output takes the form:
	* \f$Pt\{(x1, y1)-(x2,y2)\|\sqrt{(x1-x2)^2+(y1-y2)^2}: [ p[0], p[1], p[2] ]\}\f$.
	* 
	* if not it just returns the output of the overloaded vec2D ostream operator.
	* 
	* 
	*/
	std::ostream &operator<< (std::ostream &s, line2D l);
}
#endif