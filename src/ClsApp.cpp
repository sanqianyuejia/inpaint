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

// 58经验值
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

// 赶集经验值
int ClsApp::GANJI_SMALL_H = 4;//3;
int ClsApp::GANJI_SMALL_W = 6;//5;
int ClsApp::GANJI_BIG_H = 17;//14;
int ClsApp::GANJI_BIG_W = 20;//17;
int ClsApp::GANJI_BIG_WIDTH = 138 ;
int ClsApp::GANJI_BIG_HEIGHT = 57;
int ClsApp::GANJI_SMALL_WIDTH = 110 ;
int ClsApp::GANJI_SMALL_HEIGHT = 30;
int ClsApp::GANJI_PIXBOUNDARY = 350;

// 百姓经验值
int ClsApp::BAIXING_TAILOR_H = 25;

string ClsApp::getClassName() const 
{ 
	return "ClsApp"; 
}
//---------------------------------------------------------------------------
//            第一步：创建单通道空白蒙板
//			  第二步：创建跟水印大小一致的单通道非黑图片
//			  第三步：在空白蒙板上设置ROI区域
//			  第四步：将非黑图片拷贝至空白蒙板的ROI区域
//---------------------------------------------------------------------------
bool ClsApp::createMask(IplImage *src, MaskRect maskrect, IplImage *&mask)
{
	if (src == NULL)
	{
		return false;
	}

	// mask是否在图片的有效范围内
	if (src->width <= maskrect.width || src->height <= maskrect.height)
	{
		return false;
	}

	// 创建与源图大小一致的单通道空白蒙板
	mask = cvCreateImage(cvSize(src->width, src->height), src->depth, 1);
	memset(mask->imageData, 0, sizeof(uchar)*mask->width*mask->height);

	// 创建与水印大小一致的单通道图片
	IplImage *tmp = cvCreateImage(cvSize(maskrect.width, maskrect.height), src->depth, 1);
	memset(tmp->imageData, 255, sizeof(uchar)*tmp->width*tmp->height);

	// 设置指定ROI区域
	cvSetImageROI(mask, cvRect(maskrect.point.x-maskrect.width, 
		maskrect.point.y-maskrect.height, maskrect.width, maskrect.height));

	// 拷贝蒙板
	cvCopy(tmp, mask, 0);

	// 重置ROI
	cvResetImageROI(mask);

	// 释放临时图片资源
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

	// mask是否在图片的有效范围内
	if (src->_ipldata->width <= maskrect.width || src->_ipldata->height <= maskrect.height)
	{
		return false;
	}

	// 创建与源图大小一致的单通道空白蒙板
	mask->_ipldata = cvCreateImage(cvSize(src->_ipldata->width, src->_ipldata->height), src->_ipldata->depth, 1);
	memset(mask->_ipldata->imageData, 0, sizeof(uchar)*mask->_ipldata->width*mask->_ipldata->height);

	// 创建与水印大小一致的单通道图片
	IplImage *tmp = cvCreateImage(cvSize(maskrect.width, maskrect.height), src->_ipldata->depth, 1);
	memset(tmp->imageData, 255, sizeof(uchar)*tmp->width*tmp->height);

	// 设置指定ROI区域
	cvSetImageROI(mask->_ipldata, cvRect(maskrect.point.x-maskrect.width, 
		maskrect.point.y-maskrect.height, maskrect.width, maskrect.height));

	// 拷贝蒙板
	cvCopy(tmp, mask->_ipldata, 0);

	// 重置ROI
	cvResetImageROI(mask->_ipldata);

	// 释放临时图片资源
	cvReleaseImage(&tmp);

	return true;
}
//---------------------------------------------------------------------------
//            右下角x轴坐标：y = a1*x + b1;	（其中，x是图片宽度）
//			  右下角y轴坐标：y = a2*x + b2;	（其中，x是图片高度）
//---------------------------------------------------------------------------
bool ClsApp::computeParams(IplImage *src, MarkType type, MaskRect &maskrect)
{
	if (src == NULL)
	{
		return false;
	}

	int width, height;
	
	// 源图片尺寸
	width = src->width;
	height = src->height;

	if (type == MARKTYPE_58)
	{
		// 计算蒙板尺寸
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

		// 计算坐标点位置
		int temp_x = width - (int)(WUBA_XAXIS_A*width + WUBA_XAXIS_B) + WUBA_DELTA_X;
		int temp_y = height - (int)(WUBA_YAXIS_A*height + WUBA_YAXIS_B) + WUBA_DELTA_Y;
		maskrect.point.x = (temp_x > width) ? width : temp_x;
		maskrect.point.y = (temp_y > height) ? height : temp_y;
	}	
	else if (type == MARKTYPE_GANJI)
	{
		if (width > GANJI_PIXBOUNDARY)
		{
			// 计算蒙板尺寸
			maskrect.width = GANJI_BIG_WIDTH;
			maskrect.height = GANJI_BIG_HEIGHT;

			// 计算坐标点位置
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

	// 坐标是否在图片的有效范围内
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

	// 源图片尺寸
	width = src->_ipldata->width;
	height = src->_ipldata->height;

	if (type == MARKTYPE_58)
	{
		// 计算蒙板尺寸
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


		// 计算坐标点位置
		int temp_x = width - (int)(WUBA_XAXIS_A*width + WUBA_XAXIS_B) + WUBA_DELTA_X;
		int temp_y = height - (int)(WUBA_YAXIS_A*height + WUBA_YAXIS_B) + WUBA_DELTA_Y;
		maskrect.point.x = (temp_x > width) ? width : temp_x;
		maskrect.point.y = (temp_y > height) ? height : temp_y;
	}	
	else if (type == MARKTYPE_GANJI)
	{
		
		if (width > GANJI_PIXBOUNDARY)
		{
			// 计算蒙板尺寸
			maskrect.width = GANJI_BIG_WIDTH;
			maskrect.height = GANJI_BIG_HEIGHT;

			// 计算坐标点位置
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
	
	// 坐标是否在图片的有效范围内
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
//			第一步：计算Logo与源图水印的重合度
//			第二步：设置ROI区域
//			第三步：拷贝水印
//-----------------------------------------------------------------------------
bool ClsApp::addWaterMark(ClsPicture *&src, ClsPicture *logo, MaskRect maskrect, double weight)
{
	if (src == NULL || logo == NULL)
	{
		return false;
	}

	// watermark是否在图片的有效范围内
	if (src->_matdata.rows <= logo->_matdata.rows 
		|| src->_matdata.cols <= logo->_matdata.cols)
	{
		return false;
	}


	int delta_x, delta_y, x, y, w, h;

	// 计算Logo与源图水印的重合度
	w = logo->_matdata.cols;
	h = logo->_matdata.rows;
	x = maskrect.point.x;	
	y = maskrect.point.y;

	delta_x = maskrect.width - w;
	delta_y = maskrect.height - h;

	if (delta_x > 0) x = x - delta_x/2;
	if (delta_y > 0) y = y - delta_y/2;	

	// 设置指定ROI区域
	Mat tmp = src->_ipldst;
	Mat roi = tmp(cv::Rect(x-w, y-h, w, h));

	// 拷贝水印
	addWeighted(roi, 1.0, logo->_matdata, weight, 0, roi);

	// 拷贝至目标
	IplImage tmpIpl = (IplImage)tmp;
	cvCopy(&tmpIpl, src->_ipldst);
	
	// 释放临时资源
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