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
#include "config.h"
#include "ModulatedAllpass.h"
#include "RandomBuffer.h"

namespace Cloudseed
{
	class AllpassDiffuser
	{
	public:
		static const int MaxStageCount = 12;

	private:
		int samplerate;

		ModulatedAllpass filters[MaxStageCount];
		int delay;
		float modRate;
		std::vector<float> seedValues;
		int seed;
		float crossSeed;

	public:
		int Stages;

		AllpassDiffuser()
		{
			crossSeed = 0.0;
			seed = 23456;
			UpdateSeeds();
			Stages = 1;

			SetSamplerate(48000);
		}

		int GetSamplerate()
		{
			return samplerate;
		}

		void SetSamplerate(int samplerate)
		{
			this->samplerate = samplerate;
			SetModRate(modRate);
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


		bool GetModulationEnabled()
		{
			return filters[0].ModulationEnabled;
		}

		void SetModulationEnabled(bool value)
		{
			for (int i = 0; i < MaxStageCount; i++)
				filters[i].ModulationEnabled = value;

		}

		void SetInterpolationEnabled(bool enabled)
		{
			for (int i = 0; i < MaxStageCount; i++)
				filters[i].InterpolationEnabled = enabled;
		}

		void SetDelay(int delaySamples)
		{
			delay = delaySamples;
			Update();
		}

		void SetFeedback(float feedback)
		{
			for (int i = 0; i < MaxStageCount; i++)
				filters[i].Feedback = feedback;
		}

		void SetModAmount(float amount)
		{
			for (int i = 0; i < MaxStageCount; i++)
				filters[i].ModAmount = static_cast<float>(amount * (0.85 + 0.3 * seedValues[MaxStageCount + i]));
		}

		void SetModRate(float rate)
		{
			modRate = rate;

			for (int i = 0; i < MaxStageCount; i++)
				filters[i].ModRate = static_cast<float>(rate * (0.85 + 0.3 * seedValues[MaxStageCount * 2 + i]) / samplerate);
		}

		void Process(float* input, float* output, int bufSize)
		{
			float tempBuffer[MAX_BUFFER_SIZE];

			filters[0].Process(input, tempBuffer, bufSize);

			for (int i = 1; i < Stages; i++)
				filters[i].Process(tempBuffer, tempBuffer, bufSize);
			
			Utils::Copy(output, tempBuffer, bufSize);
		}

		void ClearBuffers()
		{
			for (int i = 0; i < MaxStageCount; i++)
				filters[i].ClearBuffers();
		}

	private:
		void Update()
		{
			for (int i = 0; i < MaxStageCount; i++)
			{
				auto r = seedValues[i];
				auto d = std::pow(10, r) * 0.1; // 0.1 ... 1.0
				filters[i].SampleDelay = (int)(delay * d);
			}
		}

		void UpdateSeeds()
		{
			this->seedValues = RandomBuffer::Generate(seed, MaxStageCount * 3, crossSeed);
			Update();
		}

	};
}
