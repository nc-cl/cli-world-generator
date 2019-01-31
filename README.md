## CLI World Generator
<img src="https://i.imgur.com/4TUrKIH.jpg" width=400 height=210><img src="https://i.imgur.com/sDqgUzr.jpg" width=400 height=210>

A Perlin noise-based height map generator. Originally displaying maps via printing to the command line, the primary function of the program is now to produce a mesh from the generated map data.


### Dependencies
OpenGL 3.3+ / GLSL 330+<br>
GlEW\* (apt: libglew-dev)<br>
GLM\* (libglm-dev)<br>
SDL2\* (libsdl2-dev)<br>
Boost program\_options library\* (libboost-program-options-dev, or libboost-all-dev)<br>
<br>
\**Only the latest versions available via apt have been tested.*<br>


### Options
<b>--help</b>
Display these options.

<b>-x</b>, <b>-y</b>
Specifies the dimensions of the map. Integer; default values are 100x100.

<b>--octaves</b>, <b>-o</b><br>
Specifies the number of octaves used in Perlin noise generation; maps with less octaves will more closely resemble white noise. Integer; default value is 4.

<b>--lacunarity</b>, <b>-l</b><br>
Specifies the map lacunarity; increasing results in less smaller map details and larger biomes. Float; default value is 2.

<b>--persistence</b>, <b>-p</b><br>
Decreasing results in smooth, unnatural-looking biome boundaries. Increasing has a similar effect to decreasing the number of octaves or the lacunarity. Float; default value is 0.4.

<b>--sea-level</b>, <b>-s</b><br>
Specifies the sea level. Float; default value is 0.45, valid values are between 0 and 1.

<b>--border-value</b>, <b>-b</b><br>
Specifies the height value at the map's borders. Float; default value is 0, valid values are between 0 and 1.

<b>--border-falloff</b>, <b>-f</b><br>
Specifies the change in height as the distance from the map border increases. Float; default value is 0.04, valid values are between -1 and 1.

<b>--no-border</b>
Do not apply an ocean border to the map.

<b>--wireframe</b>, <b>-w</b><br>
Displays the map mesh as a wireframe.

<b>--print</b>
Prints the map - the program's previous default behaviour.

<b>--print-nocol</b>
Prints the map without colour - useful in the failure of ANSI escape sequences.
