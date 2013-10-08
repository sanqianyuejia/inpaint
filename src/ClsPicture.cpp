/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture. 

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsPicture_cpp)
#define BAGUO_ClsPicture_cpp

// #ifdef WIN32
// 	#include  <io.h>
// 	#include <direct.h>
// #else
// 	#include <sys/io.h>
// #endif
#include <io.h>
#include "ClsPicture.h"
using namespace baguo;

ClsPicture::ClsPicture() 
{
	_ipldata = NULL;
	_ipldst = NULL;
	_initialized = false; 
}
//-------------------------------------------------------------------------

ClsPicture::ClsPicture(const char *filepath) 
{	
	setFilePath(filepath);		
}
//-------------------------------------------------------------------------
ClsPicture::~ClsPicture() {}
//-------------------------------------------------------------------------

string ClsPicture::getClassName() const 
{ 
	return "ClsPicture"; 
}
//-------------------------------------------------------------------------

void ClsPicture::setFilePath(const char *filepath) 
{ 
	_init();
	sprintf(_filepath, "%s", filepath);
}
//-------------------------------------------------------------------------

void ClsPicture::_init() 
{
	memset(_filepath, 0, sizeof(char)*256);
	_ipldata = NULL;
	_ipldst = NULL;
	_iplvector.clear();
	_matvector.clear();
	_matdata.release();
	_dstvector.clear();
	_initialized = true; 
}
//-------------------------------------------------------------------------
bool ClsPicture::loadToIplImage(int iscolor/* =1 */)
{
	if (_initialized == false)
	{
		return false;
	}

	_ipldata = cvLoadImage(_filepath, iscolor);	
	return true;
}
//---------------------------------------------------------------------------

bool ClsPicture::loadToMat(int flags/* =1 */)
{
	if (_initialized == false)
	{
		return false;
	}

	_matdata = imread(_filepath, flags);
	return true;
}
//-------------------------------------------------------------------------
bool ClsPicture::mergeChannel()
{
	if (_initialized == false) 
	{
		return false;
	}

	_ipldst = cvCreateImage(cvGetSize(_dstvector.at(0)), _dstvector.at(0)->depth, _ipldata->nChannels);
	cvMerge(_dstvector.at(0), _dstvector.at(1), _dstvector.at(2), 0, _ipldst);
	
	return true;
}
//-------------------------------------------------------------------------
bool ClsPicture::splitChannel(int nchannels)
{
	if (_initialized == false || nchannels != 3) {
		return false;
	}

	// split
	split(_matdata, _matvector);
	for (int i=0; i<nchannels;i++) _iplvector.push_back(_matvector.at(i));

	return true;
}
//---------------------------------------------------------------------------
bool ClsPicture::initDstVector()
{
	if (_initialized == false) 
	{
		return false;
	}

	for (int i=0; i<_ipldata->nChannels; i++)
	{
		_dstvector.push_back(cvCreateImage(cvGetSize(_ipldata), _ipldata->depth, 1));
	}

	//cvCreateImage(cvGetSize(_ipldata), _ipldata->depth, _ipldata->nChannels);
	return true;
}
//--------------------------------------------------------------------------
bool ClsPicture::saveImage(const char *filepath, const IplImage *src /* = NULL */)
{
	if (src == NULL)
	{
		cvSaveImage(filepath, _ipldst);
	}
	else
	{
		cvSaveImage(filepath, src);
	}

	return true;
}

void ClsPicture::resetImage()
{

	if (_ipldata != NULL) cvReleaseImage(&_ipldata);
	if (_ipldst != NULL) cvReleaseImage(&_ipldst);
	_matdata.release();

	for (unsigned int i=0; i<_matvector.size(); i++) 
	{
		_matvector.at(i).release();
	}
	for (unsigned int i=0; i<_dstvector.size(); i++) 
	{
		cvReleaseImage(&_dstvector.at(i));
	}

	_initialized = false;
}

void ClsPicture::copyIplImageToMat()
{
	Mat tmp = _ipldst;
	tmp.copyTo(_matdata);	
	tmp.release();
}

void ClsPicture::copyMatToIplImage()
{
	// _ipldst = &(IplImage)_matdata;
	IplImage tmp = (IplImage) _matdata;
	cvCopy(&tmp, _ipldst);
}

#endif // !defined(BAGUO_ClsPicture_cpp)