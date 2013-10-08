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
	//  ��һ��������ˮӡ��λ�ã����������Ͻǵ����꣩
	//  �ڶ���������λ����Ϣ�������ɰ塢ˮӡ
	//  �������������ɰ��ˮӡ��ȥ��ԭˮӡ��������ˮӡ
	//----------------------------------------------------------------------
	class ClsApp : public ClsObject
	{
	public:
		virtual string getClassName() const;

		/// 
		/// ���ܣ����ݲ����������ɰ�
		/// 
		/// @param src ԭͼƬ
		/// @param maskrect ˮӡ�ߴ��λ����Ϣ
		/// @param mask �ɰ�ͼƬ�����������
		/// @return 
		/// 
		static bool createMask(IplImage *src, MaskRect maskrect, IplImage *&mask);

		/// 
		/// ���ܣ����ݲ����������ɰ�
		/// 
		/// @param src ԭͼƬ
		/// @param maskrect ˮӡ�ߴ��λ����Ϣ
		/// @param mask �ɰ�ͼƬ�����������
		/// @return 
		/// 
		static bool createMask(ClsPicture *src, MaskRect maskrect, ClsPicture *&mask);

		/// 
		/// ���ܣ�������վ���͡�ԭͼ���������
		/// 
		/// @param src ԭͼƬ
		/// @param type ͼƬ���
		/// @param maskrect ˮӡ�ߴ��λ����Ϣ�����������
		/// @return 
		/// 
		static bool computeParams(IplImage *src, MarkType type, MaskRect &maskrect);

		/// 
		/// ���ܣ�������վ���͡�ԭͼ���������
		/// 
		/// @param src ԭͼƬ
		/// @param type ͼƬ���
		/// @param maskrect ˮӡ�ߴ��λ����Ϣ���������
		/// @return 
		/// 
		static bool computeParams(ClsPicture *src, MarkType type, MaskRect &maskrect);

		/// 
		/// ���ܣ����ݲ���������ˮӡ
		/// 
		/// @param src ԭͼƬ�����롢���������
		/// @param logo LogoͼƬ
		/// @param maskrect ˮӡ�ߴ��λ����Ϣ
		/// @param weight ˮӡȨ��,��Χ[0, 1]
		/// @return
		/// 
		static bool addWaterMark(ClsPicture *&src, ClsPicture *logo, MaskRect maskrect, double weight);
		
		/// 
		/// ���ܣ���ȡ�������Ĳü��ߴ�
		/// 
		/// @return �ü��ߴ�
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

		static double WUBA_DELTA_X;	// ����LOGO����
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