#include "SkCanvas.h"
#include "SkGraphics.h"
#include "SkImageEncoder.h"
#include "SkString.h"
#include "SkTemplates.h"
#include "SkPaint.h"

void
createTestPNG(char helloText[])
{

  //Output filename
  SkString path("skhello.png");

  //Set Text To Draw
  SkString text(helloText);

  SkPaint paint;

  //Set Text ARGB Color
  paint.setARGB(255, 255, 255, 255);

  //Turn AntiAliasing On
  paint.setAntiAlias(true);

  //Set Text Size
  paint.setTextSize(SkIntToScalar(30));

  //Set Image Width & Height
  SkScalar width = 800;
  SkScalar height = 600;

  SkBitmap bitmap;
  bitmap.setConfig(SkBitmap::kARGB_8888_Config, width, height);
  bitmap.allocPixels();

  //Create Canvas
  SkCanvas canvas(bitmap);
  canvas.drawARGB(255, 0, 0, 0);

  //Text X, Y Position Variables
  SkScalar x = 80;
  SkScalar y = 60;

  canvas.drawText(text.c_str(), text.size(), x, y, paint);

  //Set Style and Stroke Width
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(10);

  //Draw A Rectangle
  SkRect rect;
  paint.setARGB(255, 255, 0, 0);
  //Left, Top, Right, Bottom
  rect.set(50, 100, 200, 200);
  canvas.drawRoundRect(rect, 20, 20, paint);

  //Draw A Line
  canvas.drawLine(10, 300, 300, 300, paint);

  //Draw Circle (X, Y, Size, Paint)
  canvas.drawCircle(100, 400, 50, paint);

  //paint.setStrokeJoin(SkPaint::Join::kRound_Join);
  SkPath p;
  p.moveTo(100, 100);
  p.lineTo(150, 150);
  p.moveTo(150, 150);
  p.lineTo(300, 300);
  p.lineTo(30, 30);
  canvas.drawPath(p, paint);

  //Same Image  (file, bitmap, image_type, quality)
  SkImageEncoder::EncodeFile(path.c_str(), bitmap, SkImageEncoder::kPNG_Type,
      100);

}

/**
 * This is just a simple hello world script that creates a PNG file (skhello.png) with some lines and text using Skia.
 */

int
main(int argc, char * const argv[])
{
  printf("Creating test PNG...\r\n");
  char *halloText;
  if (argc < 2)
    {
      halloText = "no text";
    }
  else
    {
      halloText = argv[1];
    }
  createTestPNG(halloText);
  return 0;
}
