#pragma once

#include "s2/base/vector.h"
#include "s2/base/basic_types.h"
#include "s2/base/string_view.h"
#include "s2/ui/geometry.h"

namespace s2::ui {
class font {
public:
  virtual ~font() = default;

  virtual usize glyph_count() const = 0;
};
struct glyph_id {
  base::u32 value;
};
class shaped_segment {
private:
  base::vector<glyph_id> glyphs_;
  base::vector<point> positions_;
};
class shaped_line {
public:
private:
  base::vector<shaped_segment> segments_;
};
class text_manager {
public:
  virtual ~text_manager() = default;
  virtual font* default_font() = 0;

  virtual shaped_line shape_line(base::string_view s) = 0;
};
} // namespace s2::ui

// [NOTES]
//
// Steps:
// 1. styling: e.g. attributed strings
// 2. layout: text -> paragraphs -> lines -> runs
// 3. shaping: run -> positioned glyphs
// 4. rasterization: glyphs -> bitmap
//
// Caveats:
// a. styling depends on shaping:
//    only through shaping can one know whether the font provides the
//    characters. a robust system must support cascading into fallback fonts.
// b. layout depends on shaping:
//    there is not way to obtain the width unless the text is shaped.
//
// so step 1,2,3 are intertwined.
//
// c. glyphs can overlap.
// d. emoji breaks color and style.
// e.
