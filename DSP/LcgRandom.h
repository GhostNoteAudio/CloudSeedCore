/*
Copyright (c) 2024 Ghost Note Engineering Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include <stdint.h>

namespace Cloudseed
{
	class LcgRandom
	{
	private:
		uint64_t x;
		uint64_t a;
		uint64_t c;

		double doubleInv;
		float floatUintInv;
		float floatIntInv;

	public:
		inline LcgRandom(uint64_t seed = 0)
		{
			x = seed;
			a = 22695477;
			c = 1;

			doubleInv = 1.0 / (double)UINT32_MAX;
			floatUintInv = 1.0 / (float)UINT32_MAX;
			floatIntInv = 1.0 / (float)INT32_MAX;
		}

		inline void SetSeed(uint64_t seed)
		{
			x = seed;
		}

		inline uint32_t NextUInt()
		{
			uint64_t axc = a * x + c;
			//x = axc % m;
			x = axc & 0xFFFFFFFF;
			return (uint32_t)x;
		}

		inline int32_t NextInt()
		{
			int64_t axc = a * x + c;
			//x = axc % m;
			x = axc & 0x7FFFFFFF;
			return (int32_t)x;
		}

		inline double NextDouble()
		{
			auto n = NextUInt();
			return n * doubleInv;
		}

		inline float NextFloat()
		{
			auto n = NextInt();
			return n * floatIntInv;
		}

		inline void GetFloats(float* buffer, int len)
		{
			for (int i = 0; i < len; i++)
				buffer[i] = NextFloat();
		}

		inline void GetFloatsBipolar(float* buffer, int len)
		{
			for (int i = 0; i < len; i++)
				buffer[i] = NextFloat() * 2 - 1;
		}
	};
}
