#include "pimpl.h"
#include <printf.h>

namespace cm {
Pimpl::Pimpl(int _x, int _y) : x(_x), y(_y) {}
void Pimpl::print() const { printf("%d %d\n", x, y); }
} // namespace cm
