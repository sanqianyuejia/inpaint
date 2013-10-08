/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture.

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/

#if !defined(BAGUO_ClsApp_cpp)
#define BAGUO_ClsApp_cpp

#include "ClsApp.h"
using namespace baguo;

// 58����ֵ
double ClsApp::WUBA_XAXIS_A = 0.05882;
double ClsApp::WUBA_XAXIS_B = -3.64705;
double ClsApp::WUBA_YAXIS_A = 0.194256;
double ClsApp::WUBA_YAXIS_B = -0.405405;
int ClsApp::WUBA_BIG_WIDTH = 212;
int ClsApp::WUBA_BIG_HEIGHT = 62;
int ClsApp::WUBA_SMALL_WIDTH = 170;
int ClsApp::WUBA_SMALL_HEIGHT = 50;
int ClsApp::WUBA_PIXBOUNDARY = 640;
double ClsApp::WUBA_DELTA_X = 0.0;
double ClsApp::WUBA_DELTA_Y = 5.0;

// �ϼ�����ֵ
int ClsApp::GANJI_SMALL_H = 4;//3;
int ClsApp::GANJI_SMALL_W = 6;//5;
int ClsApp::GANJI_BIG_H = 17;//14;
int ClsApp::GANJI_BIG_W = 20;//17;
int ClsApp::GANJI_BIG_WIDTH = 138 ;
int ClsApp::GANJI_BIG_HEIGHT = 57;
int ClsApp::GANJI_SMALL_WIDTH = 110 ;
int ClsApp::GANJI_SMALL_HEIGHT = 30;
int ClsApp::GANJI_PIXBOUNDARY = 350;

// ���վ���ֵ
int ClsApp::BAIXING_TAILOR_H = 25;

string ClsApp::getClassName() const 
{ 
	return "ClsApp"; 
}
//---------------------------------------------------------------------------
//            ��һ����������ͨ���հ��ɰ�
//			  �ڶ�����������ˮӡ��Сһ�µĵ�ͨ���Ǻ�ͼƬ
//			  ���������ڿհ��ɰ�������ROI����
//			  ���Ĳ������Ǻ�ͼƬ�������հ��ɰ��ROI����
//---------------------------------------------------------------------------
bool ClsApp::createMask(IplImage *src, MaskRect maskrect, IplImage *&mask)
{
	if (src == NULL)
	{
		return false;
	}

	// mask�Ƿ���ͼƬ����Ч��Χ��
	if (src->width <= maskrect.width || src->height <= maskrect.height)
	{
		return false;
	}

	// ������Դͼ��Сһ�µĵ�ͨ���հ��ɰ�
	mask = cvCreateImage(cvSize(src->width, src->height), src->depth, 1);
	memset(mask->imageData, 0, sizeof(uchar)*mask->width*mask->height);

	// ������ˮӡ��Сһ�µĵ�ͨ��ͼƬ
	IplImage *tmp = cvCreateImage(cvSize(maskrect.width, maskrect.height), src->depth, 1);
	memset(tmp->imageData, 255, sizeof(uchar)*tmp->width*tmp->height);

	// ����ָ��ROI����
	cvSetImageROI(mask, cvRect(maskrect.point.x-maskrect.width, 
		maskrect.point.y-maskrect.height, maskrect.width, maskrect.height));

	// �����ɰ�
	cvCopy(tmp, mask, 0);

	// ����ROI
	cvResetImageROI(mask);

	// �ͷ���ʱͼƬ��Դ
	cvReleaseImage(&tmp);

	return true;
}
//---------------------------------------------------------------------------

