#ifdef GL_ES
precision mediump float;
#endif
uniform  sampler2D u_lightTexture;
uniform  vec2 v_animLight;
varying  vec2 v_texCoord;
void main(void)
{
#ifdef GL_ES
 gl_FragColor = texture2D(CC_Texture0,v_texCoord+ texture2D(u_lightTexture, v_texCoord + v_animLight);
#else
 gl_FragColor = texture2D(CC_Texture0,vec2(abs(v_texCoord.x-v_animLight.x),v_texCoord.y))+ texture2D(u_lightTexture, v_texCoord + v_animLight)*(sin(v_animLight.x)+0.5);
#endif

}