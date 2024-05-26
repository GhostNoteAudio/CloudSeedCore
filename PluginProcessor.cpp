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

#include <iostream>
#include <fstream>
#include "DSP/ReverbController.h"
#include "Programs.h"

using namespace Cloudseed;

Cloudseed::ReverbController reverb(48000);

void start(float* programData, int samplerate)
{
	for (int i = 0; i < Parameter::COUNT; i++)
	{
		reverb.SetParameter(i, programData[i]);
	}

	reverb.SetSamplerate(samplerate);
	reverb.ClearBuffers();
}

void printSettings()
{
	auto params = reverb.GetAllParameters();
	char buffer[32];
	for (int i = 0; i < Parameter::COUNT; i++)
	{
		FormatParameter(params[i], MAX_STR_SIZE, i, buffer);
		std::cout << ParameterLabel[i] << ": " << buffer << "\r\n";
	}
}

void processBlock (float* inputL, float* inputR, float* outputL, float* outputR, int bufferSize)
{
    reverb.Process(inputL, inputR, outputL, outputR, bufferSize);
}

int main()
{
	initPrograms();
	int samplerate = 48000;
	int sampleCount = samplerate * 5;

	// Apply the program parameters and set the samplerate
	start(ProgramDarkPlate, samplerate);

	// Print all the settings in human-readable form
	printSettings();

	// Process an impulse response input and store the output
	auto inputL = new float[sampleCount] { 0.0f };
	auto inputR = new float[sampleCount] { 0.0f };
	auto outputL = new float[sampleCount];
	auto outputR = new float[sampleCount];
	inputL[10000] = 1.0f;
	inputR[10000] = 1.0f;
	processBlock(inputL, inputR, outputL, outputR, sampleCount);

	// Write outputs to file
	int totalOutputBytes = sampleCount * 4;
	std::ofstream fsL("outputLeft.bin", std::ios::out | std::ios::binary | std::ios::app);
	std::ofstream fsR("outputRight.bin", std::ios::out | std::ios::binary | std::ios::app);
	fsL.write((char*)outputL, totalOutputBytes);
	fsR.write((char*)outputR, totalOutputBytes);
	fsL.close();
	fsR.close();
}