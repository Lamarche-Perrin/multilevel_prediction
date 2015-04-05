#!/bin/bash

for i in {0..9}
do
    convert -resize 15% 2C/frame_0$i.png 2C/small/frame_0$i.png
done

for i in {10..60}
do
    convert -resize 15% 2C/frame_$i.png 2C/small/frame_$i.png
done

convert -delay 10 -loop 0 2C/small/*.png 2C.gif