bool ClsApp::createMask(ClsPicture *src, MaskRect maskrect, ClsPicture *&mask)
{
	if (src == NULL || src->_ipldata == NULL || mask == NULL)
	{
		return false;
	}

	// mask�Ƿ���ͼƬ����Ч��Χ��
	if (src->_ipldata->width <= maskrect.width || src->_ipldata->height <= maskrect.height)
	{
		return false;
	}

	// ������Դͼ��Сһ�µĵ�ͨ���հ��ɰ�
	mask->_ipldata = cvCreateImage(cvSize(src->_ipldata->width, src->_ipldata->height), src->_ipldata->depth, 1);
	memset(mask->_ipldata->imageData, 0, sizeof(uchar)*mask->_ipldata->width*mask->_ipldata->height);

	// ������ˮӡ��Сһ�µĵ�ͨ��ͼƬ
	IplImage *tmp = cvCreateImage(cvSize(maskrect.width, maskrect.height), src->_ipldata->depth, 1);
	memset(tmp->imageData, 255, sizeof(uchar)*tmp->width*tmp->height);

	// ����ָ��ROI����
	cvSetImageROI(mask->_ipldata, cvRect(maskrect.point.x-maskrect.width, 
		maskrect.point.y-maskrect.height, maskrect.width, maskrect.height));

	// �����ɰ�
	cvCopy(tmp, mask->_ipldata, 0);

	// ����ROI
	cvResetImageROI(mask->_ipldata);

	// �ͷ���ʱͼƬ��Դ
	cvReleaseImage(&tmp);

	return true;
}
//---------------------------------------------------------------------------
//            ���½�x�����꣺y = a1*x + b1;	�����У�x��ͼƬ��ȣ�
//			  ���½�y�����꣺y = a2*x + b2;	�����У�x��ͼƬ�߶ȣ�
//---------------------------------------------------------------------------
bool ClsApp::computeParams(IplImage *src, MarkType type, MaskRect &maskrect)
{
	if (src == NULL)
	{
		return false;
	}

	int width, height;
	
	// ԴͼƬ�ߴ�
	width = src->width;
	height = src->height;

	if (type == MARKTYPE_58)
	{
		// �����ɰ�ߴ�
		if (width > WUBA_PIXBOUNDARY)
		{
			maskrect.width = WUBA_BIG_WIDTH;
			maskrect.height = WUBA_BIG_HEIGHT;
		}
		else
		{
			maskrect.width = WUBA_SMALL_WIDTH;
			maskrect.height = WUBA_SMALL_HEIGHT;
		}

		// ���������λ��
		int temp_x = width - (int)(WUBA_XAXIS_A*width + WUBA_XAXIS_B) + WUBA_DELTA_X;
		int temp_y = height - (int)(WUBA_YAXIS_A*height + WUBA_YAXIS_B) + WUBA_DELTA_Y;
		maskrect.point.x = (temp_x > width) ? width : temp_x;
		maskrect.point.y = (temp_y > height) ? height : temp_y;
	}	
	else if (type == MARKTYPE_GANJI)
	{
		if (width > GANJI_PIXBOUNDARY)
		{
			// �����ɰ�ߴ�
			maskrect.width = GANJI_BIG_WIDTH;
			maskrect.height = GANJI_BIG_HEIGHT;

			// ���������λ��
			maskrect.point.x = width - GANJI_BIG_W;
			maskrect.point.y = height - GANJI_BIG_H;
		}
		else
		{
			maskrect.width = GANJI_SMALL_WIDTH;
			maskrect.height = GANJI_SMALL_HEIGHT;

			maskrect.point.x = width - GANJI_SMALL_W;
			maskrect.point.y = height - GANJI_SMALL_H;
		}
	}
	else
	{
		return false;
	}

	// �����Ƿ���ͼƬ����Ч��Χ��
	if (maskrect.point.x <= 0 || maskrect.point.y <= 0
		|| maskrect.point.x-maskrect.width <= 0
		|| maskrect.point.y-maskrect.height <= 0)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------------
bool ClsApp::computeParams(ClsPicture *src, MarkType type, MaskRect &maskrect)
{
	if (src == NULL || src->_ipldata == NULL)
	{
		return false;
	}

	int width, height;

	// ԴͼƬ�ߴ�
	width = src->_ipldata->width;
	height = src->_ipldata->height;

	if (type == MARKTYPE_58)
	{
		// �����ɰ�ߴ�
		if (width > WUBA_PIXBOUNDARY)
		{			
			maskrect.width = WUBA_BIG_WIDTH;
			maskrect.height = WUBA_BIG_HEIGHT;
		}
		else
		{	
			maskrect.width = WUBA_SMALL_WIDTH;
			maskrect.height = WUBA_SMALL_HEIGHT;
		}


		// ���������λ��
		int temp_x = width - (int)(WUBA_XAXIS_A*width + WUBA_XAXIS_B) + WUBA_DELTA_X;
		int temp_y = height - (int)(WUBA_YAXIS_A*height + WUBA_YAXIS_B) + WUBA_DELTA_Y;
		maskrect.point.x = (temp_x > width) ? width : temp_x;
		maskrect.point.y = (temp_y > height) ? height : temp_y;
	}	
	else if (type == MARKTYPE_GANJI)
	{
		
		if (width > GANJI_PIXBOUNDARY)
		{
			// �����ɰ�ߴ�
			maskrect.width = GANJI_BIG_WIDTH;
			maskrect.height = GANJI_BIG_HEIGHT;

			// ���������λ��
			maskrect.point.x = width - GANJI_BIG_W;
			maskrect.point.y = height - GANJI_BIG_H;
		}
		else
		{
			maskrect.width = GANJI_BIG_WIDTH;
			maskrect.height = GANJI_BIG_HEIGHT;

			maskrect.point.x = width - GANJI_SMALL_W;
			maskrect.point.y = height - GANJI_SMALL_H;
		}
	}
	else
	{
		return false;
	}
	
	// �����Ƿ���ͼƬ����Ч��Χ��
	if (maskrect.point.x <= 0 || maskrect.point.y <= 0
		|| maskrect.point.x-maskrect.width <= 0
		|| maskrect.point.y-maskrect.height <= 0)
	{
		return false;
	}

	return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//			��һ��������Logo��Դͼˮӡ���غ϶�
//			�ڶ���������ROI����
//			������������ˮӡ
//-----------------------------------------------------------------------------
bool ClsApp::addWaterMark(ClsPicture *&src, ClsPicture *logo, MaskRect maskrect, double weight)
{
	if (src == NULL || logo == NULL)
	{
		return false;
	}

	// watermark�Ƿ���ͼƬ����Ч��Χ��
	if (src->_matdata.rows <= logo->_matdata.rows 
		|| src->_matdata.cols <= logo->_matdata.cols)
	{
		return false;
	}


	int delta_x, delta_y, x, y, w, h;

	// ����Logo��Դͼˮӡ���غ϶�
	w = logo->_matdata.cols;
	h = logo->_matdata.rows;
	x = maskrect.point.x;	
	y = maskrect.point.y;

	delta_x = maskrect.width - w;
	delta_y = maskrect.height - h;

	if (delta_x > 0) x = x - delta_x/2;
	if (delta_y > 0) y = y - delta_y/2;	

	// ����ָ��ROI����
	Mat tmp = src->_ipldst;
	Mat roi = tmp(cv::Rect(x-w, y-h, w, h));

	// ����ˮӡ
	addWeighted(roi, 1.0, logo->_matdata, weight, 0, roi);

	// ������Ŀ��
	IplImage tmpIpl = (IplImage)tmp;
	cvCopy(&tmpIpl, src->_ipldst);
	
	// �ͷ���ʱ��Դ
	tmp.release();
	roi.release();

	return true;
}
//-----------------------------------------------------------------------------

int ClsApp::getTailorHeight()
{
	return BAIXING_TAILOR_H;
}


#endif // !defined(BAGUO_ClsApp_cpp)