#ifndef CMAKE_PIMPL_
#define CMAKE_PIMPL_

#include <memory>
namespace cm {
class Pimpl {
public:
  Pimpl(int x, int y);
  void print() const;

private:
  int x;
  int y;
};
} // namespace cm
#endif /* CMAKE_PIMPL_ */
