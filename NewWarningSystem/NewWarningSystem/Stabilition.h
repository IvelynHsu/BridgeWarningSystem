#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

#pragma once
class Stabilition
{
private:
    cv::Mat_<float> rigidTransform;
    std::vector<cv::Point2f> trackedFeatures;
    cv::Mat gray;
    cv::Mat prevGray;
    cv::Mat mask;
    cv::Mat warped;
public:
	Stabilition(void);
	~Stabilition(void);
	IplImage* processImage(IplImage* src,bool debug, bool dark );
	void setupROI(int rows, int cols);
	void cannyEdgeDetection() ;
	cv::Mat_<float>& getRigidTransform();
	cv::Mat& getMask();
};

