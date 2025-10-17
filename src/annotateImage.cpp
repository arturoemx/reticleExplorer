#include <annotateImage.h>
#include <ostream>

	imNote::featureDescriptor::featureDescriptor(uint val, cv::Scalar_<uchar> C)
	{
		id = val;
		type = None;
		Color[0] = C[0];
		Color[1] = C[1];
		Color[2] = C[2];
	}
	void imNote::featureDescriptor::setId(u_int _id)
	{
		id = _id;
	}
	void imNote::featureDescriptor::setColor(cv::Scalar_<uchar> C)
	{
		Color[0] = C[0];
		Color[1] = C[1];
		Color[2] = C[2];
	}

	imNote::imageFeature::imageFeature(uint val, cv::Scalar_<uchar> C):imNote::featureDescriptor(val, C)
	{
		type = image;
	}

	void imNote::imageFeature::set(cv::Mat &I)
	{
		ftre = I;
	}

	void imNote::imageFeature::apply(cv::Mat &I)
	{
		cv::Vec3b *apuI, *endI;
		uchar *apuF;
		int i;

		for (i=0; i < I.rows; ++i)
		{
			apuF = ftre.ptr<uchar>(i);
			apuI  = I.ptr<cv::Vec3b>(i);
			endI  = apuI + I.cols;
			for (;apuI < endI; ++apuI, ++apuF)
				if (*apuF)
					*apuI = Color;
		}
	}

	std::ostream &imNote::operator<< (std::ostream &s, imNote::imageFeature &iF)
	{
		s << "Img:[" << iF.ftre.rows << "x" << iF.ftre.cols << "x" << iF.ftre.channels() <<"]";
		return s;
	}

	imNote::pointFeature::pointFeature(uint val, cv::Scalar_<uchar> C):imNote::featureDescriptor(val, C)
	{
		type = point;
	}
	void imNote::pointFeature::set(dPoint &val)
	{
		ftre = val;
	}
	void imNote::pointFeature::apply(cv::Mat &I)
	{
		I.at<cv::Vec3b>((int)rintf(ftre.cy), (int)rintf(ftre.cx)) = Color;
	}

	std::ostream &imNote::operator<< (std::ostream &s, imNote::pointFeature &pF)
	{
		s << pF.ftre;
		return s;
	}

	imNote::lineFeature::lineFeature(uint val, cv::Scalar_<uchar> C):imNote::featureDescriptor(val, C)
	{
		type = line;
	}
	
	void imNote::lineFeature::set(dLine &val)
	{
		ftre = val;
	}

	void imNote::lineFeature::apply(cv::Mat &I)
	{
		if (!ftre.unbound)	
			cv::line(I, cv::Point((int)rintf(ftre.x1),(int)rintf(ftre.y1)),
			            cv::Point((int)rintf(ftre.x2),(int)rintf(ftre.y2)),
			            Color, ftre.thickness, ftre.lineType);
		//else to Be Done Case of unbounded line.
	}

	std::ostream &imNote::operator<< (std::ostream &s, imNote::lineFeature &lF)
	{
		s << lF.ftre;
		return s;
	}

	imNote::circleFeature::circleFeature(uint val, cv::Scalar_<uchar> C):imNote::featureDescriptor(val, C)
	{
		type = circle;
	}

	void imNote::circleFeature::set(dCircle &val)
	{
		ftre = val;
	}
	
	void imNote::circleFeature::apply(cv::Mat &I)
	{
		cv::circle(I, cv::Point((int)rint(ftre.h), (int)rint(ftre.k)), (int)rint(ftre.r), Color, ftre.thickness, ftre.lineType);
	}

	std::ostream &imNote::operator<< (std::ostream &s, imNote::circleFeature &cF)
	{
		s << cF.ftre;
		return s;
	}

	imNote::markerFeature::markerFeature(uint val, cv::Scalar_<uchar> C, cv::MarkerTypes mt):imNote::featureDescriptor(val, C)
	{
		mType = mt;
		mSize = 20;
		type = marker;
	}

	void imNote::markerFeature::setIdType(u_int _id, cv::MarkerTypes mt)
	{
		id = _id;
		mType = mt;
	}

	void imNote::markerFeature::set(dPoint &val)
	{
		ftre = val;
	}

	void imNote::markerFeature::setMarkerType(cv::MarkerTypes mt)
	{
		mType = mt;
	}
	
	void imNote::markerFeature::setMarkerSize(int ms)
	{
		mSize = ms;
	}

	void imNote::markerFeature::apply(cv::Mat &I)
	{
		cv::drawMarker(I, cv::Point((int)rint(ftre.cx), (int)rint(ftre.cy)), Color, mType, mSize, ftre.thickness, ftre.lineType);
	}

	std::ostream &imNote::operator <<(std::ostream &s, imNote::markerFeature &mF)
	{
		s << mF.ftre << "|";
		switch (mF.mType)
		{
			case cv::MARKER_CROSS:
				s << "CROSS1";
				break;
			case cv::MARKER_TILTED_CROSS:
				s << "CROSS2";
				break;
			case cv::MARKER_STAR:
				s << "STAR  ";
				break;
			case cv::MARKER_DIAMOND:
				s << "DIAMND";
				break;
			case cv::MARKER_SQUARE:
				s << "SQUARE";
				break;
			case cv::MARKER_TRIANGLE_UP:
				s << "TRIUP ";
				break;
			case cv::MARKER_TRIANGLE_DOWN:
				s << "TRIDWN";
				break;
		}
		return s;
	}

	imNote::featureLayer::featureLayer(const std::string &_name, int _r, int _c)
	{	
		name = _name;
		active = false;
	}

	void imNote::featureLayer::addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C)
	{
		std::shared_ptr<imageFeature> ptr(new imageFeature(id, C));
		ptr->set(I);
		L.push_back(ptr);
	}


	void imNote::featureLayer::addPointFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C)
	{
		std::shared_ptr<pointFeature> ptr(new pointFeature(id, C));
		ptr->set(val);
		L.push_back(ptr);
	}

	void imNote::featureLayer::addLineFeature(dLine &val, u_int id, cv::Scalar_<uchar> C)
	{
		std::shared_ptr<lineFeature> ptr(new lineFeature(id, C));
		ptr->set(val);
		L.push_back(ptr);
	}
	
	void imNote::featureLayer::addCircleFeature(dCircle &val, u_int id, cv::Scalar_<uchar> C)
	{
		std::shared_ptr<circleFeature> ptr(new circleFeature(id, C));
		ptr->set(val);
		L.push_back(ptr);
	}

	void imNote::featureLayer::addMarkerFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C, cv::MarkerTypes mt)
	{
		std::shared_ptr<markerFeature> ptr(new markerFeature(id, C, mt));
		ptr->set(val);
		L.push_back(ptr);
	}

	void imNote::featureLayer::applyFeatures(cv::Mat &I)
	{
		featureDescriptor *ptr;
		std::vector<std::shared_ptr<featureDescriptor>>::iterator it, end;

		it = L.begin();
		end = L.end();
		for (; it != end; ++it)
		{
			ptr = it->get();

			switch(ptr->type)
			{
				case image:
						((imageFeature *)ptr)->apply(I);
					break;
				case point:
						((pointFeature *)ptr)->apply(I);
					break;
				case line:
						((lineFeature *)ptr)->apply(I);
					break;
				case circle:
						((circleFeature *)ptr)->apply(I);
					break;	
				case marker:
						((markerFeature *)ptr)->apply(I);
				default:break;
			}
		}
	}

	std::ostream &imNote::operator<<(std::ostream &s, imNote::featureLayer &fL)
	{
		int i, tope;
		imNote::featureDescriptor *ptr;
		std::vector<std::shared_ptr<imNote::featureDescriptor>>::iterator it;

		s << "Feature Layer Name: " << fL.name << std::endl;
		if (fL.active == true)
			s <<  "Active!"  << std::endl;
		else
			s <<  "Active!" << std::endl;
        s << "No. of features   : " << fL.L.size() << std::endl << "Features: [";

		it = fL.L.begin();
		tope = (int)fL.L.size();
		for (i = 0; i < tope; ++it, ++i)
		{
			ptr = it->get();

	        switch(ptr->type)
			{
				case image:			
					s << *((imNote::imageFeature *)ptr);
					break;
				case point:
					s << *((imNote::pointFeature *)ptr);
					break;
				case line:
					s << *((imNote::lineFeature *)ptr);
					break;
				case circle:
					s << *((imNote::circleFeature *)ptr);
					break;	
				case marker:
					s << *((imNote::markerFeature *)ptr);
				default:break;
			}
			if (i + 1 < tope)
				s << ",";
			else
				s << "]";

		}
		return s;
	}


	/*************************************************************
	 * 
	 *   ANNOTATIONS
	 * 
	 *************************************************************
	 */

	imNote::annotations::annotations(int r, int c)
	{
		if (r <=0 || c <= 0)
		{
			std::cerr << "Error in annotations constructor." << std::endl;
			std::cerr.flush();
			return;
		}
		rows = r;
		cols = c;
		featureIdx = 0;
	}

	void imNote::annotations::clear()
	{
		featureIdx = 0;
		idxMap.clear();
		Features.clear();
	}
	
	void imNote::annotations::addLayer(const std::string &name)
	{
		unsigned int idx;
		

		try
		{
			idx = idxMap.at(name);
		}
		catch(std::out_of_range& e)
		{
			featureLayer ly(name, rows, cols);

			idx = Features.size();
			idxMap[name] = idx;
			ly.active = true;
			Features.push_back(ly);
			return;
		}
#ifdef __VERBOSE__
		std::cerr << "Error in imNote::annotations::addLayer(" << name << "): "
		          << "Layer already exisist." << std::endl;
#endif		       
	}

	unsigned int imNote::annotations::getLayerIdx(const std::string &name)
	{
		unsigned int idx;

		try
		{
			idx = idxMap.at(name);
		}
		catch(std::out_of_range& e)
		{
			std::cerr << "Error: annotations::getLayerIdx " << e.what() << "=> key out of range: "<< std::endl;
			throw;
			return idxMap.size();
		}
		return idx;
	}

	std::map<std::string, unsigned int>::iterator imNote::annotations::getLayerIterator(const std::string &name)
	{
		std::map<std::string, unsigned int>::iterator it;

		try
		{
			it = idxMap.find(name);
		}
		catch(std::out_of_range& e)
		{
			std::cerr << "Error: annotations::getLayerIterator("<< name << ") " << e.what()
			          << "=> key out of range: "<< std::endl;
			throw;
			return idxMap.end();
		}
		return it;
	}

	void imNote::annotations::moveLayerUp(const std::string &name)
	{
		unsigned int idx;
		std::vector<featureLayer>::iterator it, itPrev;
		std::string tmpName;

		try
		{
			idx = getLayerIdx(name);
		}
		catch(std::exception &e)
		{
			std::cerr << "Couldn't move up Layer " << name
			          << ", it doesnt exist." << std::endl;
			return;
		}

		if (idx == 0)
		{
#ifdef __VERBOSE__
		std::cerr << "Couldn't move up Layer " << name
			          << ", already on top." << std::endl;
#endif
			return;
		}

		it = Features.begin() + idx;
		itPrev = it - 1;

		tmpName = itPrev->name;
		std::iter_swap(it, itPrev);
		idxMap[name] = idx - 1;
		idxMap[tmpName] = idx;
	}

	void imNote::annotations::moveLayerDown(const std::string &name)
	{
		unsigned int idx;
		std::vector<featureLayer>::iterator it, itNext;
		std::string tmpName;

		try
		{
			idx = getLayerIdx(name);
		}
		catch(std::exception &e)
		{
			std::cerr << "Couldn't move down Layer " << name
			          << ", it doesnt exist." << std::endl;
			return;
		}

		if (idx == Features.size() - 1)
			{
#ifdef __VERBOSE__
		std::cerr << "Couldn't move down Layer " << name
			          << ", already at the bottom." << std::endl;	
#endif
			return;
		}

		it = Features.begin() + idx;
		itNext = it + 1;

		tmpName = itNext->name;
		std::iter_swap(it, itNext);
		idxMap[name] = idx + 1;
		idxMap[tmpName] = idx;
	}

	void imNote::annotations::activateLayer(const std::string &name)
	{
		unsigned int idx;

		try
		{
			idx = getLayerIdx(name);
		}
		catch(std::exception &e)
		{
			std::cerr << "Couldn't activate Layer " << name
			          << ", it doesnt exist.";
			return;
		}

		Features[idx].active = true;
	}

	void imNote::annotations::deactivateLayer(const std::string &name)
	{
		unsigned int idx;

		try
		{
			idx = getLayerIdx(name);
		}
		catch(std::exception &e)
		{
			std::cerr << "Couldn't deactivate Layer " << name
			          << ", it doesnt exist.";
			return;
		}

		Features[idx].active = false;
	}

	void imNote::annotations::toggleLayer(const std::string &name)
	{
		unsigned int idx;

		try
		{
			idx = getLayerIdx(name);
		}
		catch(std::exception &e)
		{
			std::cerr << "Couldn't toggle Layer " << name
			          << ", it doesnt exist.";
			return;
		}

		if (Features[idx].active == true)
			Features[idx].active = false;
		else
			Features[idx].active = true;
	}

	void imNote::annotations::applyAnnotations(cv::Mat &I)
	{
		unsigned int i, N;

		if (I.rows != rows || I.cols != cols || I.channels() != 3)
		{
			std::cerr <<"Error in annotations::applyAnnotation."
			          << std::endl << "Differente Image size."
			          << std::endl
			          << "[" << I.rows << " ," << I.cols << ", " << I.channels() << "]" << std::endl;
			return;
		}

		N = Features.size();
		for (i = 0;i < N; ++i)
			if (Features[i].active == true)
				Features[i].applyFeatures(I);
	}

	void imNote::annotations::addImageFeature(const std::string &name, cv::Mat &I, cv::Scalar_<uchar> C)
	{
		unsigned int idx = getLayerIdx(name);

		Features[idx].addImageFeature(I, featureIdx++, C);

	}

	void imNote::annotations::addPointFeature(const std::string &name, dPoint &val, cv::Scalar_<uchar> C)
	{
		unsigned int idx = getLayerIdx(name);

		Features[idx].addPointFeature(val, featureIdx++, C);
	}
	
	void imNote::annotations::addLineFeature(const std::string &name, dLine &val, cv::Scalar_<uchar> C)
	{
		unsigned int idx = getLayerIdx(name);

		Features[idx].addLineFeature(val, featureIdx++, C);
	}

	void imNote::annotations::addCircleFeature(const std::string &name, dCircle &val, cv::Scalar_<uchar> C)
	{
		unsigned int idx = getLayerIdx(name);

		Features[idx].addCircleFeature(val, featureIdx++, C);
	}

	void imNote::annotations::addMarkerFeature(const std::string &name, dPoint &val, cv::Scalar_<uchar> C, cv::MarkerTypes mt)
	{
		unsigned int idx = getLayerIdx(name);

		Features[idx].addMarkerFeature(val, featureIdx++, C);
	}
