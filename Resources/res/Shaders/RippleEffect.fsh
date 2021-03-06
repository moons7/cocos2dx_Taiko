﻿varying vec4 v_fragmentColor; 
varying vec2 v_texCoord;
uniform float u_rippleDistance;
uniform float u_rippleRange;
uniform float v_x;
uniform float v_y;
 
float waveHeight(vec2 p) {
    float ampFactor = 1;
    float distFactor = 5;
    float dist = length(p);
    float delta = abs(u_rippleDistance - dist);
    if (delta <= u_rippleRange) {
    return cos((u_rippleDistance - dist) * distFactor) * (u_rippleRange - delta) * ampFactor;
    }
    else {
  return 0;
    }
}
 
void main() {
    vec2 p = v_texCoord - vec2(v_x, v_y);
    vec2 normal = normalize(p);
    v_texCoord += normal * waveHeight(p);
    gl_FragColor = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
}