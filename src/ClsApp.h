/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture.

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsApp_h)
#define BAGUO_ClsApp_h

#include "ClsObject.h"
#include "ClsPicture.h"
#include <cv.h>
#include <opencv2/opencv.hpp>

namespace baguo 
{
	//----------------------------------------------------------------------
	//  第一步：计算水印的位置（长、宽、左上角的坐标）
	//  第二步：根据位置信息，产生蒙板、水印
	//  第三步：根据蒙板和水印，去除原水印、加上新水印
	//----------------------------------------------------------------------
	class ClsApp : public ClsObject
	{
	public:
		virtual string getClassName() const;

		/// 
		/// 功能：根据参数，产生蒙板
		/// 
		/// @param src 原图片
		/// @param maskrect 水印尺寸和位置信息
		/// @param mask 蒙板图片（输出参数）
		/// @return 
		/// 
		static bool createMask(IplImage *src, MaskRect maskrect, IplImage *&mask);

		/// 
		/// 功能：根据参数，产生蒙板
		/// 
		/// @param src 原图片
		/// @param maskrect 水印尺寸和位置信息
		/// @param mask 蒙板图片（输出参数）
		/// @return 
		/// 
		static bool createMask(ClsPicture *src, MaskRect maskrect, ClsPicture *&mask);

		/// 
		/// 功能：根据网站类型、原图，计算参数
		/// 
		/// @param src 原图片
		/// @param type 图片类别
		/// @param maskrect 水印尺寸和位置信息（输出参数）
		/// @return 
		/// 
		static bool computeParams(IplImage *src, MarkType type, MaskRect &maskrect);

		/// 
		/// 功能：根据网站类型、原图，计算参数
		/// 
		/// @param src 原图片
		/// @param type 图片类别
		/// @param maskrect 水印尺寸和位置信息输出参数）
		/// @return 
		/// 
		static bool computeParams(ClsPicture *src, MarkType type, MaskRect &maskrect);

		/// 
		/// 功能：根据参数，产生水印
		/// 
		/// @param src 原图片（输入、输出参数）
		/// @param logo Logo图片
		/// @param maskrect 水印尺寸和位置信息
		/// @param weight 水印权重,范围[0, 1]
		/// @return
		/// 
		static bool addWaterMark(ClsPicture *&src, ClsPicture *logo, MaskRect maskrect, double weight);
		
		/// 
		/// 功能：获取百姓网的裁剪尺寸
		/// 
		/// @return 裁剪尺寸
		/// 
		static int getTailorHeight();		

	protected:
		static double WUBA_XAXIS_A;
		static double WUBA_XAXIS_B;
		static double WUBA_YAXIS_A;
		static double WUBA_YAXIS_B;

		static int WUBA_BIG_WIDTH;
		static int WUBA_BIG_HEIGHT;
		static int WUBA_SMALL_WIDTH;
		static int WUBA_SMALL_HEIGHT;

		static double WUBA_DELTA_X;	// 扩大LOGO区域
		static double WUBA_DELTA_Y;

		static int GANJI_SMALL_H;
		static int GANJI_SMALL_W;
		static int GANJI_BIG_H;
		static int GANJI_BIG_W;

		static int GANJI_BIG_WIDTH;
		static int GANJI_BIG_HEIGHT;
		static int GANJI_SMALL_WIDTH;
		static int GANJI_SMALL_HEIGHT;

		static int WUBA_PIXBOUNDARY;
		static int GANJI_PIXBOUNDARY;
		static int BAIXING_TAILOR_H;
	};

}

#endif // !defined(BAGUO_ClsApp_h)