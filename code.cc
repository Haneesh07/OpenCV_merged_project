
#include <opencv2\opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "object_localiser.h"
#include "feature_detector.h"
#include "feature_matcher.h"
#include "getopt.h"
#include "getdir.h"
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgcodecs.hpp"
//Function main
int main(int argc, char *argv[])
{
	//read the input images and stroring it variables image_1 and image_2
	cv::Mat image_1 = cv::imread("C:/Users/Dell/bazel_project/assignment/second.jpg");
	cv::Mat image_2 = cv::imread("C:/Users/Dell/bazel_project/assignment/main.jpg");
	cv::Mat image_3 = cv::imread("C:/Users/Dell/bazel_project/assignment/oriented.jpg");
	cv::Mat image_4 = cv::imread("C:/Users/Dell/bazel_project/assignment/light.jpg");
	cv::Mat image_5 = cv::imread("C:/Users/Dell/bazel_project/assignment/contour.jpg");
	cv::Mat image_6 = cv::imread("C:/Users/Dell/bazel_project/assignment/secondcontour.jpg");
	cv::Mat image_7 = cv::imread("C:/Users/Dell/bazel_project/assignment/flipped.jpg");   //no output
	cv::Mat image_8 = cv::imread("C:/Users/Dell/bazel_project/assignment/flipor.jpg");     //no output
	cv::Mat image_9 = cv::imread("C:/Users/Dell/bazel_project/assignment/invertedor.jpg");   //no output 

	// if statement/loop checks the presence of imput images
	if (image_1.empty() || image_2.empty() || image_3.empty() || image_4.empty() || image_5.empty() || image_6.empty() || image_7.empty() || image_8.empty())
	{
		std::cout << "Could not open image/s." << std::endl;
		return -1;
	}

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	//THRESHOLD IMAGE
	//variables taken to store the output image and theshold image
	cv::Mat result_opicc, sss;
	//random number grneration for random border colour
	cv::RNG rng(12345);

	// cvtColor (Original, result_opicc,CV_RGB2HSV);// this convert the image to HSV
	cv::cvtColor(image_2, result_opicc, CV_BGR2HSV);
	// erode and dilate process the image output
	cv::erode(result_opicc, result_opicc, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7)));
	cv::erode(result_opicc, result_opicc, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7)));
	cv::dilate(result_opicc, result_opicc, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7)));
	cv::dilate(result_opicc, result_opicc, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7)));
	// inRange defines the range for colour blue
	cv::inRange(result_opicc, cv::Scalar(100, 25, 25), cv::Scalar(120, 225, 225), sss); //Scalar(H_min,S_min,V_min), Scalar(H_max,S_max,V_max)

	cv::imshow("Input_first_image", image_2); // open the window for input image

	cv::imshow("Randomcoloured_Image", result_opicc); //open the window for output image

	cv::imshow("Threshold_component", sss); //open the window for threshold image having blue colour detected
	cv::imwrite(cv::String("Output threshold.jpg"), sss);
	cv::imwrite(cv::String("Randomcoloured.jpg"), result_opicc);
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	//FEATURE DETECTION
	// function for feature detection
	feature_detector detector;
	char chh;
	std::cout << "Would you like to see case a,b: \n ";
	std::cout << "Case a will detech the features of the original input image \n";
	std::cout << "Case b will detech the features of the second contour input image \n";
	std::cout << "Case c will detech the features of the  first contour input image \n";
	std::cin >> chh;
	std::cout << chh << std::endl;
	switch (char(chh))
	{
	case 'a':
	{
		//Oriented FAST and Rotated BRIEF (ORB) used for detecting keypoints
		detector.ORB(image_2, &image_2);
		//displays the input image
		cv::imshow("Image", image_2);
		// writes the output image in Out 2.jpg format
		cv::imwrite(cv::String("Out 2.jpg"), image_2);
	}
	break;

	case 'b':
	{
		detector.ORB(image_6, &image_6);
		//displays the input image
		cv::imshow("Image", image_6);
		// writes the output image in Out 2.jpg format
		cv::imwrite(cv::String("Out 3.jpg"), image_6);
	}
	break;
    case 'c':
	{
		detector.ORB(image_5, &image_5);
		//displays the input image
		cv::imshow("Image", image_5);
		// writes the output image in Out 2.jpg format
		cv::imwrite(cv::String("Out 11.jpg"), image_5);
	}
	break;
	}
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	// CONTOUR OF TWO INPUT IMAGES
	//function for finding contour of input image-original

	int cho;
	std::cout << "Would you like to see case 1,2,3: \n ";
	std::cout << "Case 1 will show contour image of first input image  \n\n Case 2 will show the second input image contour \n\n Else enter 3 for both images ";
	std::cin >> cho;
	std::cout << cho << std::endl;
	switch (int(cho))
	{
	label_1:
	{
	case 1:
		{

			cv::Mat gray, vector, Point, contours, hierarchy, Vec4i, Sc;
			cv::cvtColor(image_2, gray, CV_BGR2GRAY);
			cv::Canny(gray, gray, 100, 200, 3);
			std::vector<std::vector<cv::Point>> contours_1;
			vector<Vec4i> hierarchy;
			cv::findContours(gray, contours_1, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
			/// Draw contours
			cv::Mat drawing = cv::Mat::zeros(gray.size(), CV_8UC3);
			for (int i = 0; i < contours_1.size(); i++)
			{
				cv::Scalar c = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				cv::drawContours(drawing, contours_1, i, c, 2, 8, hierarchy, 0, cv::Point());
			}

			cv::imshow("Result window for First Input Image", drawing);
			cv::imwrite(cv::String("Outputc1.jpg"), drawing);
		}
		break;
	}
	label_2:
	{
	case 2:
		{
			//function for finding contour of input image-second
			cv::Mat gray_1, P, vector, contourm, hierarchy_1, Vec4i_1, Sc_1;
			cv::cvtColor(image_1, gray_1, CV_BGR2GRAY);
			cv::Canny(gray_1, gray_1, 100, 200, 3);
			std::vector<std::vector<cv::Point>> contour2;
			vector<Vec4i_1> hierarchy_1;
			cv::findContours(gray_1, contour2, hierarchy_1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
			/// Draw contours
			cv::Mat drawing_1 = cv::Mat::zeros(gray_1.size(), CV_8UC3);
			for (int j = 0; j < contour2.size(); j++)
			{
				cv::Scalar c1 = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				cv::drawContours(drawing_1, contour2, j, c1, 2, 8, hierarchy_1, 0, cv::Point());
			}

			cv::imshow("Result window for Second Image", drawing_1);
			cv::imwrite(cv::String("Outputc2.jpg"), drawing_1);
		}
		break;
	}
    case 3:
    	{
			goto label_1; 
			goto label_2;
		}	
			break;
	}
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	// FEATURE MATCHING WITH CASES
	//function for feature matching
	fm::feature_matcher matcher;
	//variable to store the output image
	cv::Mat output_imagee;
	char ch;
	std::cout << "Would you like to see case a,b,c,d,e,f: \n ";
	std::cout << "Case a will match the two original input images \n";
	std::cout << "Case b will match the second input image with oriented input image \n";
	std::cout << "Case c will match the second input image with low light input image \n";
	std::cout << "Case d will match the second input image with flipped and oriented input image \n";
	std::cout << "Case e will match the second contour input image with first contour input image \n";
	std::cout << "Case f will match the second input image with flipped input image \n";
	std::cout << "Case g will match the second input image with inverted and oriented input image \n";
	std::cin >> ch;
	std::cout << ch << std::endl;
	switch (char(ch))
	{
	// keypoint detector for feature matching in OpenCV
	case 'a':
	{
		matcher.BRISK(image_1, image_2, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 10.jpg"), output_imagee);
	}
	break;

	case 'b':
	{
		matcher.BRISK(image_1, image_3, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 4.jpg"), output_imagee);
	}
	break;
	case 'c':
	{
		matcher.BRISK(image_1, image_4, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 5.jpg"), output_imagee);
	}
	break;
	case 'd':
	{
		matcher.BRISK(image_1, image_8, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 6.jpg"), output_imagee);
	}
	break;
	case 'e':
	{
		matcher.BRISK(image_6, image_5, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 7.jpg"), output_imagee);
	}
	break;
	case 'f':
	{
		matcher.BRISK(image_1, image_7, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 8.jpg"), output_imagee);
	}
	break;
	case 'g':
	{
		matcher.BRISK(image_1, image_9, &output_imagee);

		cv::imshow("Image", output_imagee);

		cv::imwrite(cv::String("Out 9.jpg"), output_imagee);
	}
	break;
	}
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	// waits for a key
	cv::waitKey(0);
	//destroys all opened windows after a key is pressed
	cv::destroyAllWindows();

	return 0;
}