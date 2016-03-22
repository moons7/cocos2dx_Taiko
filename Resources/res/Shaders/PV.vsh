attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;  
#ifdef GL_ES
varying mediump vec2 v_texCoord; 
#else
varying vec2 v_texCoord;
#endif

void main()    
{  
v_texCoord=a_texCoord;                          
gl_Position = CC_PMatrix * a_position;
}