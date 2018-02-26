#include "allocator.h"
#include <cassert>

using cm::Chunk;

Chunk::Chunk(std::size_t blockSize, unsigned char blocks) {
  data                = new unsigned char[blockSize * blocks];
  firstAvailableBlock = 0;
  blocksAvailable     = blocks;
  unsigned char* p    = data;
  for (unsigned char i = 0; i != blocks; p += blockSize)
    *p = ++i;
}

void* Chunk::allocate(std::size_t blockSize) {
  if (!blocksAvailable)
    return nullptr;
  unsigned char* result = data + (firstAvailableBlock * blockSize);
  firstAvailableBlock   = *result;
  --blocksAvailable;
  return result;
}

void Chunk::deallocate(void* p, std::size_t blockSize) {
  assert(p >= data);
  unsigned char* toRelease = static_cast<unsigned char*>(p);
  assert((toRelease - data) % blockSize == 0);
  firstAvailableBlock =
      static_cast<unsigned char>((toRelease - data) / blockSize);
  assert(firstAvailableBlock == (toRelease - data) / blockSize);
  ++blocksAvailable;
}
