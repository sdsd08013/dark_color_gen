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
#include <boost/format.hpp>

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

      unsigned int r = strtol(rs, NULL, 16);
      unsigned int g = strtol(gs, NULL, 16);
      unsigned int b = strtol(bs, NULL, 16);

      unsigned int nr = (SkColorGetR(android::uirenderer::makeDark(SkColorSetRGB(r, g, b))));
      unsigned int ng = (SkColorGetG(android::uirenderer::makeDark(SkColorSetRGB(r, g, b))));
      unsigned int nb = (SkColorGetB(android::uirenderer::makeDark(SkColorSetRGB(r, g, b))));

      string snr =  (boost::format("%1$02x") % nr).str();
      string sng =  (boost::format("%1$02x") % ng).str();
      string snb =  (boost::format("%1$02x") % nb).str();

      ptree& color = root.add("color", "#" + snr + sng + snb);
      color.put("<xmlattr>.name", name);

      count++;
  }
  write_xml("dark_colors.xml", npt, std::locale(),xml_writer_make_settings<std::string>(' ', count));

  return 0;
 
}
