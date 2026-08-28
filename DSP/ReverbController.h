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
#include "../Parameters.h"
#include "ReverbChannel.h"
#include "AllpassDiffuser.h"
#include "MultitapDelay.h"
#include "Utils.h"

namespace Cloudseed
{
	class ReverbController
	{
	private:
		int samplerate;

		ReverbChannel channelL;
		ReverbChannel channelR;
		float parameters[(int)Parameter::COUNT] = {0};

	public:
		ReverbController(int samplerate) :
			channelL(samplerate, ChannelLR::Left),
			channelR(samplerate, ChannelLR::Right)
		{
			this->samplerate = samplerate;
		}

		int GetSamplerate()
		{
			return samplerate;
		}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

		void SetSamplerate(int samplerate)
		{
			this->samplerate = samplerate;
			channelL.SetSamplerate(samplerate);
			channelR.SetSamplerate(samplerate);
		}
#pragma clang diagnostic pop

		int GetParameterCount()
		{
			return Parameter::COUNT;
		}

		float* GetAllParameters()
		{
			return parameters;
		}

		void SetParameter(int paramId, float value)
		{
			parameters[paramId] = value;
			auto scaled = ScaleParam(value, paramId);
			channelL.SetParameter(paramId, scaled);
			channelR.SetParameter(paramId, scaled);
		}

		void ClearBuffers()
		{
			channelL.ClearBuffers();
			channelR.ClearBuffers();
		}

		void Process(float* inL, float* inR, float* outL, float* outR, int bufSize)
		{
			float outLTemp[MAX_BUFFER_SIZE];
			float outRTemp[MAX_BUFFER_SIZE];

			while (bufSize > 0)
			{
				int subBufSize = bufSize > MAX_BUFFER_SIZE ? MAX_BUFFER_SIZE : bufSize;
				ProcessChunk(inL, inR, outLTemp, outRTemp, subBufSize);
				Utils::Copy(outL, outLTemp, subBufSize);
				Utils::Copy(outR, outRTemp, subBufSize);
				inL = &inL[subBufSize];
				inR = &inR[subBufSize];
				outL = &outL[subBufSize];
				outR = &outR[subBufSize];
				bufSize -= subBufSize;
			}
		}

	private:
		void ProcessChunk(float* inL, float* inR, float* outL, float* outR, int bufSize)
		{
			float leftChannelIn[MAX_BUFFER_SIZE];
			float rightChannelIn[MAX_BUFFER_SIZE];

			float inputMix = ScaleParam(parameters[Parameter::InputMix], Parameter::InputMix);
			float cm = inputMix * 0.5f;
			float cmi = (1 - cm);

			for (int i = 0; i < bufSize; i++)
			{
				leftChannelIn[i] = inL[i] * cmi + inR[i] * cm;
				rightChannelIn[i] = inR[i] * cmi + inL[i] * cm;
			}

			channelL.Process(leftChannelIn, outL, bufSize);
			channelR.Process(rightChannelIn, outR, bufSize);
		}
	};
}
