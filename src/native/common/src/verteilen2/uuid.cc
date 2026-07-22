/**
    MIT License

    Copyright (c) 2026 ZhuElly

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#include <verteilen2/uuid.h>
#include <absl/numeric/int128.h>
#include <absl/random/random.h>
#include <absl/strings/str_format.h>

namespace verteilen2 {
    std::string generate_uuid(){
        absl::BitGen bitgen;
        uint64_t high = absl::LogUniform<uint64_t>(bitgen, 0, UINT64_MAX);
        uint64_t low = absl::LogUniform<uint64_t>(bitgen, 0, UINT64_MAX);

        high = (high & 0xFFFFFFFFFFFF0FFF_u64) | 0x0000000000004000_u64;        
        low = (low & 0x3FFFFFFFFFFFFFFF_u64) | 0x8000000000000000_u64;

        uint32_t time_low = high >> 32;
        uint16_t time_mid = (high >> 16) & 0xFFFF;
        uint16_t time_hi_and_version = high & 0xFFFF;
        uint16_t clock_seq = low >> 48;
        uint64_t node = low & 0xFFFFFFFFFFFF_u64;

        return absl::StrFormat("%08x-%04x-%04x-%04x-%012x", time_low, time_mid, time_hi_and_version, clock_seq, node);
    }
}