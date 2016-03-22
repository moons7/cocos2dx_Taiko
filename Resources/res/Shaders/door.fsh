uniform float iGlobalTime;
varying vec2 v_texCoord;
//uniform  sampler2D u_lightTexture;
void main()
{       
    float pi=3.14159;
    //gl_FragColor =texture2D(CC_Texture0,vec2(v_texCoord.x - sin(iGlobalTime*pi),v_texCoord.y));
	gl_FragColor =texture2D(CC_Texture0,vec2(v_texCoord.x+abs(sin(iGlobalTime*pi)),v_texCoord.y))*step(v_texCoord.x,0.5f-abs(sin(iGlobalTime*pi)))*abs(cos(iGlobalTime*pi))+texture2D(CC_Texture0, vec2(v_texCoord.x-abs(sin(iGlobalTime*pi)),v_texCoord.y))*step(0.5f+abs(sin(iGlobalTime*pi)),v_texCoord.x)*abs(cos(iGlobalTime*pi));
}
