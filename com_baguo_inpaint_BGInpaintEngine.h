/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_talentedsoft_VPR_TSVPREngine */

#ifndef _Included_com_baguo_inpaint_BGInpaintEngine
#define _Included_com_baguo_inpaint_BGInpaintEngine

#ifndef bgInpaint_DLL
#define bgInpaint_DLL __declspec(dllexport)
#else
#define bgInpaint_DLL __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define com_baguo_inpaint_BGInpaintEngine_BGINPAINT_SUCCESS 0L
#define com_baguo_inpaint_BGInpaintEngine_BGINPAINT_FAIL 1L


// return BGINPAINT_SUCCESS when process successfully, else return BGINPAINT_FAIL
JNIEXPORT jint JNICALL Java_com_baguo_inpaint_BGInpaintEngine_wbInpaint
  (JNIEnv *, jclass, jstring, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
