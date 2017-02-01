# version 400

in  vec4 Color;
in  vec2 TexCoord; 

out vec4 fColor;

uniform float Col;
uniform sampler2D Tex1;

void main() 
 { 
    fColor = Col*Color + texture2D ( Tex1, TexCoord ); 
 } 
