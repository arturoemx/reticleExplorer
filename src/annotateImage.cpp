#include <annotateImage.h>


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
		feature = I;
	}

	void imNote::imageFeature::apply(cv::Mat &I)
	{
		cv::Vec3b *apuI, *endI;
		uchar *apuF;
		int i;

		for (i=0; i < I.rows; ++i)
		{
			apuF = feature.ptr<uchar>(i);
			apuI  = I.ptr<cv::Vec3b>(i);
			endI  = apuI + I.cols;
			for (;apuI < endI; ++apuI, ++apuF)
				if (*apuF)
					*apuI = Color;
		}
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

	imNote::featureLayer::featureLayer(std::string nme, int _r, int _c)
	{	
		name = nme;
		active = false;
		lyImage = cv::Mat::zeros(_r, _c, CV_8UC3);
	}

	void imNote::featureLayer::addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C)
	{
		if (I.rows != lyImage.rows || I.cols != lyImage.cols || I.channels() != 1)
		{
			std::cerr << "Error in addImageFeature" << std::endl;
			std::cerr.flush();
			return;
		}
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

	imNote::annotation::annotation(int r, int c)
	{
		if (r <=0 || c <= 0)
		{
			std::cerr << "Error in annotation constructor." << std::endl;
			std::cerr.flush();
			return;
		}
		rows = r;
		cols = c;
		nLayers = 0;
	}
	
	void imNote::annotation::addLayer(std::string name)
	{
		unsigned int idx;
		featureLayer ly(name, rows, cols);

		idx = Features.size();
		idxMap[name] = idx;

		ly.active = true;

		Features.push_back(ly);
	}

	void imNote::annotation::moveLayerUp(std::string name)
	{
		unsigned int idx;

		idx = idxMap[name];

		if (idx == 0)
			return;

		std::vector<featureLayer>::iterator it, prev;

		prev = Features.begin() + idx - 1;
		it = prev + 1;
		std::iter_swap(prev,it);
	}

	void imNote::annotation::moveLayerDown(std::string name)
	{
		unsigned int idx;

		idx = idxMap[name];

		if (idx == Features.size() - 1)
			return;

		std::vector<featureLayer>::iterator it, next;

		it = Features.begin() + idx;
		next = it + 1;
		std::iter_swap(it, next);
	}

	void imNote::annotation::activateLayer(std::string name)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].active = true;
	}

	void imNote::annotation::deactivateLayer(std::string name)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].active = false;
	}

	void imNote::annotation::applyAnnotations(cv::Mat &I)
	{
		unsigned int i, N;

		if (I.rows != rows || I.cols != cols || I.channels() != 3)
		{
			std::cerr <<"Error in annotation::applyAnnotation."
			          << std:: endl << "Differente Image size."
			          << std::endl;
			return;
		}

		N = Features.size();
		for (i = 0;i < N; ++i)
			if (Features[i].active == true)
				Features[i].applyFeatures(I);
	}

	void imNote::annotation::addImageFeature(std::string name, cv::Mat &I, u_int id, cv::Scalar_<uchar> C)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].addImageFeature(I, id, C);

	}

	void imNote::annotation::addPointFeature(std::string name, dPoint &val, u_int id, cv::Scalar_<uchar> C)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].addPointFeature(val, id, C);
	}
	
	void imNote::annotation::addLineFeature(std::string name, dLine &val, u_int id, cv::Scalar_<uchar> C)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].addLineFeature(val, id, C);
	}

	void imNote::annotation::addCircleFeature(std::string name, dCircle &val, u_int id, cv::Scalar_<uchar> C)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].addCircleFeature(val, id, C);
	}

	void imNote::annotation::addMarkerFeature(std::string name, dPoint &val, u_int id, cv::Scalar_<uchar> C, cv::MarkerTypes mt)
	{
		unsigned int idx;

		idx = idxMap[name];
		Features[idx].addMarkerFeature(val, id, C);
	}
