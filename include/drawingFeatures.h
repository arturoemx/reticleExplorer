#ifndef __DRAWING_FEATURES__
#define __DRAWING_FEATURES__

#include <geomFeatures.h>
#include <opencv2/opencv.hpp>

/*! \struct drawingFeatures
* 
* \brief This structure defines an abstract class that stores drawn image features properties.
* 
*  This structure defines an abstract class that stores drawn image features properties. It together with
*  abstract geometric features point2D, line2D and Circle to define new structures which includes by inheritance
*  both structures attributes.
*/
struct drawingFeatures
{
	int thickness; //!< Stores the width of a drawn feature.
	int lineType; //!< Stores the kind of lines used to draw a feature. The kind on lines are the ones used by the openCV highGUI library.

	/*! \fn drawingFeatures()
	 *  \brief Object default constructor.
	 *  
	 *  It sets thickness to 1 and linesType to cv::LINE_8.
	 */
	drawingFeatures();
	
	/*! \fn setThickness(int t)
	 *  \brief set the thickness attribute to the values of the paramter t.
	 *  \param t The value used to set the thickness atribute.
	 */
	void setThickness(int t);

	/*! \fn setLineType(int type)
	 *  \brief set the lineType attribute to the values of the paramter type.
	 *  \param type The value used to set the lineType atribute.
	 */
	void setLineType(int type);
};


/*!
 * \struct dPoint
 * \brief This structure defines a class that combines drawing attributess with geometric 2D point attributes to create objects that are meant to be drawn.
 */
struct dPoint: public gfeat::point2D, public drawingFeatures
{
	/*! \fn dPoint()
	 *  \brief Object default constructor.
	 */
	dPoint():point2D(){}
	
	/*! 
	 * \fn dPoint(float _x, float _y, float _w = 1)
	 * \brief Object constructor. Initializes the geometric point attributes.
	 * \param _x -> The first parameter of the point defined as \f$[_x,_y,_w]^top\f$.
	 * \param _y -> The second parameter of the point defined as \f$[_x,_y,_w]^top\f$.
     * \param _w -> The third parameter of the point defined as \f$[_x,_y,_w]^top\f$. 
	 */
	dPoint(float _x, float _y, float _w = 1):point2D(_x, _y, _w){}

	/*! 
	 * \fn dPoint(cv::Vec2f &v)
	 * \brief Object constructor. Initializes the geometric point attributes using a openCV 2-element float vector.
     * \param v -> openCV 2-element float vector.
	 */
	dPoint(cv::Vec2f &v):point2D(v){}

	/*! 
	 * \fn dPoint(cv::Vec3f &v)
	 * \brief Object constructor. Initializes the geometric point attributes using a openCV 3-element float vector.
     * \param v -> openCV 3-element float vector.
	 */
	dPoint(cv::Vec3f &v):point2D(v){}
};

/*!
 * \fn std::ostream &operator<< (std::ostream &s, dPoint &p)
 * \brief Overload the stream output operator.
 * \param s The object at the left of the operator <<. It is the output stream where the output will be written.
 * \param p A dPoint object whose attributes are formated and written into the stream s.
 * \return The stream s.
 * 
 * This methods formats a dPoint object p and writes it into an output stream.
 */
std::ostream &operator<< (std::ostream &s, dPoint &p);

/*!
 * \struct dLine
 * \brief This structure defines a class that combines drawing attributess with geometric 2D line attributes to create objects that are meant to be drawn.
 */
struct dLine: public gfeat::line2D, public drawingFeatures
{
	/*! \fn dLine()
	 *  \brief Object default constructor.
	 */
	dLine():line2D(){}
	
	/*! 
	 * \fn dLine(float _A, float _B, float _C = 1)
	 * \brief Object constructor. Initializes the geometric line attributes.
	 * \param _A -> The first parameter of the 2D line equation \f$Ax+By+C=0\f$.
	 * \param _B -> The second parameter of the 2D line equation \f$Ax+By+C=0\f$.
	 * \param _C -> The third parameter of the 2D line equation \f$Ax+By+C=0\f$. 
	 */
	dLine(float _A, float _B, float _C):line2D(_A, _B, _C){}

	/*!
	 * \fn dLine(float _x1, float _y1, float _x2, float _y2)
	 * \brief Object constructor with line endpoints. 
	 * \param _x1 -> the \f$x\f$ of the first endpoint coordinate.
	 * \param _y1 -> the \f$y\f$ of the first endpoint coordinate.
	 * \param _x2 -> the \f$x\f$ of the second endpoint coordinate.
	 * \param _y2 -> the \f$y\f$ of the second endpoint coordinate.
	 * 
	 * Define the object parameters that correspond to the 2D line that join the 2 endpoints and sets the attribute unbound to false.
	 */
	dLine(float x1, float y1, float x2, float y2):line2D(x1, y1, x2, y2){}

	/*! 
	 * \fn dLine(cv::Vec2f &v)
	 * \brief Object constructor. Initializes the geometric line attributes using a openCV 2-element float vector.
     * \param v -> openCV 2-element float vector.
	 */
	dLine(cv::Vec2f &v):line2D(v){}

	/*! 
	 * \fn dLine(cv::Vec3f &v)
	 * \brief Object constructor. Initializes the geometric line attributes using a openCV 3-element float vector.
     * \param v -> openCV 2-element float vector.
	 */
	dLine(cv::Vec3f &v):line2D(v){}

	/*! 
	 * \fn dLine(cv::Vec4f &v)
	 * \brief Object constructor. Initializes the geometric line attributes using a openCV 4-element float vector.
     * \param v -> openCV 2-element float vector.
     * 
     * The parameter of this constructor contains the four floating numbers that define the line endpoints.
	 * It initializes the line endpoints with the vector v elements: (v[0], v[1]), (v[2], v[3]),
	 * and the attribute unbound is set to false. The three element vector that contain the line parameters
	 * are computed as the parameters that join the two endopints. 
	 */
	dLine(cv::Vec4f &v):line2D(v){}
};

/*!
 * \fn std::ostream &operator<< (std::ostream &s, dLine &l)
 * \brief Overload the stream output operator.
 * \param s The object at the left of the operator <<. It is the output stream where the output will be written.
 * \param l A dLine object whose attributes are formated and written into the stream s.
 * \return The stream s.
 * 
 * This methods formats a dLine object p and writes it into an output stream.
 */
std::ostream &operator<< (std::ostream &s, dLine &l);

/*!
 * \struct dCircle
 * \brief This structure defines a class that combines drawing attributess with geometric 2D circle attributes to create objects that are meant to be drawn.
 */
struct dCircle: public gfeat::circle, public drawingFeatures 
{
	/*! \fn dCircle()
	 *  \brief Object default constructor.
	 */
	dCircle():circle(){}

	/*! 
	 * \fn dCircle(float _h, float _k, float _r)
	 * \brief Object constructor. Initializes the geometric circle attributes.
	 * \param _h parameter that is copied to the object attribute h.
	 * \param _k parameter that is copied to the object attribute k.
	 * \param _r parameter that is copied to the object attribute r.
	 */
	dCircle(float _h, float _k, float _r):circle(_h, _k, _r){}
};

/*!
 * \fn std::ostream &operator<< (std::ostream &s, dCircle &c)
 * \brief Overload the stream output operator.
 * \param s The object at the left of the operator <<. It is the output stream where the output will be written.
 * \param c A dCircle object whose attributes are formated and written into the stream s.
 * \return The stream s.
 * 
 * This methods formats a dCircle object p and writes it into an output stream.
 */
std::ostream &operator<< (std::ostream &s, dCircle &c);

#endif