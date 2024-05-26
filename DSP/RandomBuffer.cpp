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

#include <climits>
#include "RandomBuffer.h"
#include "LcgRandom.h"

namespace Cloudseed
{
	std::vector<float> RandomBuffer::Generate(uint64_t seed, int count)
	{
		LcgRandom rand(seed);
		std::vector<float> output;

		for (int i = 0; i < count; i++)
		{
			unsigned int val = rand.NextUInt();
			float fVal = val / (float)UINT_MAX;
			output.push_back(fVal);
		}

		return output;
	}

	std::vector<float> RandomBuffer::Generate(uint64_t seed, int count, float crossSeed)
	{
		auto seedA = seed;
		auto seedB = ~seed;
		auto seriesA = Generate(seedA, count);
		auto seriesB = Generate(seedB, count);

		std::vector<float> output;
		for (int i = 0; i < count; i++)
			output.push_back(seriesA[i] * (1 - crossSeed) + seriesB[i] * crossSeed);

		return output;
	}
}
