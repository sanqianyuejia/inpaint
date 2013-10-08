/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture. 

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsProc_cpp)
#define BAGUO_ClsProc_cpp

#include "ClsProc.h"
using namespace baguo;

const double ClsProc::INPAINT_RANGE = 3.0;	// Ëã·¨°ë¾¶

string ClsProc::getClassName() const 
{ 
	return "ClsProc"; 
}
//------------------------------------------------------------------------

bool ClsProc::inpaint(const vector<IplImage> src, const IplImage *mask, vector<IplImage *> &dst)
{
	if (src.size() <= 0 || mask == NULL)
	{
		return false;
	}

	// inpaint
	for (unsigned int i=0; i<src.size(); i++)
	{
		cvInpaint(&src.at(i), mask, dst.at(i), INPAINT_RANGE, CV_INPAINT_TELEA);
	}

	return true;
}
//---------------------------------------------------------------------------

bool ClsProc::inpaint(ClsPicture *&pic, ClsPicture *mask)
{
	if (pic->_iplvector.size() <= 0 
		|| pic->_dstvector.size() <= 0
		|| mask->_ipldata == NULL)
	{
		return false;
	}

	for (unsigned int i=0; i<pic->_iplvector.size(); i++)
	{
		cvInpaint(&pic->_iplvector.at(i), mask->_ipldata, 
			pic->_dstvector.at(i), INPAINT_RANGE, CV_INPAINT_TELEA);
	}

	return true;
}
//-----------------------------------------------------------------------------------

bool ClsProc::inpaint(ClsPicture *&pic, IplImage *mask)
{
	if (pic->_iplvector.size() <= 0 
		|| pic->_dstvector.size() <= 0
		|| mask == NULL)
	{
		return false;
	}

	for (unsigned int i=0; i<pic->_iplvector.size(); i++)
	{
		cvInpaint(&pic->_iplvector.at(i), mask, 
			pic->_dstvector.at(i), INPAINT_RANGE, CV_INPAINT_TELEA);
	}

	return true;
}

bool ClsProc::tailor(IplImage *src, int height, IplImage *&dst)
{
	if (height < 0 || src == NULL || height >= src->height)
	{
		return false;
	}

	int h = src->height - height;
	int w = src->width;
	// create destination image
	dst = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, src->nChannels);

	// set roi rect
	cvSetImageROI(src, cvRect(0, 0, w, h));

	// copy data
	cvCopy(src, dst, 0);

	// reset roi
	cvResetImageROI(src);

	return true;
}
//------------------------------------------------------------------------

bool ClsProc::tailor(ClsPicture *&pic, int height)
{
	if (pic == NULL || height >= pic->_ipldata->height)
	{
		return false;
	}

	int h = pic->_ipldata->height - height;
	int w = pic->_ipldata->width;
	// create destination image
	pic->_ipldst = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, pic->_ipldata->nChannels);

	// set roi rect
	cvSetImageROI(pic->_ipldata, cvRect(0, 0, w, h));

	// copy data
	cvCopy(pic->_ipldata, pic->_ipldst, 0);

	// reset roi
	cvResetImageROI(pic->_ipldata);

	return true;
}

#endif // !defined(BAGUO_ClsProc_cpp)