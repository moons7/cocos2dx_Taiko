#ifdef GL_ES
precision mediump float;
#endif
uniform  vec2 v_animLight;
varying  vec2 v_texCoord;

void main()
{       
     const float pi=3.14159; 
    vec2 uv=-1.0+2*v_texCoord;//同样扩展UV,扩展后UV坐标保证了X与Y坐标同时扩散的要求~~
    vec4 backGhost=texture2D(CC_Texture0,v_texCoord*cos(v_animLight.x*pi));//但会出现四个扩展后的子图像,暂时无法解决= =
    gl_FragColor = texture2D(CC_Texture0,v_texCoord)+backGhost*cos(v_animLight.x*pi)*0.2;
}