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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::property_tree;
using namespace std;

double XYZ_WHITE_REFERENCE_X = 95.047;
double XYZ_WHITE_REFERENCE_Y = 100;
double XYZ_WHITE_REFERENCE_Z = 108.883;

double XYZ_EPSILON = 0.008856;
double XYZ_KAPPA = 903.3;

vector<double> RGBToXYZ(int r, int g, int b);
vector<double> XYZToLAB(float x, float y, float z);
double pivotXyzComponent(double component);

vector<double> RGBToXYZ(int r, int g, int b){
  vector<double> outXyz;
  double sr = r / 255.0;
  if (sr < 0.04045) sr = sr / 12.92; else sr = pow((sr + 0.055) / 1.055, 2.4);
  double sg = g / 255.0;
  if (sg < 0.04045) sg = sg / 12.92; else sg = pow((sg + 0.055) / 1.055, 2.4);
  double sb = b / 255.0;
  if(sb < 0.04045) sb = sb / 12.92; else sb = pow((sb + 0.055) / 1.055, 2.4);

  outXyz.push_back(100 * (sr * 0.4124 + sg * 0.3576 + sb * 0.1805));
  outXyz.push_back(100 * (sr * 0.2126 + sg * 0.7152 + sb * 0.0722));
  outXyz.push_back(100 * (sr * 0.0193 + sg * 0.1192 + sb * 0.9505));

  return outXyz;
}

vector<double> XYZToLAB(float x, float y, float z){
  vector<double> outLab;

  x = pivotXyzComponent(x / XYZ_WHITE_REFERENCE_X);
  y = pivotXyzComponent(y / XYZ_WHITE_REFERENCE_Y);
  z = pivotXyzComponent(z / XYZ_WHITE_REFERENCE_Z);
  if (0 > 116*y - 16) {
    outLab.push_back(0);
  } else {
    outLab.push_back(116*y - 16);
  }
  outLab.push_back(500 * (x - y));
  outLab.push_back(200 * (y - z));

  return outLab;
}

vector<double> LABToXYZ(double l, double a, double b) {
  vector<double> outXyz;

  double fy = (l + 16) / 116;
  double fx = a / 500 + fy;
  double fz = fy - b / 200;

  double tmp = pow(fx, 3);
  double xr;
  if (tmp > XYZ_EPSILON) xr = tmp; else xr = (116 * fx - 16) / XYZ_KAPPA;
  double yr;
  if( l > XYZ_KAPPA * XYZ_EPSILON) yr = pow(fy, 3); else yr = l / XYZ_KAPPA;
  tmp = pow(fz, 3);
  double zr;
  if(tmp > XYZ_EPSILON) zr = tmp; else zr = (116 * fz - 16) / XYZ_KAPPA;
  outXyz.push_back(xr * XYZ_WHITE_REFERENCE_X);
  outXyz.push_back(yr * XYZ_WHITE_REFERENCE_Y);
  outXyz.push_back(zr * XYZ_WHITE_REFERENCE_Z);
  return outXyz;
}

/*
SkColor XYZToColor(double x, double y, double z) {
  double r = (x * 3.2406 + y * -1.5372 + z * -0.4986) / 100;
  double g = (x * -0.9689 + y * 1.8758 + z * 0.0415) / 100;
  double b = (x * 0.0557 + y * -0.2040 + z * 1.0570) / 100;
  if(r > 0.0031308) r = 1.055 * pow(r, 1 / 2.4) - 0.055; else 12.92 * r;
  if(g > 0.0031308) g =  1.055 * pow(g, 1 / 2.4) - 0.055 else 12.92 * g;
  if(b > 0.0031308) b = 1.055 * pow(b, 1 / 2.4) - 0.055 else 12.92 * b;
  return Color.rgb(
          constrain((int) Math.round(r * 255), 0, 255),
          constrain((int) Math.round(g * 255), 0, 255),
          constrain((int) Math.round(b * 255), 0, 255));
}
          */

double pivotXyzComponent(double component) {
  if (component > XYZ_EPSILON) {
    return pow(component, 1/3.0);
  } else {
    return (XYZ_KAPPA * component + 16) / 116;
  }
}

/*
vector<double> createRGB(char *r, char *g, char *b)
{
  vector<double> outRGB;
  outRGB.push_back(strtol(r, NULL, 16));
  outRGB.push_back(strtol(g, NULL, 16));
  outRGB.push_back(strtol(b, NULL, 16));
  return outRGB;
}
*/

int main() {
  vector<double> outXyz;
  vector<double> outLab;

  ptree pt;
  read_xml("colors.xml", pt);

  if (boost::optional<string> str = pt.get_optional<string>("resources.color")) {
    string l = str.get();
    const char* const rs = l.substr(1,2).c_str();
    const char* const gs = l.substr(3,2).c_str();
    const char* const bs = l.substr(5,2).c_str();

    double r = strtol(rs, NULL, 16);
    double g = strtol(bs, NULL, 16);
    double b = strtol(gs, NULL, 16);

    outXyz = RGBToXYZ(r, g, b);
    outLab = XYZToLAB(outXyz.at(0), outXyz.at(1), outXyz.at(2));
  }

  return 0;
 
}
