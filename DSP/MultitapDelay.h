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

#include <vector>
#include <memory>
#include <array>
#include <cmath>
#include "Utils.h"
#include "RandomBuffer.h"

namespace Cloudseed
{
	class MultitapDelay
	{
	public:
		static const int MaxTaps = 256;
		static const int DelayBufferSize = 192000 * 2;

	private:
		float delayBuffer[DelayBufferSize] = { 0 };

		float tapGains[MaxTaps] = { 0 };
		float tapPosition[MaxTaps] = { 0 };

		std::vector<float> seedValues;

		int writeIdx;
		int seed;
		float crossSeed;
		int count;
		float lengthSamples;
		float decay;

	public:
		MultitapDelay()
		{
			writeIdx = 0;
			seed = 0;
			crossSeed = 0.0;
			count = 1;
			lengthSamples = 1000;
			decay = 1.0;
			
			UpdateSeeds();
		}

		void SetSeed(int seed)
		{
			this->seed = seed;
			UpdateSeeds();
		}

		void SetCrossSeed(float crossSeed)
		{
			this->crossSeed = crossSeed;
			UpdateSeeds();
		}

		void SetTapCount(int tapCount)
		{
			if (tapCount < 1) tapCount = 1;
			count = tapCount;
			Update();
		}

		void SetTapLength(int tapLengthSamples)
		{
			if (tapLengthSamples < 10) tapLengthSamples = 10;
			lengthSamples = tapLengthSamples;
			Update();
		}

		void SetTapDecay(float tapDecay)
		{
			decay = tapDecay;
		}

		void Process(float* input, float* output, int bufSize)
		{
			float lengthScaler = lengthSamples / (float)count;
			float totalGain = 3.0f / sqrtf(1 + count);
			totalGain *= (1 + decay * 2);

			for (int i = 0; i < bufSize; i++)
			{
				delayBuffer[writeIdx] = input[i];
				output[i] = 0;

				for (int j = 0; j < count; j++)
				{
					float offset = tapPosition[j] * lengthScaler;
					float decayEffective = expf(-offset / lengthSamples * 3.3f) * decay + (1-decay);
					int readIdx = writeIdx - (int)offset;
					if (readIdx < 0) readIdx += DelayBufferSize;

					output[i] += delayBuffer[readIdx] * tapGains[j] * decayEffective * totalGain;
				}

				writeIdx = (writeIdx + 1) % DelayBufferSize;
			}
		}

		void ClearBuffers()
		{
			Utils::ZeroBuffer(delayBuffer, DelayBufferSize);
		}


	private:
		void Update()
		{
			int s = 0;
			auto rand = [&]() {return seedValues[s++]; };

			for (int i = 0; i < MaxTaps; i++)
			{
				float phase = rand() < 0.5 ? 1 : -1;
				tapGains[i] = Utils::DB2Gainf(-20 + rand() * 20) * phase;
				tapPosition[i] = i + rand();
			}
		}

		void UpdateSeeds()
		{
			this->seedValues = RandomBuffer::Generate(seed, MaxTaps * 3, crossSeed);
			Update();
		}
	};
}
