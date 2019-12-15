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

#include "Color.h"

int main() {
  //cout << SkColorGetR(SkColorSetARGB(0x80, 0xFF, 0xFF, 0x00)) << endl;

  sRGBToLab(SK_ColorBLUE);
  std::cout << SkColorGetR(SkColorSetARGB(0x80, 0xFF, 0xFF, 0x00)) << std::endl;
  std::cout << SK_ColorBLUE << std::endl;

  return 0;
 
}
