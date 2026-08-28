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

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "DSP/Utils.h"

namespace Cloudseed
{
    namespace Parameter
    {
        const int Interpolation = 0;
        const int LowCutEnabled = 1;
        const int HighCutEnabled = 2;
        const int InputMix = 3;
        const int LowCut = 4;
        const int HighCut = 5;
        const int DryOut = 6;
        const int EarlyOut = 7;
        const int LateOut = 8;

        const int TapEnabled = 9;
        const int TapCount = 10;
        const int TapDecay = 11;
        const int TapPredelay = 12;
        const int TapLength = 13;

        const int EarlyDiffuseEnabled = 14;
        const int EarlyDiffuseCount = 15;
        const int EarlyDiffuseDelay = 16;
        const int EarlyDiffuseModAmount = 17;
        const int EarlyDiffuseFeedback = 18;
        const int EarlyDiffuseModRate = 19;

        const int LateMode = 20;
        const int LateLineCount = 21;
        const int LateDiffuseEnabled = 22;
        const int LateDiffuseCount = 23;
        const int LateLineSize = 24;
        const int LateLineModAmount = 25;
        const int LateDiffuseDelay = 26;
        const int LateDiffuseModAmount = 27;
        const int LateLineDecay = 28;
        const int LateLineModRate = 29;
        const int LateDiffuseFeedback = 30;
        const int LateDiffuseModRate = 31;

        const int EqLowShelfEnabled = 32;
        const int EqHighShelfEnabled = 33;
        const int EqLowpassEnabled = 34;
        const int EqLowFreq = 35;
        const int EqHighFreq = 36;
        const int EqCutoff = 37;
        const int EqLowGain = 38;
        const int EqHighGain = 39;
        const int EqCrossSeed = 40;

        const int SeedTap = 41;
        const int SeedDiffusion = 42;
        const int SeedDelay = 43;
        const int SeedPostDiffusion = 44;

        const int COUNT = 45;
    }

    extern const char* ParameterLabel[Parameter::COUNT];

    inline float ScaleParam(float val, int index)
    {
        switch (index)
        {
        case Parameter::Interpolation:
        case Parameter::LowCutEnabled:
        case Parameter::HighCutEnabled:
        case Parameter::TapEnabled:
        case Parameter::LateDiffuseEnabled:
        case Parameter::EqLowShelfEnabled:
        case Parameter::EqHighShelfEnabled:
        case Parameter::EqLowpassEnabled:
        case Parameter::EarlyDiffuseEnabled:
            return val < 0.5f ? 0.0f : 1.0f;

        case Parameter::InputMix:
        case Parameter::EarlyDiffuseFeedback:
        case Parameter::TapDecay:
        case Parameter::LateDiffuseFeedback:
        case Parameter::EqCrossSeed:
            return val;

        case Parameter::SeedTap:
        case Parameter::SeedDiffusion:
        case Parameter::SeedDelay:
        case Parameter::SeedPostDiffusion:
            return (int)floor(val * 999.999);

        case Parameter::LowCut:
            return 20 + Utils::Resp4oct(val) * 980;
        case Parameter::HighCut:
            return 400 + Utils::Resp4oct(val) * 19600;

        case Parameter::DryOut:
        case Parameter::EarlyOut:
        case Parameter::LateOut:
            return -30 + val * 30;

        case Parameter::TapCount:
            return (int)(1 + val * 255);
        case Parameter::TapPredelay:
            return Utils::Resp1dec(val) * 500;
        case Parameter::TapLength:
            return 10 + val * 990;

        case Parameter::EarlyDiffuseCount:
            return (int)(1 + val * 11.999);
        case Parameter::EarlyDiffuseDelay:
            return 10 + val * 90;
        case Parameter::EarlyDiffuseModAmount:
            return val * 2.5f;
        case Parameter::EarlyDiffuseModRate:
            return Utils::Resp2dec(val) * 5;

        case Parameter::LateMode:
            return val < 0.5 ? 0.0 : 1.0;
        case Parameter::LateLineCount:
            return (int)(1 + val * 11.999);
        case Parameter::LateDiffuseCount:
            return (int)(1 + val * 7.999);
        case Parameter::LateLineSize:
            return 20 + Utils::Resp2dec(val) * 980;
        case Parameter::LateLineModAmount:
            return val * 2.5f;
        case Parameter::LateDiffuseDelay:
            return 10 + val * 90;
        case Parameter::LateDiffuseModAmount:
            return val * 2.5f;
        case Parameter::LateLineDecay:
            return 0.05f + Utils::Resp3dec(val) * 59.95f;
        case Parameter::LateLineModRate:
            return Utils::Resp2dec(val) * 5;
        case Parameter::LateDiffuseModRate:
            return Utils::Resp2dec(val) * 5;

        case Parameter::EqLowFreq:
            return 20 + Utils::Resp3oct(val) * 980;
        case Parameter::EqHighFreq:
            return 400 + Utils::Resp4oct(val) * 19600;
        case Parameter::EqCutoff:
            return 400 + Utils::Resp4oct(val) * 19600;
        case Parameter::EqLowGain:
            return -20 + val * 20;
        case Parameter::EqHighGain:
            return -20 + val * 20;
        }
        return 0;
    }

