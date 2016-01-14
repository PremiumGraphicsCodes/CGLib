#include "colors.inc"
#include "textures.inc"
camera {
location <1,1,-2>
look_at <0,0,0>
}
light_source {
<10,10,-10>
color rgb <1,1,1>
}
plane {
<0,1,0>,-1
pigment {color Pink}
}
mesh {
triangle {<0,0,0>
<1,0,0>
<1,1,0>
}
texture{ pigment{ color rgb <1,1,1> } } 
}
