#ifndef _BAGUO_UTILS_H
#define _BAGUO_UTILS_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// 58ȥˮӡ
bool wbInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename);

// �ϼ�ȥˮӡ
bool gjInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename, int type);

// ����ȥˮӡ
bool bxInpaint(const char *srcFilename, const char *dstFilename, int height);

#ifdef __cplusplus
}
#endif

#endif	//_BAGUO_UTILS_H