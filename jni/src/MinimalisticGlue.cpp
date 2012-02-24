#include "SkCanvas.h"
#include "SkGraphics.h"
#include "SkImageEncoder.h"
#include "SkString.h"
#include "SkTemplates.h"
#include "SkPaint.h"

#include "JNIHelper.h"

#include <stdio.h>

#define BITMAP_JAVA_CLASS_NAME "org/mapsforge/skia/Bitmap"
#define CANVAS_JAVA_CLASS_NAME "org/mapsforge/skia/Canvas"

//[Native Bitmap wrapper functions]/////////////////////////////////////////////

static SkBitmap* Bitmap_nativeCreate(JNIEnv*, jobject)
{
	printf("[Native] Bitmap_nativeCreate() \r\n");
	SkBitmap *bmp = new SkBitmap();
	bmp->setConfig(SkBitmap::kARGB_8888_Config, 400, 200);
	bmp->allocPixels();

	printf("[Native] return: 0x%x \r\n", (unsigned int) bmp);
	return bmp;
}

void Bitmap_recycle(JNIEnv* env, jobject obj)
{
	printf("[Native] Bitmap_recycle() \r\n");
	SkBitmap* bmp = (SkBitmap*) JNIHelper::getNativeObject(env, obj);
	// TODO is this correct?
	bmp->setPixels(NULL, NULL);
}
void Bitmap_delete(JNIEnv* env, jobject obj)
{
	printf("[Native] Bitmap_delete() \r\n");
	SkBitmap* bmp = (SkBitmap*) JNIHelper::getNativeObject(env, obj);
	delete bmp;
}

void Bitmap_saveAsPNG(JNIEnv* env, jobject obj, jstring path)
{
	const char* pathCStr = env->GetStringUTFChars(path, NULL);
	printf("[Native] Bitmap_saveAsPNG(%s) \r\n", pathCStr);

	SkBitmap* bmp = (SkBitmap*) JNIHelper::getNativeObject(env, obj);
	SkImageEncoder::EncodeFile(pathCStr, *bmp, SkImageEncoder::kPNG_Type, 100);
}

static JNINativeMethod Bitmap_nativeMethods[] = {
		{ (char*) &"createBitmap",(char*) &"()I", (void*) Bitmap_nativeCreate },
		{ (char*) &"recycle", (char*) &"()V", (void*) Bitmap_recycle },
		{ (char*) &"delete",  (char*) &"()V", (void*) Bitmap_delete },
		{ (char*) &"saveAsPNG",  (char*) &"(Ljava/lang/String;)V", (void*) Bitmap_saveAsPNG }
};

//[Native Canvas wrapper functions]/////////////////////////////////////////////
static SkCanvas* Canvas_nativeCreate(JNIEnv*, jobject)
{
	printf("[Native] Canvas_nativeCreate() \r\n");
	SkCanvas *canvas = new SkCanvas();

	printf("[Native] return: 0x%x \r\n", (unsigned int) canvas);
	return 0;
}


static JNINativeMethod Canvas_nativeMethods[] = {
		{ (char*) &"createCanvas",(char*) &"(Lorg/mapsforge/skia/Bitmap;)I", (void*) Canvas_nativeCreate }
};
////////////////////////////////////////////////////////////////////////////////

void Bitmap_registerMethods()
{
	JNIHelper::registerMethodsForClass(BITMAP_JAVA_CLASS_NAME,
			Bitmap_nativeMethods,
			sizeof(Bitmap_nativeMethods) / sizeof(Bitmap_nativeMethods[0]));
}

void Canvas_registerMethods()
{
	JNIHelper::registerMethodsForClass(CANVAS_JAVA_CLASS_NAME,
			Canvas_nativeMethods,
			sizeof(Canvas_nativeMethods) / sizeof(Canvas_nativeMethods[0]));
}
