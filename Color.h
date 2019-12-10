#ifndef COLOR_H
#define COLOR_H
#include <math.h>
#include "PixelFormat.h"
#include <SkColor.h>
#include <SkColorSpace.h>
#include <SkImageInfo.h>
struct Lab {
    float L;
    float a;
    float b;
};
Lab sRGBToLab(SkColor color);
SkColor LabToSRGB(const Lab& lab, SkAlpha alpha);
#endif /* COLOR_H */

