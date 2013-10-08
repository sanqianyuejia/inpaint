/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture. 

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsProc_h)
#define BAGUO_ClsProc_h

#include "ClsObject.h"
#include "ClsPicture.h"
#include <cv.h>
#include <opencv2/opencv.hpp>
#include <vector>
using std::vector;

namespace baguo 
{
	//----------------------------------------------------------------------
	//  provide a set of algorithms from opencv
	// 
	//	@inpaint @tailor
	//	
	//----------------------------------------------------------------------
	class ClsProc : public ClsObject
	{
	public:
		virtual string getClassName() const;

		/// 
		/// inpaint watermark from picture
		/// 
		/// @return true when ok
		/// 
		static bool inpaint(const vector<IplImage > src, const IplImage *mask, vector<IplImage *> &dst);
		static bool inpaint(ClsPicture *&pic, ClsPicture *mask);
		static bool inpaint(ClsPicture *&pic, IplImage *mask);

		/// 
		/// cut bottom section from picture
		/// 
		/// @return true when ok
		/// 
		static bool tailor(IplImage *src, int height, IplImage *&dst);
		static bool tailor(ClsPicture *&pic, int height);

	protected:
		static const double INPAINT_RANGE;
	};

}

#endif // !defined(BAGUO_ClsProc_h)