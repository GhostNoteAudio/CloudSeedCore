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

#include "Lp1.h"
#include "ModulatedDelay.h"
#include "AllpassDiffuser.h"
#include "Biquad.h"

namespace Cloudseed
{
	template<unsigned int N>
	class CircularBuffer
	{
		float buffer[N];
		int idxRead;
		int idxWrite;
		int count;
	public:
		CircularBuffer()
		{
			Reset();
		}

		void Reset()
		{
			for (unsigned int i = 0; i < N; i++)
				buffer[i] = 0.0f;
			idxRead = 0;
			idxWrite = 0;
			count = 0;
		}

		int GetCount()
		{
			return count;
		}

		int PushZeros(float* /*data*/, int bufSize)
		{
			int countBefore = count;
			for (int i = 0; i < bufSize; i++)
			{
				buffer[idxWrite] = 0.0f;
				idxWrite = (idxWrite + 1) % N;
				count++;
				if (count >= N)
					break; // overflow
			}

			return count - countBefore;
		}

		int Push(float* data, int bufSize)
		{
			int countBefore = count;
			for (int i = 0; i < bufSize; i++)
			{
				buffer[idxWrite] = data[i];
				idxWrite = (idxWrite + 1) % N;
				count++;
				if (count >= (int)N)
					break; // overflow
			}

			return count - countBefore;
		}

		int Pop(float* destination, int bufSize)
		{
			int countBefore = count;
			for (int i = 0; i < bufSize; i++)
			{
				if (count > 0)
				{
					destination[i] = buffer[idxRead];
					idxRead = (idxRead + 1) % N;
					count--;
				}
				else
				{
					destination[i] = 0.0f;
				}
			}

			return countBefore - count;
		}

	};

	class DelayLine
	{
	private:
		ModulatedDelay delay;
		AllpassDiffuser diffuser;
		Biquad lowShelf;
		Biquad highShelf;
		Lp1 lowPass;
		CircularBuffer<2*MAX_BUFFER_SIZE> feedbackBuffer;
		float feedback;

	public:
		bool DiffuserEnabled;
		bool LowShelfEnabled;
		bool HighShelfEnabled;
		bool CutoffEnabled;
		bool TapPostDiffuser;

		DelayLine() :
			lowShelf(Biquad::FilterType::LowShelf, 48000),
			highShelf(Biquad::FilterType::HighShelf, 48000)
		{
			feedback = 0;

			lowShelf.SetGainDb(-20);
			lowShelf.Frequency = 20;

			highShelf.SetGainDb(-20);
			highShelf.Frequency = 19000;

			lowPass.SetCutoffHz(1000);
			lowShelf.Update();
			highShelf.Update();
			SetSamplerate(48000);
			SetDiffuserSeed(1, 0.0);
		}

		void SetSamplerate(int samplerate)
		{
			diffuser.SetSamplerate(samplerate);
			lowPass.SetSamplerate(samplerate);
			lowShelf.SetSamplerate(samplerate);
			highShelf.SetSamplerate(samplerate);
		}

		void SetDiffuserSeed(int seed, float crossSeed)
		{
			diffuser.SetSeed(seed);
			diffuser.SetCrossSeed(crossSeed);
		}

		void SetDelay(int delaySamples)
		{
			delay.SampleDelay = delaySamples;
		}

		void SetFeedback(float feedb)
		{
			feedback = feedb;
		}

		void SetDiffuserDelay(int delaySamples)
		{
			diffuser.SetDelay(delaySamples);
		}

		void SetDiffuserFeedback(float feedb)
		{
			diffuser.SetFeedback(feedb);
		}

		void SetDiffuserStages(int stages)
		{
			diffuser.Stages = stages;
		}

		void SetLowShelfGain(float gainDb)
		{
			lowShelf.SetGainDb(gainDb);
			lowShelf.Update();
		}

		void SetLowShelfFrequency(float frequency)
		{
			lowShelf.Frequency = frequency;
			lowShelf.Update();
		}

		void SetHighShelfGain(float gainDb)
		{
			highShelf.SetGainDb(gainDb);
			highShelf.Update();
		}

		void SetHighShelfFrequency(float frequency)
		{
			highShelf.Frequency = frequency;
			highShelf.Update();
		}

		void SetCutoffFrequency(float frequency)
		{
			lowPass.SetCutoffHz(frequency);
		}

		void SetLineModAmount(float amount)
		{
			delay.ModAmount = amount;
		}

		void SetLineModRate(float rate)
		{
			delay.ModRate = rate;
		}

		void SetDiffuserModAmount(float amount)
		{
			diffuser.SetModulationEnabled(amount > 0.0);
			diffuser.SetModAmount(amount);
		}

		void SetDiffuserModRate(float rate)
		{
			diffuser.SetModRate(rate);
		}

		void SetInterpolationEnabled(bool value)
		{
			diffuser.SetInterpolationEnabled(value);
		}

		void Process(float* input, float* output, int bufSize)
		{
			float tempBuffer[MAX_BUFFER_SIZE];
			feedbackBuffer.Pop(tempBuffer, bufSize);

			for (int i = 0; i < bufSize; i++)
				tempBuffer[i] = input[i] + tempBuffer[i] * feedback;

			delay.Process(tempBuffer, tempBuffer, bufSize);
			
			if (!TapPostDiffuser)
				Utils::Copy(output, tempBuffer, bufSize);
			if (DiffuserEnabled)
				diffuser.Process(tempBuffer, tempBuffer, bufSize);
			if (LowShelfEnabled)
				lowShelf.Process(tempBuffer, tempBuffer, bufSize);
			if (HighShelfEnabled)
				highShelf.Process(tempBuffer, tempBuffer, bufSize);
			if (CutoffEnabled)
				lowPass.Process(tempBuffer, tempBuffer, bufSize);

			feedbackBuffer.Push(tempBuffer, bufSize);

			if (TapPostDiffuser)
				Utils::Copy(output, tempBuffer, bufSize);
		}

		void ClearDiffuserBuffer()
		{
			diffuser.ClearBuffers();
		}

		void ClearBuffers()
		{
			delay.ClearBuffers();
			diffuser.ClearBuffers();
			lowShelf.ClearBuffers();
			highShelf.ClearBuffers();
			lowPass.Output = 0;
			feedbackBuffer.Reset();
		}
	};
}
