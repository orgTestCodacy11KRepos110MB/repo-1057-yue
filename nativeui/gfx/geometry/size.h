// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NATIVEUI_GFX_GEOMETRY_SIZE_H_
#define NATIVEUI_GFX_GEOMETRY_SIZE_H_

#include <iosfwd>
#include <string>

#include "base/compiler_specific.h"
#include "base/numerics/safe_math.h"
#include "build/build_config.h"
#include "nativeui/nativeui_export.h"

#if defined(OS_WIN)
typedef struct tagSIZE SIZE;
#elif defined(OS_MAC)
typedef struct CGSize CGSize;
#endif

namespace nu {

// A size has width and height values.
class NATIVEUI_EXPORT Size {
 public:
  Size() : width_(0), height_(0) {}
  Size(int width, int height)
      : width_(width < 0 ? 0 : width), height_(height < 0 ? 0 : height) {}
#if defined(OS_MAC)
  explicit Size(const CGSize& s);
#endif

  ~Size() {}

#if defined(OS_MAC)
  Size& operator=(const CGSize& s);
#endif

#if defined(OS_WIN)
  SIZE ToSIZE() const;
#elif defined(OS_MAC)
  CGSize ToCGSize() const;
#endif

  int width() const { return width_; }
  int height() const { return height_; }

  void set_width(int width) { width_ = width < 0 ? 0 : width; }
  void set_height(int height) { height_ = height < 0 ? 0 : height; }

  // This call will CHECK if the area of this size would overflow int.
  int GetArea() const;
  // Returns a checked numeric representation of the area.
  base::CheckedNumeric<int> GetCheckedArea() const;

  void SetSize(int width, int height) {
    set_width(width);
    set_height(height);
  }

  void Enlarge(int grow_width, int grow_height);

  void SetToMin(const Size& other);
  void SetToMax(const Size& other);

  bool IsEmpty() const { return !width() || !height(); }

  std::string ToString() const;

 private:
  int width_;
  int height_;
};

inline bool operator==(const Size& lhs, const Size& rhs) {
  return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

inline bool operator!=(const Size& lhs, const Size& rhs) {
  return !(lhs == rhs);
}

// This is declared here for use in gtest-based unit tests but is defined in
// the gfx_test_support target. Depend on that to use this in your unit test.
// This should not be used in production code - call ToString() instead.
void PrintTo(const Size& size, ::std::ostream* os);

// Helper methods to scale a Size to a new Size.
NATIVEUI_EXPORT Size ScaleToCeiledSize(const Size& size,
                                  float x_scale,
                                  float y_scale);
NATIVEUI_EXPORT Size ScaleToCeiledSize(const Size& size, float x_scale);
NATIVEUI_EXPORT Size ScaleToFlooredSize(const Size& size,
                                   float x_scale,
                                   float y_scale);
NATIVEUI_EXPORT Size ScaleToFlooredSize(const Size& size, float x_scale);
NATIVEUI_EXPORT Size ScaleToRoundedSize(const Size& size,
                                   float x_scale,
                                   float y_scale);
NATIVEUI_EXPORT Size ScaleToRoundedSize(const Size& size, float x_scale);

}  // namespace nu

#endif  // NATIVEUI_GFX_GEOMETRY_SIZE_H_
