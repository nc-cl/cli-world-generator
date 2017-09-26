## GenMap
A simple command line map generator. Perlin noise is used to generate various geographical properties, from which map biomes are computed.

Compiled using:<br>
g++ -std=c++11 -Wall -o gen gen.cc

## Options
<b>--no-color</b>, <b>-nc</b><br>
Prints the map with no color.

<b>--size</b>, <b>-s</b><br>
Specifies the map size; the first argument is the width, the second is the height.

<b>--width</b>, <b>-w</b>, <b>-x</b><br>
Specifies only the width. Integer; default value is 120.

 <b>--height</b>, <b>-h</b>, <b>-y</b><br>
Specifies only the height. Integer; default value is 40.

<b>--octaves</b>, <b>-o</b><br>
Specifies the number of octaves used in Perlin noise generation; maps with less octaves will more closely resemble white noise. Integer; default value is 4.

<b>--lacunarity</b>, <b>-l</b><br>
Specifies the map lacunarity; increasing results in less smaller map details and larger biomes. Floating-point; default value is 2.

<b>--persistence</b>, <b>-p</b><br>
Decreasing results in smooth, unnatural-looking biome boundaries. Increasing has a similar effect to decreasing the number of octaves or the lacunarity. Floating-point; default value is 0.4.
