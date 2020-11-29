# WFC Cloth Mesh Corrugator
A procedural mesh corrugator in C++ to generate corrugated vertices given a mesh for cloth simulation. This software is used as a module in a PBD cloth simulator for realistic knitted clothes simulation. It is part of the paper titled <i>A Procedural Approach For Cloth Simulation</i><sup>\*</sup>, authored by Wei Guo, Yihao Wang and Kai Zhang.

Author: Wei Guo <a href="mailto:wei.parker.guo.sg@gmail.com">wei.parker.guo.sg@gmail.com</a>

Date of Initiation: 11/29/2020

<sub><sup>\*The paper discussed here is under publishing process. A link will be provided for full text when it's officially published.</sup></sub>

# Usage
This is a platform independent cmake project. The executables are built using Visual Studio on the author's machine for Windows in 64 bits.

## Input Image Formats
An input image is required for the corrugator to procedurally generate patterns that are similar to it. It should represent the knitting pattern of desired cloth material, with white pixels indicating space and black indicating cloth fiber. The image could be either png or jpeg. You will be prompted in the console to supply this image's path.

# References
<li>tooljpeg jpeg encoder from <a href="https://create.stephan-brumme.com/toojpeg/">https://create.stephan-brumme.com/toojpeg/</a></li>
<li>stb_image.h jpeg image loader from <a href="https://raw.githubusercontent.com/nothings/stb/master/stb_image.h">https://raw.githubusercontent.com/nothings/stb/master/stb_image.h</a></li>
