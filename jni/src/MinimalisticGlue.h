#include "SkCanvas.h"
#include "SkGraphics.h"
#include "SkImageEncoder.h"
#include "SkString.h"
#include "SkTemplates.h"
#include "SkPaint.h"

#ifndef MINIMALISTIC_GLUE_H
#define MINIMALISTIC_GLUE_H

SkBitmap* Bitmap_registerMethods();
SkBitmap* Canvas_registerMethods();
//void Bitmap_recycle();
//void Bitmap_delete();
//void Bitmap_saveAsPNG(const char* path);

#endif
