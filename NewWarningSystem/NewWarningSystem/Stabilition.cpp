#include "stdafx.h"
#include "Stabilition.h"



Stabilition::Stabilition(void)
{
	rigidTransform = cv::Mat::eye(3,3,CV_32FC1); //affine 2x3 in a 3x3 matrix
}


Stabilition::~Stabilition(void)
{
}

IplImage* Stabilition::processImage(IplImage* src, bool debug = false, bool dark =false) {
        cv::Mat img = cv::cvarrToMat(src, true);
        

        cv::cvtColor(img,gray,CV_BGR2GRAY);
        cv::Mat gray_opt;
        equalizeHist( gray, gray_opt );

//        cv::blur( gray_opt, gray, cv::Size(5,5) );

		//cvReleaseImage(&src);

        cannyEdgeDetection();

        if (mask.empty()) {
            setupROI(gray.rows, gray.cols);
        }

        std::vector<cv::Point2f> corners;
        if(trackedFeatures.size() < 200) {
            cv::goodFeaturesToTrack(gray, corners, 300, 0.03, 10,mask);
            std::cout << "found " << corners.size() << " features\n";
            for (size_t i = 0; i < corners.size(); ++i) {

                trackedFeatures.push_back(corners[i]);
            }
        }

        if(!prevGray.empty()) {
            std::vector<uchar> status; std::vector<float> errors;
            cv::calcOpticalFlowPyrLK(prevGray,gray,trackedFeatures,corners,status,errors,cv::Size(10,10));

            if(cv::countNonZero(status) < status.size() * 0.8) {
                std::cout << "cataclysmic error, fresh start\n";
                rigidTransform = cv::Mat::eye(3,3,CV_32FC1);
                trackedFeatures.clear();
                prevGray.release();

                IplImage* result = cvCreateImage(cvSize(img.cols,img.rows),8,3);
                IplImage ipltemp=img;
                cvCopy(&ipltemp, result);
                return result;
            }

            cv::Mat_<float> newRigidTransform = cv::estimateRigidTransform(trackedFeatures,corners,false);
            cv::Mat_<float> nrt33 = cv::Mat_<float>::eye(3,3);
            newRigidTransform.copyTo(nrt33.rowRange(0,2));
            rigidTransform *= nrt33;

            trackedFeatures.clear();
            for (size_t i = 0; i < status.size(); ++i) {
                if(status[i]) {
                    trackedFeatures.push_back(corners[i]);
                }
            }
        }

        if (debug) {
            for (size_t i = 0; i < trackedFeatures.size(); ++i) {
                cv::circle(img,trackedFeatures[i],3,cv::Scalar(0,0,255),CV_FILLED);
            }
        }

        cv::Mat invTrans = rigidTransform.inv(cv::DECOMP_SVD);
        cv::warpAffine(img, warped,invTrans.rowRange(0,2),cv::Size());

        gray.copyTo(prevGray);

        if(dark==true)
		{
			cv::Mat warped_masked;
			warped.copyTo(warped_masked, mask); 
			IplImage* result = cvCreateImage(cvSize(warped_masked.cols,warped_masked.rows),8,3);
			IplImage ipltemp=warped_masked;
			cvCopy(&ipltemp, result);
			return result;
		}
		else
		{
			IplImage* result = cvCreateImage(cvSize(warped.cols,warped.rows),8,3);
			IplImage ipltemp=warped;
			cvCopy(&ipltemp, result);
			return result;
		}
}

void Stabilition::setupROI(int rows, int cols) {

        mask = cv::Mat::zeros(rows, cols, CV_8U);
        mask = cv::Scalar(255);

		//cv::Point pts[] = {
  //          cv::Point(0.10*mask.cols, mask.rows),
  //          cv::Point(0.15*mask.cols, 0.65*mask.rows),
  //          cv::Point(0.35*mask.cols, 0.30*mask.rows),
  //          cv::Point(0.65*mask.cols, 0.30*mask.rows),
  //          cv::Point(0.85*mask.cols, 0.65*mask.rows),
  //          cv::Point(0.90*mask.cols, mask.rows),
  //      };
		
        cv::Point pts[] = {
			cv::Point(0 , 0),

			cv::Point(mask.cols, 0),
            cv::Point(mask.cols, 0.07*mask.rows),
            cv::Point(0,  0.07*mask.rows),

        };

		cv::Point pts1[] = {
			cv::Point(0 , mask.rows),
			cv::Point(0 , 0.25*mask.rows),
            //cv::Point(0.10*mask.cols, 0.9*mask.rows),
            cv::Point(0.15*mask.cols, 0.25*mask.rows),
            cv::Point(0.25*mask.cols, 0.13*mask.rows),

            cv::Point(0.65*mask.cols, 0.13*mask.rows),
			cv::Point(0.85*mask.cols, 0.25*mask.rows),
			cv::Point(mask.cols, 0.25*mask.rows),
			cv::Point(mask.cols , mask.rows),

        };

        cv::fillConvexPoly(mask, pts, sizeof(pts)/sizeof(cv::Point), cv::Scalar(0));
		cv::fillConvexPoly(mask, pts1, sizeof(pts1)/sizeof(cv::Point), cv::Scalar(0));
}

void Stabilition::cannyEdgeDetection() 
{
        cv::Mat src, detected_edges, dst;
        gray.copyTo(src);

        cv::Canny( src, detected_edges, 40, 100, 3 );

        // use Canny's output as a mask to display the result
        dst = cv::Scalar::all(0);

        src.copyTo( dst, detected_edges);
        //imshow( "Canny", dst );
}

cv::Mat_<float>& Stabilition::getRigidTransform()
{
        return rigidTransform;
}

cv::Mat& Stabilition::getMask() 
{
        return mask;
}