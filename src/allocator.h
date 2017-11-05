#ifndef CMAKE_ALLOCATOR_H
#define CMAKE_ALLOCATOR_H

#include <cstddef>
#include <vector>

namespace cm {
class Chunk {
public:
  Chunk(std::size_t blockSize, unsigned char blocks);
  void* allocate(std::size_t blockSize);
  void deallocate(void* p, std::size_t blockSize);

private:
  unsigned char* data;
  unsigned char firstAvailableBlock;
  unsigned char blocksAvailable;
};

  class FixedAllocator {
  public:

  private:
    std::size_t blockSize;
    unsigned char numBlocks;
    using Chunks = std::vector<Chunk>;
    Chunks chunks;
    Chunk* allocChunk;
    Chunk* deallocChunk;
  };
} // namespace cm

#endif /* CMAKE_ALLOCATOR_H */
