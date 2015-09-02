#!/bin/bash

for i in {1..9}
do
    mv 2C/frame_$i.png 2C/frame_0$i.png
    #convert -resize 15% 2C/frame_0$i.png 2C/small/frame_0$i.png
done

convert -delay 300 2C/frame_01.png -delay 6 2C/frame_02.png -delay 6 2C/frame_03.png -delay 6 2C/frame_04.png -delay 6 2C/frame_05.png -delay 6 2C/frame_06.png -delay 6 2C/frame_07.png -delay 6 2C/frame_08.png -delay 6 2C/frame_09.png -delay 6 2C/frame_10.png -delay 6 2C/frame_11.png -delay 6 2C/frame_12.png -delay 6 2C/frame_13.png -delay 6 2C/frame_14.png -delay 6 2C/frame_15.png -delay 6 2C/frame_16.png -delay 6 2C/frame_17.png -delay 6 2C/frame_18.png -delay 6 2C/frame_19.png -delay 6 2C/frame_20.png -delay 300 2C/frame_21.png -delay 12 2C/frame_22.png -delay 12 2C/frame_23.png -delay 12 2C/frame_24.png -delay 12 2C/frame_25.png -delay 12 2C/frame_26.png -delay 12 2C/frame_27.png -delay 12 2C/frame_28.png -delay 12 2C/frame_29.png -delay 12 2C/frame_30.png -delay 300 2C/frame_31.png -delay 12 2C/frame_32.png -delay 12 2C/frame_33.png -delay 12 2C/frame_34.png -delay 12 2C/frame_35.png -delay 12 2C/frame_36.png -delay 12 2C/frame_37.png -delay 12 2C/frame_38.png -delay 12 2C/frame_39.png -delay 12 2C/frame_40.png -delay 300 2C/frame_41.png -delay 12 2C/frame_42.png -delay 12 2C/frame_43.png -delay 12 2C/frame_44.png -delay 12 2C/frame_45.png -delay 12 2C/frame_46.png -delay 12 2C/frame_47.png -delay 12 2C/frame_48.png -delay 12 2C/frame_49.png -delay 12 2C/frame_50.png -delay 300 2C/frame_51.png -delay 12 2C/frame_52.png -delay 12 2C/frame_53.png -delay 12 2C/frame_54.png -delay 12 2C/frame_55.png -delay 12 2C/frame_56.png -delay 12 2C/frame_57.png -delay 12 2C/frame_58.png -delay 12 2C/frame_59.png -delay 12 2C/frame_60.png -delay 300 2C/frame_61.png 2Cb.gif

