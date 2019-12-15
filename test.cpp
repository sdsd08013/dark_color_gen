#include "test.h"

#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "Color.h"

namespace android {
namespace uirenderer {

SkColor makeDark(SkColor color) {
    Lab lab = sRGBToLab(color);
    float invertedL = std::min(110 - lab.L, 100.0f);
    if (invertedL < lab.L) {
        lab.L = invertedL;
        return LabToSRGB(lab, SkColorGetA(color));
    } else {
        return color;
    }
}
void test() {
  std::cout << "========" << std::endl;
}
}
}

