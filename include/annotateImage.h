#ifndef __ANNOTATE_IMAGE__
#define __ANNOTATE_IMAGE__

#include <math.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <drawingFeatures.h>


/*! 
 \namespace imNote
 \brief A namespace for image visual annotations.
*/
namespace imNote
{

	/*!
 	 * \enum dFeatureTypes
     * \brief defines the types of features that are considered for image annotations.
     */
    enum dFeatureTypes {None=0, image, point, line, circle, marker};

	/*!
	 * \struct featureDescriptor
	 * \brief Abstract struct definition that contains a unique identifier, type and color of an image feature.
	 */
	struct featureDescriptor
	{
		u_int id; //!< A number that uniquely identifies a feature.
		dFeatureTypes type; //!< The type of feature.
		cv::Vec3b Color; //!< OpenCV 3-element 8-bit unsigned integer vector that stores the feature RGB components color

		featureDescriptor(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));

		/*! \fn setId(u_int _id)
		 *  \brief Set the unique identifier attribute to the values of the paramter _id.
		 *  \param _id The value used to set the unique identifier atribute.
		 */
		void setId(u_int _id);

		/*! \fn setColor(cv::Scalar_<uchar> C)
		 *  \brief set the color attribute to the values of the paramter C.
		 *  \param C The OpenCV 3-element 8-bit unsigned integer vector used to initialize the Color attribute.
		 */
		void setColor(cv::Scalar_<uchar> C);

	};

	/*!
	 * \struct imageFeature
	 * \brief Structure that contains an Image feature.
	 * 
	 * An image feature is conceived as a binary image, where pixels that are greater than 0
	 * represent a feature which is srawn with a particular color in a RGB image.
	 */
	struct imageFeature: public featureDescriptor
	{
		cv::Mat ftre; //!< OpenCV Mat object which stores the image feature.

		/*!
		 * \fn imageFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Object constructor.
		 * \param val The value assigned to the feature unique identifier.
		 * \param C Color used to initilize the image. The default value corresponds to color white.
		 */
		imageFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn set(cv::Mat &I)
		 * \brief Copies the image I into the feature image stored in the object.
		 * \param I The image that is copied to the feature image.
		 */
		void set(cv::Mat &I);
		
		/*!
		 * \fn apply(cv::Mat &I)
		 * \brief Paint the image feature into the image I. 
		 * \param I The image where the feature will be painted.
		 */
		void apply(cv::Mat &I);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, imageFeature &iF)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param iF A reference to an imageFeature object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a imageFeature object iF and writes it into an output stream.
	*/
	std::ostream &operator<< (std::ostream &s, imageFeature &iF);

	/*!
	 * \struct pointFeature
	 * \brief Structure that contains a point feature.
	 */
	struct pointFeature: public featureDescriptor
	{
		dPoint ftre; //!< point feature.

		/*!
		 * \fn pointFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Object constructor.
		 * \param val The value assigned to the feature unique identifier.
		 * \param C Color used to draw the point feature. The default value corresponds to color white.
		 */
		pointFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn set(dPoint &val)
		 * \brief Copies dPoint object val into the feature point stored in the object.
		 * \param val The dPoint that is copied to the feature point.
		 */
		void set(dPoint &val);

		/*!
		 * \fn apply(cv::Mat &I)
		 * \brief Paint the point feature into the image I. 
		 * \param I The image where the feature will be painted.
		 */
		void apply(cv::Mat &I);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, pointFeature &pF)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param pF A reference to an pointFeature object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a pointFeature object pF and writes it into an output stream.
	*/
	std::ostream &operator<< (std::ostream &s, pointFeature &pF);

	/*!
	 * \struct lineFeature
	 * \brief Structure that contains a line feature.
	 */
	struct lineFeature: public featureDescriptor
	{
		dLine ftre;//!< line feature

		/*!
		 * \fn lineFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Object constructor.
		 * \param val The value assigned to the feature unique identifier.
		 * \param C Color used to draw the line feature. The default value corresponds to color white.
		 */
		lineFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn set(dLine &val)
		 * \brief Copies dLine object val into the feature line stored in the object.
		 * \param val The dLine that is copied to the feature line.
		 */
		void set(dLine &val);

		/*!
		 * \fn apply(cv::Mat &I,  bool unboundLines=false)
		 * \brief Paint the line feature into the image I. 
		 * \param I The image where the feature will be painted.
		 * \param unboundLines A boolean parameter that signals wheter bound linefeature should also drawn a skinner unbound line.
		 */
		void apply(cv::Mat &I,  bool unboundLines=false);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, lineFeature &lF)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param lF A reference to an lineFeature object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a lineFeature object lF and writes it into an output stream.
	*/
	std::ostream &operator<< (std::ostream &s, lineFeature &lF);

	/*!
	 * \struct circleFeature
	 * \brief Structure that contains a circle feature.
	 */
	struct circleFeature: public featureDescriptor
	{
		dCircle ftre;//!< circle feature

		/*!
		 * \fn circleFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Object constructor.
		 * \param val The value assigned to the feature unique identifier.
		 * \param C Color used to draw the circle feature. The default value corresponds to color white.
		 */
		circleFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));

		/*!
		 * \fn set(dCircle &val)
		 * \brief Copies dCircle object val into the feature circle stored in the object.
		 * \param val The dCircle that is copied to the feature circle.
		 */
		void set(dCircle &val);

		/*!
		 * \fn apply(cv::Mat &I)
		 * \brief Paint the circle feature into the image I. 
		 * \param I The image where the feature will be painted.
		 */
		void apply(cv::Mat &I);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, circleFeature &cF)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param cF A reference to an circleFeature object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a circleFeature object cF and writes it into an output stream.
	*/
	std::ostream &operator<< (std::ostream &s, circleFeature &cF);

	/*!
	 * \struct markerFeature
	 * \brief Structure that contains a marker feature.
	 */
	struct markerFeature: public featureDescriptor
	{
		dPoint ftre; //!< marker feature position int the image.
		cv::MarkerTypes mType; //!< The type of the marker feature. The kind on marker are the ones used by the openCV highGUI library. 
		int mSize; //!< The size of the marker feature

		/*!
		 * \fn markerFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS)
		 * \brief Object constructor.
		 * \param val The value assigned to the object feature unique identifier.
		 * \param C Color used to draw the marker feature. The default value corresponds to color white.
		 * \param mt The marker type. If omitted the default marker type cv::MARKER_CROSS will be used.
		 */
		markerFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS);
		
		/*!
		 * \fn setIdType(u_int _id, cv::MarkerTypes mt = cv::MARKER_CROSS)
		 * \brief Sets if unique identifier and marker type attributes.
		 * \param _id The unique identifer value assigned to the object id attribute.
		 * \param mt The marker type value assigned to the object mType attribute.
		 */
		void setIdType(u_int _id, cv::MarkerTypes mt = cv::MARKER_CROSS);

		/*!
		 * \fn set(dPoint &val)
		 * \brief Sets the position of the marker in the image.
		 * \param val The dPoint object val is used to initialize the dPoint ftre attribute.
		 */
		void set(dPoint &val);

		/*!
		 * \fn setMarkerType(cv::MarkerTypes mt)
		 * \brief Sets the object attribute mType.
		 * \param mt The cv::MarkerType that is used to set the mType object attribute.
		 */
		void setMarkerType(cv::MarkerTypes mt);

		/*!
		 * \fn setMarkerSize(int ms)
		 * \brief Sets the object attribute mSize.
		 * \param ms The value that is used to set the mSize object attribute.
		 */
		void setMarkerSize(int ms);

		/*!
		 * \fn apply(cv::Mat &I)
		 * \brief Paint the marker feature into the image I. 
		 * \param I The image where the feature will be painted.
		 */
		void apply(cv::Mat &I);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, markerFeature &mF)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param mF A reference to an markerFeature object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a markerFeature object mF and writes it into an output stream.
	*/
	std::ostream &operator<< (std::ostream &s, markerFeature &mF);


	/*!
	 * \struct featureLayer
	 * \brief This structure organizes as set of features that will constitute a Layer of features.
	 * 
	 * This structure organizes as set of features that will constitute a Layer of features. The features
	 * contained in a layer will be drawn at the same time and will be drawn over features that have been
	 * drawn before.
	 */
	struct featureLayer
	{
		std::string name; //!< A string name of the feature layer.
		bool active; //!< A boolean value that indicate whether the layer is 'active' (is meant to be drawn) or not.
		std::vector<std::shared_ptr<featureDescriptor>> L; //!< A vector that contains the features stored in the layer. 

		/*!
		 * \fn featureLayer(const std::string &_name)
		 * \brief Object constructor. Sets the layer name and the active attribute as false.
		 * \param _name The name assigned to the name attribute.
		 */
		featureLayer(const std::string &_name);
		
		/*!
		 * \fn addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add an image feature to the layer, initialized with parameter I, unique identifier id and color C.
		 * \param I Image used to initialize the feature.
		 * \param id unique identifier of the feature.
		 * \param C Default color of the feature.
		 */
		void addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn addPointFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add a dPoint feature to the layer, initialized with parameter val, unique identifier id and color C.
		 * \param val A dLine object whose copy will be added to the layer.
		 * \param id The unique identifier of the feature.
		 * \param C Default color of the feature.
		 */
		void addPointFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addLineFeature(dLine &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add a dLine feature to the layer, initialized with parameter val, unique identifier id and color C.
		 * \param val A dLine object whose copy will be added to the layer.
		 * \param id The unique identifier of the feature.
		 * \param C Default color of the feature.
		 */
		void addLineFeature(dLine &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addCircleFeature(dCircle &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add a dCircle feature to the layer, initialized with parameter val, unique identifier id and color C.
		 * \param val A dCircle object whose copy will be added to the layer.
		 * \param id The unique identifier of the feature.
		 * \param C Default color of the feature.
		 */
		void addCircleFeature(dCircle &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addMarkerFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS)
		 * \brief Add a dPoint feature to the layer, initialized with parameter val, unique identifier id and color C.
		 * \param val A dPoint object that indicates the position of the Marker in the image.
		 * \param id The unique identifier of the feature.
		 * \param C Default color of the feature.
		 * \param mt The marker type value of the marker objecte added to the layer.
		 */
		void addMarkerFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS);
		
        /*!
         * \fn applyFeatures(cv::Mat &I, bool unboundLines)
         * \brief Paint all the layer features into the image I.
         * \param I The image where the features will be painted.
         * \param unboundLines A boolean parameter that signals wheter a bound line feature should also drawn a skinner unbound line.
         */
		void applyFeatures(cv::Mat &I, bool unboundLines);
	};

	/*!
	* \fn std::ostream &operator<< (std::ostream &s, featureLayer &fL)
	* \brief Overload the stream output operator.
	* \param s The object at the left of the operator <<. It is the output stream where the output will be written.
	* \param fL A reference to an featureLayer object whose attributes are formated and written into the stream s.
	* \return The stream s.
	* 
	* This methods formats a featureLayer object fL and writes it into an output stream.
	*/
	std::ostream &operator<<(std::ostream &s, featureLayer &fL);


	/*!
	 * \struct annotations
	 * \brief This struct keeps a collection of feature layers.
	 * 
	 * This collection is what we called 'annotations' of an image. When applied to the image
	 * the feature layers is done in a particular order, the upper layers painting the over the lower layers.
	 * The structure provide methos to add and remove layers, to add features to the exisiting layers, to set the 
	 * visibility of each layer (toggling their attribute 'active'), to change the drawing order and to apply the
	 * annotations to an Image. 
	 */
	struct annotations
	{
		unsigned int featureIdx; //!< This is the feature counter. it is used to set the unique identifier of 
		                         // a feature that is added to the object.
		int rows; //!< The number of rows of the image where the annotations will be drawn.
		int cols; //!< The number of cols of the image where the annotations will be drawn.
		std::map<std::string,unsigned int> idxMap; //!< A map that keeps the asociation between a featureLayer index and its name.  
		std::vector<featureLayer> Features; //!< The vector of feature layers, which contains the features.

		/*!
		 * \fn annotations(int r, int c);
		 * \brief Object constructor.
		 * \param r Value used to initialize the attribute rows.
		 * \param c Value used to initialize the attribute cols.
		 * 
		 * Initialize the rows and cols attributes and sets the featureIdx to 0.
		 */
		annotations(int r, int c);

		/*!
		 * \fn clear()
		 * \brief Cleans the objects structures and initilize featureIdx to 0.
		 */
		void clear();
		
		/*!
		 * \fn addLayer(const std::string &name)
		 * \brief Creates an empty featureLayer which is added to the Features vector.
		 * \param name The name of the new layer to be added.
		 */	
		void addLayer(const std::string &name);

		/*!
		 * \fn unsigned int getLayerIdx(const std::string &name)
		 * \brief Obtains the index of a layer.
		 * \param name The name of the layer whose name is needed.
		 * \return The index of the layer whose name is equal to the parameter 'name'.
		 */
		unsigned int getLayerIdx(const std::string &name);

		/*!
		 * \fn std::map<std::string, unsigned int>::iterator getLayerIterator(const std::string &name)
		 * \brief Gets the idxMap map iterator of the layer whose name is required. 
		 * \param name The name of the layer whose name is needed.
		 *  \return The idxMap iterator that corresponds to the layer whose name is equal to the parameter 'name'.
		 */
		std::map<std::string, unsigned int>::iterator getLayerIterator(const std::string &name);
		
		/*!
		 * \fn void moveLayerUp(const std::string &name)
		 * \brief Moves the layer up in the drawing order. 
		 * \param name The name of the layer to be moved up.
		 * 
		 * Moving a layer up implies drawing it earlier when appling it to an image.
		 */
		void moveLayerUp(const std::string &name);
		
		/*!
		 * \fn void moveLayerDown(const std::string &name)
		 * \brief Moves the layer down in the drawing order. 
		 * \param name The name of the layer to be moved down.
		 * 
		 * Moving a layer down implies drawing it later when appling it to an image.
		 */
		void moveLayerDown(const std::string &name);
		
		/*!
		 * \fn void activateLayer(const std::string &name)
		 * \brief Sets the attribute 'active' to the layer 'name' to true.
		 * \param name The name of the layer to be activated.
		 */
		void activateLayer(const std::string &name);
		
		/*!
		 * \fn void deactivateLayer(const std::string &name)
		 * \brief Sets the attribute 'active' to the layer 'name' to false.
		 * \param name The name of the layer to be deactivated.
		 */
		void deactivateLayer(const std::string &name);

		/*!
		 * \fn toggleLayer(const std::string &name)
		 * \brief Changes the attribute 'active' to the layer 'name' from false to true or from true to false.
		 * \param name The name of the layer to be toggled.
		 */
		void toggleLayer(const std::string &name);
		
		/*!
		 * \fn applyAnnotations(cv::Mat &I, bool unboundLines=false)
		 * \brief Paint all the layerd features into the image I.
         * \param I The image where the features will be painted.
         * \param unboundLines A boolean parameter that signals wheter a bound line feature should also drawn a skinner unbound line.
         */
		void applyAnnotations(cv::Mat &I, bool unboundLines=false);
		
		/*!
		 * \fn void addImageFeature(const std::string &name, cv::Mat &I, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add an image feature to the layer 'name', initialized with parameter I and color C.
		 * \param name The name of the layer where the image feature will be added.
		 * \param I Image used to initialize the image feature that will be added to the layer 'name'.
		 * \param C Default color of the feature.
		 */
		void addImageFeature(const std::string &name, cv::Mat &I, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addPointFeature(const std::string &name, dPoint &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add an point feature to the layer 'name', initialized with parameter val and color C.
		 * \param name The name of the layer where the dPoint feature will be added.
		 * \param val A dPoint object whose copy will be added to the layer 'name'.
		 * \param C Default color of the feature.
		 */
		void addPointFeature(const std::string &name, dPoint &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addLineFeature(const std::string &name, dLine &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add an line feature to the layer 'name', initialized with parameter val and color C.
		 * \param name The name of the layer where the dLine feature will be added.
		 * \param val A dLine object whose copy will be added to the layer 'name'.
		 * \param C Default color of the feature.
		 */		
		void addLineFeature(const std::string &name, dLine &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addCircleFeature(const std::string &name, dCircle &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		 * \brief Add an circle feature to the layer 'name', initialized with parameter val and color C.
		 * \param name The name of the layer where the dCircle feature will be added.
		 * \param val A dCircle object whose copy will be added to the layer 'name'.
		 * \param C Default color of the feature.
		 */	
		void addCircleFeature(const std::string &name, dCircle &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		/*!
		 * \fn void addMarkerFeature(const std::string &name, dPoint &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS)
		 * \brief Add an marker feature to the layer 'name', initialized with parameter val and color C.
		 * \param name The name of the layer where the dLine feature will be added.
		 * \param val A dPoint object that indicates the position of the Marker in the image.
		 * \param C Default color of the feature.
		 * \param mt The marker type value of the marker objecte added to the layer 'name'.
		 */	
		void addMarkerFeature(const std::string &name, dPoint &val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS);
	};
}
#endif