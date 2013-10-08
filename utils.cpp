#include "utils.h" 
#include "./src/ClsPicture.h"
#include "./src/ClsProc.h"
#include "./src/ClsApp.h"
using namespace baguo;

// 去水印
bool wbInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename)
{
	// get source picture
	ClsPicture *picture = new ClsPicture();
	picture->setFilePath(srcFilename);
	if (picture->loadToIplImage(1) == false) return false;
	if (picture->loadToMat(1) == false) return false;
	if (picture->splitChannel(3) == false) return false;
	if (picture->initDstVector() == false) return false;

	// get mask
	MaskRect mask_rect;
	ClsPicture *maskPic = new ClsPicture();
	if (ClsApp::computeParams(picture, MARKTYPE_58, mask_rect) == false) return false;
	if (ClsApp::createMask(picture, mask_rect, maskPic) == false) return false;

	// get logo
	ClsPicture *logo = new ClsPicture();
	logo->setFilePath(logoFilename);
	if (logo->loadToMat(1) == false) return false;
	
	// inpaint
	if (ClsProc::inpaint(picture, maskPic) == false) return false;	

	// merge image and add watermark
	if (picture->mergeChannel() == false) return false;
	if (ClsApp::addWaterMark(picture, logo, mask_rect, 0.7) == false) return false;

	// save and release image 
	if (picture->saveImage(dstFilename) == false) return false;
	picture->resetImage();
	logo->resetImage();
	maskPic->resetImage();

	return true;
}

// type: 0--小水印， 1--大水印
bool gjInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename, int type)
{
	// get source picture
	ClsPicture *picture = new ClsPicture();
	picture->setFilePath(srcFilename);
	if (picture->loadToIplImage(1) == false) return false;
	if (picture->loadToMat(1) == false) return false;
	if (picture->splitChannel(3) == false) return false;
	if (picture->initDstVector() == false) return false;

	// get mask
	MaskRect mask_rect;
	ClsPicture *maskPic = new ClsPicture();
	if (ClsApp::computeParams(picture, MARKTYPE_GANJI, mask_rect) == false)return false;
	if (ClsApp::createMask(picture, mask_rect, maskPic) == false)return false;

	// get logo
	ClsPicture *logo = new ClsPicture();
	logo->setFilePath(logoFilename);
	if (logo->loadToMat(1) == false) return false;

	// inpaint
	if (ClsProc::inpaint(picture, maskPic) == false) return false;	
	if (picture->mergeChannel() == false) return false;
	if (ClsApp::addWaterMark(picture, logo, mask_rect, 0.7) == false) return false;

	// release
	if (picture->saveImage(dstFilename) == false) return false;
	picture->resetImage();
	maskPic->resetImage();

	return true;
}

// 裁剪图片
bool bxInpaint(const char *srcFilename, const char *dstFilename, int size)
{
	ClsPicture *pic = new ClsPicture(srcFilename);
	if (pic->loadToIplImage(1) == false) return false;
	if (ClsProc::tailor(pic, size) == false) return false;
	if (pic->saveImage(dstFilename) == false) return false;
	pic->resetImage();

	return true;
}