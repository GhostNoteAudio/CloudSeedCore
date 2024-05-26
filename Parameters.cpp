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

#include "Parameters.h"

namespace Cloudseed
{
    const char* ParameterLabel[Parameter::COUNT] = {
        "Interpolation",
        "High Cut",
        "Low Cut",
        "Input Mix",
        "High Cut",
        "Low Cut",
        "Dry",
        "Early",
        "Late",

        "Multitap Delay",
        "Count",
        "Decay",
        "Pre-delay",
        "Length",

        "Diffusion",
        "Diffusion Stages",
        "Delay",
        "Mod Amt",
        "Feedback",
        "Mod Rate",

        "Mode",
        "Line Count",
        "Diffusion",
        "Diffusion Stages",
        "Size",
        "Mod Amt",
        "Delay",
        "Mod Amt",
        "Decay",
        "Mod Rate",
        "Feedback",
        "Mod Rate",

        "Low Shelf",
        "High Shelf",
        "Lowpass",
        "Low Freq",
        "High Freq",
        "Cutoff",
        "Low Gain",
        "High Gain",
        "Cross Seed",

        "Tap Seed",
        "Diffusion Seed",
        "Delay Seed",
        "Late Diffusion Seed",
    };

}
