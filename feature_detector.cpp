#include "feature_detector.h"

//class feature_detector is created with constructor and destructor
feature_detector::feature_detector()
{
}


feature_detector::~feature_detector()
{
}

const bool feature_detector::ORB(const cv::Mat & in, cv::Mat * out)
{

	//pointer Ptr uses ORB detector for finding keypoints in image. 
	cv::Ptr<cv::ORB> detector = cv::ORB::create();

	std::vector<cv::KeyPoint> key_points;

	detector->detect(in, key_points);

	cv::drawKeypoints(in, key_points, *out, cv::Scalar(0, 0, 255));

	return true;
}

const bool feature_detector::BRISK(const cv::Mat & in, cv::Mat * out)
{

	//pointer Ptr uses BRISK detector for finding keypoints in image. 
	cv::Ptr<cv::BRISK> detector = cv::BRISK::create();

	std::vector<cv::KeyPoint> key_points;

	detector->detect(in, key_points);

	cv::drawKeypoints(in, key_points, *out, cv::Scalar(0, 0, 255));

	return true;
}
