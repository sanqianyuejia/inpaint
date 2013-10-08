#include "com_baguo_inpaint_BGInpaintEngine.h"
#include "utils.h"

JNIEXPORT jint JNICALL Java_com_baguo_inpaint_BGInpaintEngine_wbInpaint
		(JNIEnv *env, jclass obj, jstring srcfilepath, jstring logofilepath, jstring dstfilepath) 
{	
	
	// get file path strings
	const char *cSrcFilepath = env->GetStringUTFChars(srcfilepath, 0);
	const char *cLogoFilepath = env->GetStringUTFChars(logofilepath, 0);
	const char *cDstFilepath = env->GetStringUTFChars(dstfilepath, 0);

	// inpaint
	if (wbInpaint(cSrcFilepath, cLogoFilepath, cDstFilepath) == false) {
		// release file path strings
		env->ReleaseStringUTFChars(srcfilepath, cSrcFilepath);
		env->ReleaseStringUTFChars(logofilepath, cLogoFilepath);
		env->ReleaseStringUTFChars(dstfilepath, cDstFilepath);
		return 1;
	}

	// release file path strings
	env->ReleaseStringUTFChars(srcfilepath, cSrcFilepath);
	env->ReleaseStringUTFChars(logofilepath, cLogoFilepath);
	env->ReleaseStringUTFChars(dstfilepath, cDstFilepath);
	return 0;
}