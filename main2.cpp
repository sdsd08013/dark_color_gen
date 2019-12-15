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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::property_tree;
using namespace std;
int main() {

  int count = 0;
  ptree npt;
  ptree& root = npt.put("resources", "");
  ptree pt;
  read_xml("colors.xml", pt);

  BOOST_FOREACH (const ptree::value_type& child, pt.get_child("resources")) {
      const string name = child.second.get<string>("<xmlattr>.name");

      const string l = boost::lexical_cast<string>(child.second.data());
      const char* const rs = l.substr(1,2).c_str();
      const char* const gs = l.substr(3,2).c_str();
      const char* const bs = l.substr(5,2).c_str();

      double r = strtol(rs, NULL, 16);
      double g = strtol(bs, NULL, 16);
      double b = strtol(gs, NULL, 16);

      string nr = to_string(SkColorGetR(android::uirenderer::makeDark(SkColorSetRGB(r, g, b))));
      string ng = to_string(SkColorGetG(android::uirenderer::makeDark(SkColorSetRGB(r, g, b))));
      string nb = to_string(SkColorGetB(android::uirenderer::makeDark(SkColorSetRGB(r, g, b))));

      ptree& color = root.add("color", "#" + nr + ng + nb);
      color.put("<xmlattr>.name", name);

      count++;
  }
  write_xml("dark_colors.xml", npt, std::locale(),xml_writer_make_settings<std::string>(' ', count));

  return 0;
 
}
