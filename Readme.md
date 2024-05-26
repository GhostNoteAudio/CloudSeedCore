# Cloud Seed Core

This is the core DSP code of Cloud Seed 2.0

**You can download and purchase the plugin here:**

**https://ghostnoteaudio.uk/products/cloudseed**

The plugin itself is not open source, but the core reverb algorithm is.

This repository contains all the necessary code to integrate the Cloud Seed algorithm into your application.

# License

This code it MIT Licensed. In short:

* You can use this plugin for both free and commercial purposes.
* Please credit Ghost Note Audio as the original author of this code.
* You *can* use the name "Cloud Seed" in your marketing material, but please do so respectfully, and in a way that would not confuse potential customers. It should be clear that your product is NOT created by Ghost Note Audio, even if it does use our algorithm.
    * I do reserve the right to ask you to please stop using the Cloud Seed name, should you not adhere to this.
* If you can, please drop us a line at support@ghostnoteaudio.uk - we love seeing what people are using our algorithms for, and we're usually happy to offer suggestions and advice!

# Build Instructions

This is a bare-bones console C++ program. It requires C++14 to compile.

The demo program creates an impulse and feeds it through the reverb. It's only meant to show how the API works, and how to call the necessary functions and pass in the right argument to get it working.

The output is written to a raw binary file, which you can open using Audacity:

* File -> Import -> Raw Data
* Encoding: 32-bit float
* Byte order: default endianness
* Channels: 1 Channel (mono)
* Sample Rate: 48000 Hz

## Preprocessor Definitions

    BUFFER_SIZE=1024 (or whatever you want the maximum supported buffer size to be)
    MAX_STR_SIZE=32 (maximum length of strings being formatted and returned)
