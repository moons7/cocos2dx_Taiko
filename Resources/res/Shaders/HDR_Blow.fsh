    varying vec2 v_texCoord;	  
	//uniform float k;
	
	vec4 xposure(vec4 _color, float gray, float ex)  
	{							  
	float b = (4.0*ex - 1.0);     
	float a = 1.0 - b;          
		float f = gray*(a*gray + b); 
		return f*_color;		  
	}			
	
	void main()				  
	{							  
		vec4 _dsColor = texture2D(CC_Texture0, v_texCoord); 
		float _lum = 0.3*_dsColor.x + 0.59*_dsColor.y;    
		vec4 _fColor = texture2D(CC_Texture0, v_texCoord);  
		gl_FragColor = xposure(_fColor, _lum, 1.1);         
	}                                                    