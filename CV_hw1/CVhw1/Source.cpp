#include<highgui.h>
#include<cv.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

uchar Blue[512][512];
uchar Green[512][512];
uchar Red[512][512];
uchar Gray[512][512];
uchar Intensity[512][512];

uchar Blue2[341][490];
uchar Green2[341][490];
uchar Red2[341][490];
uchar Gray2[341][490];
uchar Intensity2[341][490];

int main()
{
	//////////////////////////////////////"I1.jpg"////////////////////////////////////////
	//Gray
	char* pictureFileName = "I1.jpg";
	IplImage*picture = cvLoadImage(pictureFileName, 1);

	for (int i = 0; i < picture->height; i++)
	{
		for (int j = 0; j < picture->widthStep; j = j + 3)
		{
			Blue[i][(int)j / 3] = picture->imageData[i*picture->widthStep + j];
			Green[i][(int)j / 3] = picture->imageData[i*picture->widthStep + j + 1];
			Red[i][(int)j / 3] = picture->imageData[i*picture->widthStep + j + 2];
		}
	}

	for (int i = 0; i < picture->height; i++)
	{
		for (int j = 0; j < picture->widthStep; j++)
		{
			Gray[i][j] = (uchar)(Red[i][j] * 0.299 + Green[i][j] * 0.587 + Blue[i][j] * 0.114);
			Blue[i][j] = Gray[i][j];
			Green[i][j] = Gray[i][j];
			Red[i][j] = Gray[i][j];
		}
	}

	for (int i = 0; i < picture->height; i++)
	{
		for (int j = 0; j < picture->widthStep; j = j + 3)
		{
			picture->imageData[i*picture->widthStep + j] = Blue[i][(int)j / 3];
			picture->imageData[i*picture->widthStep + j + 1] = Green[i][(int)j / 3];
			picture->imageData[i*picture->widthStep + j + 2] = Red[i][(int)j / 3];
		}
	}
	cvSaveImage("I1_gray.jpg", picture);
	cvShowImage("I1_gray", picture);


	//Threshold
	char* pictureFileName_gray = "I1_gray.jpg";
	IplImage* picture_gray = cvLoadImage(pictureFileName_gray, 1);

	int Threshold = 100;

	for (int i = 0; i < picture_gray->height; i++)
	{
		for (int j = 0; j < picture_gray->widthStep; j = j + 3)
		{
			Blue[i][(int)j / 3] = picture_gray->imageData[i*picture->widthStep + j];
			Green[i][(int)j / 3] = picture_gray->imageData[i*picture->widthStep + j + 1];
			Red[i][(int)j / 3] = picture_gray->imageData[i*picture->widthStep + j + 2];
		}
	}

	for (int i = 0; i < picture_gray->height; i++)
	{
		for (int j = 0; j < picture_gray->widthStep; j++)
		{
			if (Gray[i][j]>Threshold)
			{
				Blue[i][j] = 255;
				Green[i][j] = 255;
				Red[i][j] = 255;
				Gray[i][j] = 255;
			}
			else
			{
				Blue[i][j] = 0;
				Green[i][j] = 0;
				Red[i][j] = 0;
				Gray[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < picture_gray->height; i++)
	{
		for (int j = 0; j < picture_gray->widthStep; j = j + 3)
		{
			picture_gray->imageData[i*picture_gray->widthStep + j] = Blue[i][(int)j / 3];
			picture_gray->imageData[i*picture_gray->widthStep + j + 1] = Green[i][(int)j / 3];
			picture_gray->imageData[i*picture_gray->widthStep + j + 2] = Red[i][(int)j / 3];
		}
	}

	cvSaveImage("I1_threshold.jpg", picture_gray);
	cvShowImage("I1_threshold", picture_gray);

	//Intensity
	char *pictureFileName_Intensity = "I1.jpg";
	IplImage *picture_Intensity = cvLoadImage(pictureFileName_Intensity, 1);

	for (int i = 0; i < picture_Intensity->height; i++)
	{
		for (int j = 0; j < picture_Intensity->widthStep; j = j + 3)
		{
			Blue[i][(int)j / 3] = picture_Intensity->imageData[i*picture_Intensity->widthStep + j];
			Green[i][(int)j / 3] = picture_Intensity->imageData[i*picture_Intensity->widthStep + j + 1];
			Red[i][(int)j / 3] = picture_Intensity->imageData[i*picture_Intensity->widthStep + j + 2];
		}
	}

	for (int i = 0; i < picture_Intensity->height; i++)
	{
		for (int j = 0; j < picture_Intensity->widthStep; j++)
		{
			Intensity[i][j] = (int)(Blue[i][j] + Green[i][j] + Red[i][j]) / 3;
			Blue[i][j] = Intensity[i][j];
			Green[i][j] = Intensity[i][j];
			Red[i][j] = Intensity[i][j];
		}
	}

	for (int i = 0; i < picture_Intensity->height; i++)
	{
		for (int j = 0; j < picture_Intensity->widthStep; j = j + 3)
		{
			picture_Intensity->imageData[i*picture_Intensity->widthStep + j] = Blue[i][(int)j / 3];
			picture_Intensity->imageData[i*picture_Intensity->widthStep + j + 1] = Green[i][(int)j / 3];
			picture_Intensity->imageData[i*picture_Intensity->widthStep + j + 2] = Red[i][(int)j / 3];
		}
	}
	cvSaveImage("I1_Intensity.jpg", picture_Intensity);
	cvShowImage("I1_Intensity", picture_Intensity);

	//Rotate
	IplImage *picture_Rotate1 = cvLoadImage("I1.jpg", 1);;
	IplImage *picture_Rotate2;
	CvSize pictureSize2 = cvSize(512, 512);
	picture_Rotate2 = cvCreateImage(pictureSize2, IPL_DEPTH_8U, 3);


	for (int i = 0; i<picture_Rotate1->height; i++)
	{
		for (int j = 0; j<picture_Rotate1->widthStep; j = j + 3)
		{
			Blue[i][(int)(j / 3)] = picture_Rotate1->imageData[i*picture_Rotate1->widthStep + j];
			Green[i][(int)(j / 3)] = picture_Rotate1->imageData[i*picture_Rotate1->widthStep + j + 1];
			Red[i][(int)(j / 3)] = picture_Rotate1->imageData[i*picture_Rotate1->widthStep + j + 2];


		}
	}

	for (int i = 0; i<picture_Rotate2->height; i++)
	{
		for (int j = 0; j<picture_Rotate2->widthStep; j = j + 3)
		{
			picture_Rotate2->imageData[i*picture_Rotate2->widthStep + j] = Blue[picture_Rotate2->width - (int)j / 3][i];
			picture_Rotate2->imageData[i*picture_Rotate2->widthStep + j + 1] = Green[picture_Rotate2->width - (int)j / 3][i];
			picture_Rotate2->imageData[i*picture_Rotate2->widthStep + j + 2] = Red[picture_Rotate2->width - (int)j / 3][i];

		}
	}
	
	cvSaveImage("I1_Rotate.jpg", picture_Rotate2);
	cvShowImage("I1_Rotate", picture_Rotate2);

	////////////////////////////////////"I2.jpg"////////////////////////////////////////////////
	//Gray
	char* imgFileName = "I2.jpg";
	IplImage*img = cvLoadImage(imgFileName,1);
	
	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->widthStep; j = j + 3)
		{
			Blue2[i][(int)j / 3] = img->imageData[i*img->widthStep + j];
			Green2[i][(int)j / 3] = img->imageData[i*img->widthStep + j + 1];
			Red2[i][(int)j / 3] = img->imageData[i*img->widthStep + j + 2];
		}
	}

	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->widthStep; j++)
		{
			Gray2[i][j] = (uchar)(Red2[i][j] *0.299 +Green2[i][j] *0.587 +Blue2[i][j]*0.114);  
			Blue2[i][j] = Gray2[i][j];
			Green2[i][j] = Gray2[i][j];
			Red2[i][j] = Gray2[i][j];
		}
	}

	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->widthStep; j = j + 3)
		{
			img->imageData[i*img->widthStep + j] = Blue2[i][(int)j / 3];
			img->imageData[i*img->widthStep + j + 1] = Green2[i][(int)j / 3];
			img->imageData[i*img->widthStep + j + 2] = Red2[i][(int)j / 3];
		}
	}
	cvSaveImage("I2_gray.jpg",img );
	cvShowImage("I2_gray", img);
	

	//Threshold
	char* imgFileName_gray ="I2_gray.jpg";
	IplImage* img_gray = cvLoadImage(imgFileName_gray,1);

	int Threshold2 = 100;
	
	for (int i = 0; i < img_gray->height; i++)
	{
		for (int j = 0; j < img_gray->widthStep; j = j + 3)
		{
			Blue2[i][(int)j / 3] = img_gray->imageData[i*img->widthStep + j];
			Green2[i][(int)j / 3] = img_gray->imageData[i*img->widthStep + j + 1];
			Red2[i][(int)j / 3] = img_gray->imageData[i*img->widthStep + j + 2];
		}
	}
	
	for (int i = 0; i < img_gray->height; i++)
	{
		for (int j = 0; j < img_gray->widthStep; j++)
		{
			if (Gray2[i][j]>Threshold2)
			{
				Blue2[i][j] = 255;
				Green2[i][j] = 255;
				Red2[i][j] = 255;
				Gray2[i][j] = 255;
			}
			else
			{
				Blue2[i][j] = 0;
				Green2[i][j] = 0;
				Red2[i][j] = 0;
				Gray2[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < img_gray->height; i++)
	{
		for (int j = 0; j < img_gray->widthStep; j = j + 3)
		{
			img_gray->imageData[i*img_gray->widthStep + j] = Blue2[i][(int)j / 3];
			img_gray->imageData[i*img_gray->widthStep + j + 1] = Green2[i][(int)j / 3];
			img_gray->imageData[i*img_gray->widthStep + j + 2] = Red2[i][(int)j / 3];
		}
	}
	
	cvSaveImage("I2_threshold.jpg", img_gray);
	cvShowImage("I2_threshold", img_gray);

	//Intensity
	char *imgFileName_Intensity = "I2.jpg";
	IplImage *img_Intensity = cvLoadImage(imgFileName_Intensity, 1);

	for (int i = 0; i < img_Intensity->height; i++)
	{
		for (int j = 0; j < img_Intensity->widthStep; j = j + 3)
		{
			Blue2[i][(int)j / 3] = img_Intensity->imageData[i*img_Intensity->widthStep + j];
			Green2[i][(int)j / 3] = img_Intensity->imageData[i*img_Intensity->widthStep + j + 1];
			Red2[i][(int)j / 3] = img_Intensity->imageData[i*img_Intensity->widthStep + j + 2];
		}
	}

	for (int i = 0; i < img_Intensity->height; i++)
	{
		for (int j = 0; j < img_Intensity->widthStep; j++)   
		{
			Intensity2[i][j] = (int)(Blue2[i][j] +  Green2[i][j] + Red2[i][j]) / 3;
			Blue2[i][j] = Intensity2[i][j];
			Green2[i][j] = Intensity2[i][j];
			Red2[i][j] = Intensity2[i][j];
		}
	}

	for (int i = 0; i < img_Intensity->height; i++)
	{
		for (int j = 0; j < img_Intensity->widthStep; j = j + 3)
		{
			img_Intensity->imageData[i*img_Intensity->widthStep + j] = Blue2[i][(int)j / 3];
			img_Intensity->imageData[i*img_Intensity->widthStep + j + 1] =  Green2[i][(int)j / 3];
			img_Intensity->imageData[i*img_Intensity->widthStep + j + 2] = Red2[i][(int)j / 3];
		}
	}
	cvSaveImage("I2_Intensity.jpg", img_Intensity);
	cvShowImage("I2_Intensity", img_Intensity);

	//Rotate
	IplImage *img_Rotate1 = cvLoadImage("I2.jpg", 1);;	
	IplImage *img_Rotate2;
	CvSize ImageSize2 = cvSize(341, 490);
	img_Rotate2 = cvCreateImage(ImageSize2, IPL_DEPTH_8U, 3);

	for (int i = 0; i<img_Rotate1->height; i++)
	{
		for (int j = 0; j<img_Rotate1->widthStep; j = j + 3)
		{
			Blue2[i][(int)(j / 3)] = img_Rotate1->imageData[i*img_Rotate1->widthStep + j];
			Green2[i][(int)(j / 3)] = img_Rotate1->imageData[i*img_Rotate1->widthStep + j + 1];
			Red2[i][(int)(j / 3)] = img_Rotate1->imageData[i*img_Rotate1->widthStep + j + 2];

			
		}
	}

	for (int i = 0; i<img_Rotate2->height; i++)
	{
		for (int j = 0; j<img_Rotate2->widthStep; j = j + 3)
		{
			img_Rotate2->imageData[i*img_Rotate2->widthStep + j] = Blue2[img_Rotate2->width - (int)j / 3][i];
			img_Rotate2->imageData[i*img_Rotate2->widthStep + j + 1] = Green2[img_Rotate2->width - (int)j / 3][i];
			img_Rotate2->imageData[i*img_Rotate2->widthStep + j + 2] = Red2[img_Rotate2->width - (int)j / 3][i];

		}
	}

	cvSaveImage("I2_Rotate.jpg", img_Rotate2);
	cvShowImage("I2_Rotate", img_Rotate2);

	///////////////////////////ReleaseImage////////////////////////////////////
	cvWaitKey(0);
	cvReleaseImage(&picture);
	cvReleaseImage(&picture_gray);
	cvReleaseImage(&picture_Intensity);
	cvReleaseImage(&picture_Rotate1);
	cvReleaseImage(&picture_Rotate2);
	cvReleaseImage(&img);
	cvReleaseImage(&img_gray);
	cvReleaseImage(&img_Intensity);
	cvReleaseImage(&img_Rotate1);
	cvReleaseImage(&img_Rotate2);

	return 0;
}