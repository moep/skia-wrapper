#include "SkBitmap.h"
#include "SkImageEncoder.h"
#include "SkColorPriv.h"
#include "GraphicsJNI.h"
#include "SkDither.h"
#include "SkUnPreMultiply.h"

#include "JNIHelper.h"
#include <jni.h>
#include <stdio.h>

#define BITMAP_JAVA_CLASS_NAME "android/graphics/Bitmap"

static jobject Bitmap_creator(JNIEnv* env, jobject, jintArray jColors,
                              int offset, int stride, int width, int height,
                              SkBitmap::Config config, jboolean isMutable) {
    if (width <= 0 || height <= 0) {
        //doThrowIAE(env, "width and height must be > 0");
        return NULL;
    }

    if (NULL != jColors) {
        size_t n = env->GetArrayLength(jColors);
        if (n < SkAbs32(stride) * (size_t)height) {
            //doThrowAIOOBE(env);
            return NULL;
        }
    }

    SkBitmap bitmap;

    bitmap.setConfig(config, width, height);
    if (!GraphicsJNI::setJavaPixelRef(env, &bitmap, NULL, true)) {
        return NULL;
    }

    if (jColors != NULL) {
        GraphicsJNI::SetPixels(env, jColors, offset, stride,
                               0, 0, width, height, bitmap);
    }

    return GraphicsJNI::createBitmap(env, new SkBitmap(bitmap), isMutable,
                                     NULL);
}

static void Bitmap_destructor(JNIEnv* env, jobject, SkBitmap* bitmap) {
    printf("[Native] Bitmap_destructor() \r\n");
    delete bitmap;
}

static void Bitmap_erase(JNIEnv* env, jobject, SkBitmap* bitmap, jint color) {
    printf("[Native] Bitmap_erase(0x%x) \r\n", color);
    bitmap->eraseColor(color);
}

static jboolean Bitmap_hasAlpha(JNIEnv* env, jobject, SkBitmap* bitmap) {
    printf("[Native] Bitmap_hasAlpha() \r\n");
    return !bitmap->isOpaque();
}

static void Bitmap_setHasAlpha(JNIEnv* env, jobject, SkBitmap* bitmap,
                               jboolean hasAlpha) {
    printf("[Native] Bitmap_setHasAlpha() \r\n");
    bitmap->setIsOpaque(!hasAlpha);
}

////////////////////////////////////////////////////////////////////////////////
static JNINativeMethod Bitmap_nativeMethods[] = {
    {   "nativeCreate", "([IIIIIIZ)Landroid/graphics/Bitmap;",(void*)Bitmap_creator },
    {   "nativeDestructor",         "(I)V", (void*)Bitmap_destructor },
    {   "nativeErase",              "(II)V", (void*)Bitmap_erase },
    {   "nativeHasAlpha",           "(I)Z", (void*)Bitmap_hasAlpha },
    {   "nativeSetHasAlpha",        "(IZ)V", (void*)Bitmap_setHasAlpha },
};

void Bitmap_registerMethods()
{
        JNIHelper::registerMethodsForClass(BITMAP_JAVA_CLASS_NAME,
                        Bitmap_nativeMethods,
                        sizeof(Bitmap_nativeMethods) / sizeof(Bitmap_nativeMethods[0]));
}
