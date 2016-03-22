#ifdef GL_ES
precision mediump float;
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif
uniform float progress;
uniform float region;
uniform float x_offset;
uniform float y_offset;

void main()            
{
	vec4 v_orColor =texture2D(CC_Texture0, vec2((v_texCoord.x+x_offset),(v_texCoord.y+y_offset))*region);
	float alpha=0.0f;
	if(progress-v_orColor.a<=0) 
	   alpha=progress;
     else  alpha=1-progress;
    gl_FragColor = v_orColor*alpha;
}      