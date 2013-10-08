/*
	This file is part of EMark_v1.0 which eliminate watermark from a
	marked picture. 

	Copyright (C) 2013-2020
	Xiamen Baguo Network Technology Co., Ltd. [http://www.ibaguo.com]
	Chimyli [chimyli@gmail.com]
*/
#if !defined(BAGUO_ClsObject_cpp)
#define BAGUO_ClsObject_cpp

#include "ClsObject.h"
#include <cstdio>

using namespace baguo;

ClsObject::ClsObject() {}

//-------------------------------------------------------------------------
string ClsObject::toString() const
{ 
	return "[ " + getClassName() + " " + getAddress() + " ]"; 
}


string ClsObject::getAddress() const
{
	char str[50];
	::sprintf(str, "%p", (void*)this);
	return str;
}
//-------------------------------------------------------------------------
ClsObject::~ClsObject() {}

#endif // !defined(BAGUO_ClsObject_cpp)