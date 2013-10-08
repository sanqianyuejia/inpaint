/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture. 

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsPicture_h)
#define BAGUO_ClsPicture_h

#include "ClsObject.h"
#include <cv.h>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace baguo 
{
	//----------------------------------------------------------------------
	//  provide a set of operation with picture
	// 
	//	@read @transfer @save @split @merge @reset
	// 
	//----------------------------------------------------------------------
	class ClsPicture : public ClsObject
	{
	public:
		explicit ClsPicture();
		explicit ClsPicture(const char *filepath);
		virtual ~ClsPicture();
		virtual string getClassName() const;

		/// 
		/// set file path
		/// 
		/// @return true when ok
		/// 
		void setFilePath(const char *filepath);

		/// 
		/// load image data to IplImage
		/// 
		/// @return true when ok
		/// 
		bool loadToIplImage(int iscolor=1);


		/// 
		/// load image data to matrix 
		/// 
		/// @return true when ok
		/// 
		bool loadToMat(int flags=1);


		/// 
		/// split matrix of color image to single channel
		/// 
		/// @return true when ok
		/// 
		bool splitChannel(int nchannels);


		/// 
		/// merge single channel to mixed channel
		/// 
		/// @return true when ok
		/// 
		bool mergeChannel();

		/// 
		/// initialize
		/// 
		/// @return true when ok
		/// 
		bool initDstVector();

		/// 
		/// save image
		/// 
		/// @return true when ok
		/// 
		bool saveImage(const char *filepath, const IplImage *src = NULL);


		void copyIplImageToMat();
		void copyMatToIplImage();


		/// 
		/// reset image
		/// 
		/// @return
		/// 
		void resetImage();

	private:
		void _init();
		bool _initialized;
		char _filepath[256];

	public:
		vector<IplImage> _iplvector;
		IplImage *_ipldata;
		vector<Mat> _matvector;
		Mat _matdata;
		vector<IplImage *> _dstvector;
		IplImage *_ipldst;
	};

}

#endif // !defined(BAGUO_ClsPicture_h)