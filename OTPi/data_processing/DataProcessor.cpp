#include "DataProcessor.h"

DataProcessor::DataProcessor(Properties* properties) {
	isOoiDefined = false;
	isRegionDefined = false;
	isSendNotification = false;
	isFirstFrameDefined = false;
	sentOnce = false;
	cropCounter = 0;
	cameraInterface = new CameraInterface(std::stoi(properties->getProperty("CAM_INDEX")));

}

DataProcessor::~DataProcessor() {
	// TODO Auto-generated destructor stub
}

void DataProcessor::initialize() {
	cameraInterface->init();
}

ImgData* DataProcessor::run() {
	//while(true) {
		//cameraInterface->poll()->showImg("Test");
		//TODO: Filter image
		//TODO: Detect objects
		//TODO: Track objects

		//TODO: Show result
	logger->info("polling");
	//return cameraInterface->poll();
	cv::Mat src, src_gray, src_blur, src_diff, diff_threshold;
	cv::Mat dst, detected_edges, dst_temp;

	int edgeThresh = 1;
	int lowThreshold = 30;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	
	
	ImgData* temp = cameraInterface->poll();

	if(!isOoiDefined){
		src = temp->getImg();
		dst = src;
		dst_temp.create( src.size(), src.type() );
		cv::cvtColor( src, src_gray, CV_BGR2GRAY );
		cv::blur( src_gray, detected_edges, cv::Size(3,3) );
		cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
		//src = cv::Mat(2, 2, CV_8UC3, cv::Scalar(1,1,1));
		src.copyTo(dst_temp);
		src.setTo(cv::Scalar(255,255,255));
		//dst_temp = cv::Scalar::all(0);
		src.copyTo( dst_temp, detected_edges);
		temp->setImg(dst_temp);
	}

	else if(isOoiDefined && !isRegionDefined){
		logger->info("Here is OoiDefined "+std::to_string(ooi.x)+","+std::to_string(ooi.y));
		//distance transform
		src = temp->getImg();
		cv::cvtColor( src, src_gray, CV_BGR2GRAY );
		cv::blur( src_gray, detected_edges, cv::Size(3,3) );
		cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );


		temp->setImg(detected_edges);
		//find contours using ooi point
		//define region

		isRegionDefined = true;
	}

	else if(isRegionDefined){
		src = temp->getImg();
		double x_mod = ooi.x-300;
		double y_mod = ooi.y-300;
		// Setup a rectangle to define your region of interest
		if(ooi.x-300<0){
			x_mod = 10;
		}
		if(ooi.y-300<0){
			y_mod = 10;
		}
		if(ooi.x+300>1280){
			x_mod = 670;
		}
		if(ooi.y+300>960){
			y_mod = 350;
		}
		logger->info("Creating ROI with: "+std::to_string(x_mod)+","+std::to_string(y_mod));
		cv::Rect myROI(x_mod, y_mod, 600, 600);
		logger->info("ROI created: "+std::to_string(x_mod)+","+std::to_string(y_mod));

		// Crop the full image to that image contained by the rectangle myROI
		// Note that this doesn't copy the data
		cv::Mat croppedRef(src, myROI);

		cv::Mat cropped;
		// Copy the data into new matrix
		//cropped.create(cv::Size(100,100), croppedRef.type());
		//croppedRef.copyTo(cropped);
		src(myROI).copyTo(cropped);
		//crop image, set to temp
		if(!sentOnce){
			if(!isFirstFrameDefined){
				cv::cvtColor( cropped, src_gray, CV_BGR2GRAY );
				cv::blur( src_gray, src_blur, cv::Size(3,3) );
				src_blur.copyTo(first_frame);
				isFirstFrameDefined = true;
			}
			else{
				//TODO: send alert event if any movement

				cv::cvtColor( cropped, src_gray, CV_BGR2GRAY );
				cv::blur( src_gray, src_blur, cv::Size(3,3) );
				cv::absdiff( first_frame, src_blur, src_diff);
				cv::threshold(src_diff, diff_threshold, 25, 255, CV_THRESH_BINARY);
				double sum = cv::sum(diff_threshold)[0] + cv::sum(diff_threshold)[1] + cv::sum(diff_threshold)[2];
				if (sum > 5){
					logger->info("Sendnotification is being set to true and sum is:"+std::to_string(sum));
					isSendNotification=true;
					sentOnce = true;
				}
			}
		}
		/*if(sentOnce){
			cropCounter++;
		}*/
		logger->info("Crop counter is "+std::to_string(cropCounter));
		if(cropCounter>=5){
			isOoiDefined = false;
			isRegionDefined = false;
			isFirstFrameDefined = false;
			sentOnce = false;
			cropCounter = 0;
			logger->info("Resetting the values.");
		}
		temp->setImg(cropped);

	}

	return temp;

}

/*
void DataProcessor::FindContour(cv::Mat a, cv::Mat &image){
    cv::Mat temp;
    int x=0, y=0;
    int i;
    int largest=65535;
    a.copyTo(temp);
    cv::vector< vector<Point> > contours;
    cv::vector<Vec4i> hierarchy;
    cv::findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE );
    for (int index = 0; index >= 0; index = hierarchy[index][0]) {
         cv::Moments moment = moments(contours[index]);
         double area = moment.m00;
         int  a = moment.m10/area;
         int  b = moment.m01/area;
          i=std::sqrt((float)(a-50)^2+(b-60)^2);
           if (i<largest)
           {  x=a;
              y=b;
              largest=i;
              cout<<"x"<<x<<"y"<<y<<"i"<<i<<"/n";
           }

    }
       Point2i pt(x,y);
       circle(image,pt,20,cv::Scalar(0,255,0),2);
    putText(image,"object",cv::Point(x,y+30),1,1,cv::Scalar(0,255,0),2);
}

*/
