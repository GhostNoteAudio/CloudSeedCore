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

#include "Parameters.h"

namespace Cloudseed
{
	float ProgramDarkPlate[Parameter::COUNT];

	void initPrograms()
	{
		ProgramDarkPlate[Parameter::DryOut] = 0.8705999851226807;
		ProgramDarkPlate[Parameter::EarlyDiffuseCount] = 0.2960000038146973;
		ProgramDarkPlate[Parameter::EarlyDiffuseDelay] = 0.3066999912261963;
		ProgramDarkPlate[Parameter::EarlyDiffuseEnabled] = 0.0;
		ProgramDarkPlate[Parameter::EarlyDiffuseFeedback] = 0.7706999778747559;
		ProgramDarkPlate[Parameter::EarlyDiffuseModAmount] = 0.143899992108345;
		ProgramDarkPlate[Parameter::EarlyDiffuseModRate] = 0.2466999888420105;
		ProgramDarkPlate[Parameter::EarlyOut] = 0.0;
		ProgramDarkPlate[Parameter::EqCrossSeed] = 0.0;
		ProgramDarkPlate[Parameter::EqCutoff] = 0.9759999513626099;
		ProgramDarkPlate[Parameter::EqHighFreq] = 0.5133999586105347;
		ProgramDarkPlate[Parameter::EqHighGain] = 0.7680000066757202;
		ProgramDarkPlate[Parameter::EqHighShelfEnabled] = 1.0;
		ProgramDarkPlate[Parameter::EqLowFreq] = 0.3879999816417694;
		ProgramDarkPlate[Parameter::EqLowGain] = 0.5559999942779541;
		ProgramDarkPlate[Parameter::EqLowShelfEnabled] = 0.0;
		ProgramDarkPlate[Parameter::EqLowpassEnabled] = 0.0;
		ProgramDarkPlate[Parameter::HighCut] = 0.2933000028133392;
		ProgramDarkPlate[Parameter::HighCutEnabled] = 0.0;
		ProgramDarkPlate[Parameter::InputMix] = 0.2346999943256378;
		ProgramDarkPlate[Parameter::Interpolation] = 1.0;
		ProgramDarkPlate[Parameter::LateDiffuseCount] = 0.4879999756813049;
		ProgramDarkPlate[Parameter::LateDiffuseDelay] = 0.239999994635582;
		ProgramDarkPlate[Parameter::LateDiffuseEnabled] = 1.0;
		ProgramDarkPlate[Parameter::LateDiffuseFeedback] = 0.8506999611854553;
		ProgramDarkPlate[Parameter::LateDiffuseModAmount] = 0.1467999964952469;
		ProgramDarkPlate[Parameter::LateDiffuseModRate] = 0.1666999906301498;
		ProgramDarkPlate[Parameter::LateLineCount] = 1.0;
		ProgramDarkPlate[Parameter::LateLineDecay] = 0.6345999836921692;
		ProgramDarkPlate[Parameter::LateLineModAmount] = 0.2719999849796295;
		ProgramDarkPlate[Parameter::LateLineModRate] = 0.2292999923229218;
		ProgramDarkPlate[Parameter::LateLineSize] = 0.4693999886512756;
		ProgramDarkPlate[Parameter::LateMode] = 1.0;
		ProgramDarkPlate[Parameter::LateOut] = 0.6613999605178833;
		ProgramDarkPlate[Parameter::LowCut] = 0.6399999856948853;
		ProgramDarkPlate[Parameter::LowCutEnabled] = 1.0;
		ProgramDarkPlate[Parameter::SeedDelay] = 0.2180999964475632;
		ProgramDarkPlate[Parameter::SeedDiffusion] = 0.1850000023841858;
		ProgramDarkPlate[Parameter::SeedPostDiffusion] = 0.3652999997138977;
		ProgramDarkPlate[Parameter::SeedTap] = 0.3339999914169312;
		ProgramDarkPlate[Parameter::TapDecay] = 1.0;
		ProgramDarkPlate[Parameter::TapLength] = 0.9866999983787537;
		ProgramDarkPlate[Parameter::TapPredelay] = 0.0;
		ProgramDarkPlate[Parameter::TapCount] = 0.1959999948740005;
		ProgramDarkPlate[Parameter::TapEnabled] = 0.0;
	}
}
