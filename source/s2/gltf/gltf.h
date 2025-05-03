#pragma once

namespace s2::gltf {

// binary gltf is litten endian
// a binary gltf consists of a 12-byte header and one or more chunks of data
//
// | header | chunk 0 (json) | chunk 1 (bin, optional) |
//
// header:
//   u32  magic     0x46546C67 "glTF"
//   u32  version   2 (glb container versions)
//   u32  length    total length (header + chunks) in bytes
// chunk:
//   u32  length    length of this chunk in bytes
//   u32  type      chunk type
//   u8[] data
//
// the start and the end of each chunk must be aligned to a 4-byte boundary
// chunks must appear in the order of the chunk types listed below
//
// chunk types:
//  0x4E4F534A  JSON    one chunk
//  0x004E4942  BIN     zero or one chunk
//

}
