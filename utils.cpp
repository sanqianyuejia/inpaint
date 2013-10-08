#include "utils.h" 
#include "./src/ClsPicture.h"
#include "./src/ClsProc.h"
#include "./src/ClsApp.h"
using namespace baguo;

// 去水印
void wbInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename)
{
	// get source picture
	ClsPicture *picture = new ClsPicture();
	picture->setFilePath(srcFilename);
	picture->loadToIplImage(1);
	picture->loadToMat(1);
	picture->splitChannel(3);
	picture->initDstVector();

	// get mask
	MaskRect mask_rect;
	ClsPicture *maskPic = new ClsPicture();
	if (ClsApp::computeParams(picture, MARKTYPE_58, mask_rect) == false) return;
	if (ClsApp::createMask(picture, mask_rect, maskPic) == false) return;

	// get logo
	ClsPicture *logo = new ClsPicture();
	logo->setFilePath(logoFilename);
	logo->loadToMat(1);
	
	// inpaint
	ClsProc::inpaint(picture, maskPic);	

	// merge image and add watermark
	picture->mergeChannel();
	ClsApp::addWaterMark(picture, logo, mask_rect, 0.7);

	// save and release image 
	picture->saveImage(dstFilename);
	picture->resetImage();
	logo->resetImage();
	maskPic->resetImage();
}

// type: 0--小水印， 1--大水印
void gjInpaint(const char *srcFilename, const char *logoFilename, const char *dstFilename, int type)
{
	// get source picture
	ClsPicture *picture = new ClsPicture();
	picture->setFilePath(srcFilename);
	picture->loadToIplImage(1);
	picture->loadToMat(1);
	picture->splitChannel(3);
	picture->initDstVector();

	// get mask
	MaskRect mask_rect;
	ClsPicture *maskPic = new ClsPicture();
	ClsApp::computeParams(picture, MARKTYPE_GANJI, mask_rect);
	ClsApp::createMask(picture, mask_rect, maskPic);

	// get logo
	ClsPicture *logo = new ClsPicture();
	logo->setFilePath(logoFilename);
	logo->loadToMat(1);

	// inpaint
	ClsProc::inpaint(picture, maskPic);	
	picture->mergeChannel();
	ClsApp::addWaterMark(picture, logo, mask_rect, 0.7);

	// release
	picture->saveImage(dstFilename);
	picture->resetImage();
	maskPic->resetImage();
}

// 裁剪图片
void bxInpaint(const char *srcFilename, const char *dstFilename, int size)
{
	ClsPicture *pic = new ClsPicture(srcFilename);
	pic->loadToIplImage(1);
	ClsProc::tailor(pic, size);
	pic->saveImage(dstFilename);
	pic->resetImage();
}