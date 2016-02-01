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
mesh2 {
vertex_vectors {
3,
<0,0,0>
<1,0,0>
<1,1,0>
}
face_indices {
1
<0,1,2>
}
pigment {rgb 1}
}
