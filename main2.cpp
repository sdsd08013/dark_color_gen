#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "SkCanvas.h"
#include "SkData.h"
#include "SkEncodedImageFormat.h"
#include "SkImage.h"
#include "SkPaint.h"
#include "SkSurface.h"
#include "SkColorSpace.h"

#include "transform.h"

int main() {
  //cout << SkColorGetR(SkColorSetARGB(0x80, 0xFF, 0xFF, 0x00)) << endl;

  /*
  std::cout << SkColorGetR(SkColorSetARGB(0x80, 0xFF, 0xFF, 0x00)) << std::endl;
  std::cout << SK_ColorBLUE << std::endl;
  std::cout << android::uirenderer::Color::Red_500 << std::endl;
  */

  SkColor b = SK_ColorBLUE;

  //SkColorSpace::MakeSRGB();
  //android::uirenderer::sRGBToLab(SK_ColorBLUE);
  SkColor dc = android::uirenderer::makeDark(b);
  //android::ColorSpace::test();
  std::cout << SkColorGetA(dc) << std::endl;

  return 0;
 
}
