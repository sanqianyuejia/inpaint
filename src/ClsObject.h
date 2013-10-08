/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture. 

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsObject_h)
#define BAGUO_ClsObject_h

#include <string>
using std::string;

#ifndef NULL
#define NULL 0
#endif


namespace baguo 
{
	// coordinate
	struct Point 
	{
		int x;
		int y;
	};
	
	// mask rectangle
	struct MaskRect
	{
		Point point;	// сроб╫г╣д╣Ц
		int width;
		int height;
	};

	// different websites
	enum MarkType
	{
		MARKTYPE_58,
		MARKTYPE_GANJI,
		MARKTYPE_BAIXING,
		MARKTYPE_AIBANG,
		MARKTYPE_DIANPING
	};

	// different methods
	enum ProcType
	{
		PROCTYPE_INPAINT,
		PROCTYPE_COVER,
		PROCTYPE_CUT
	};

	enum PicType
	{
		PICTYPE_SMALL,
		PICTYPE_Medium,
		PICTYPE_BIG
	};

	enum ColorType
	{
		COLORTYPE_GRAY,
		COLORTYPE_COLOR
	};

	enum ChannelType
	{
		CHANNELTYPE_RED,
		CHANNELTYPE_GREEN,
		CHANNELTYPE_BLUE
	};

	class ClsObject
	{
	public :

		ClsObject();
		virtual ~ClsObject();

		/// Returns the name of the class
		/// @returns the name of the class of the object as a String
		///
		virtual string getClassName() const = 0;

		/// This method is frequently overridden in the derived classes.
		/// If it is not, it returns the name of the class of the object and the
		/// address of the object
		///
		/// @return a description of the object
		///
		virtual string toString() const;

		/// Returns the address
		///
		virtual string getAddress() const;
	};

}

#endif // !defined(BAGUO_ClsObject_h)