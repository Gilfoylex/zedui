#include <sstream>
#include "zedui/geometry/vector.h"

namespace zedui {

std::string Vector3::ToString() const {
  std::stringstream stream;
  stream << "{" << x << ", " << y << ", " << z << "}";
  return stream.str();
}

std::string Vector4::ToString() const {
  std::stringstream stream;
  stream << "{" << x << ", " << y << ", " << z << ", " << w << "}";
  return stream.str();
}

}  // namespace zedui