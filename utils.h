#ifndef _BAGUO_UTILS_H
#define _BAGUO_UTILS_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// 58去水印
bool wbInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename);

// 赶集去水印
bool gjInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename, int type);

// 百姓去水印
bool bxInpaint(const char *srcFilename, const char *dstFilename, int height);

#ifdef __cplusplus
}
#endif

#endif	//_BAGUO_UTILS_H