    inline void FormatParameter(float val, int maxLen, int paramId, char* buffer)
    {
        double s = ScaleParam(val, paramId);
        const auto maxLenTerminated = maxLen - 1;

        switch (paramId)
        {
        case Parameter::Interpolation:
        case Parameter::HighCutEnabled:
        case Parameter::LowCutEnabled:
        case Parameter::TapEnabled:
        case Parameter::LateDiffuseEnabled:
        case Parameter::EqLowShelfEnabled:
        case Parameter::EqHighShelfEnabled:
        case Parameter::EqLowpassEnabled:
        case Parameter::EarlyDiffuseEnabled:
            if (ScaleParam(val, paramId) == 1)
                strncpy(buffer, "ENABLED", maxLenTerminated);
            else
                strncpy(buffer, "ENABLED", maxLenTerminated);
            break;

        case Parameter::InputMix:
        case Parameter::EarlyDiffuseFeedback:
        case Parameter::TapDecay:
        case Parameter::LateDiffuseFeedback:
        case Parameter::EqCrossSeed:
            snprintf(buffer, maxLen, "%d%%", (int)(s * 100));
            break;

        case Parameter::SeedTap:
        case Parameter::SeedDiffusion:
        case Parameter::SeedDelay:
        case Parameter::SeedPostDiffusion:
            snprintf(buffer, maxLen, "%03d", (int)s);
            break;

        case Parameter::LowCut:
        case Parameter::HighCut:
        case Parameter::EqLowFreq:
        case Parameter::EqHighFreq:
        case Parameter::EqCutoff:
            snprintf(buffer, maxLen, "%d Hz", (int)s);
            break;

        case Parameter::DryOut:
        case Parameter::EarlyOut:
        case Parameter::LateOut:
            if (s <= -30)
                strncpy(buffer, "MUTED", maxLenTerminated);
            else
                snprintf(buffer, maxLen, "%.1f dB", s);
            break;

        case Parameter::TapCount:
        case Parameter::EarlyDiffuseCount:
        case Parameter::LateLineCount:
        case Parameter::LateDiffuseCount:
            snprintf(buffer, maxLen, "%d", (int)s);
            break;

        case Parameter::TapPredelay:
        case Parameter::TapLength:
        case Parameter::EarlyDiffuseDelay:
        case Parameter::LateLineSize:
        case Parameter::LateDiffuseDelay:
            snprintf(buffer, maxLen, "%d ms", (int)s);
            break;

        case Parameter::LateLineDecay:
            if (s < 1)
                snprintf(buffer, maxLen, "%d ms", (int)(s * 1000));
            else if (s < 10)
                snprintf(buffer, maxLen, "%.2f sec", s);
            else
                snprintf(buffer, maxLen, "%.1f sec", s);
            break;

        case Parameter::LateMode:
            if (s == 1)
                strncpy(buffer, "POST", maxLenTerminated);
            else
                strncpy(buffer, "PRE", maxLenTerminated);
            break;

        case Parameter::EarlyDiffuseModAmount:
        case Parameter::LateLineModAmount:
        case Parameter::LateDiffuseModAmount:
            snprintf(buffer, maxLen, "%d%%", (int)(s * 100));
            break;

        case Parameter::EarlyDiffuseModRate:
        case Parameter::LateLineModRate:
        case Parameter::LateDiffuseModRate:
            snprintf(buffer, maxLen, "%.2f Hz", s);
            break;

        case Parameter::EqLowGain:
        case Parameter::EqHighGain:
            snprintf(buffer, maxLen, "%.1f dB", s);
            break;

        default:
            snprintf(buffer, maxLen, "%.2f", s);
        }
    }
}
