#version 450 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
// uniform sampler2D notexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface) -- THIS WORKS WITH COLOR MIXING! :D
	// FragColor = texture(notexture, TextCoord) * vec4(ourColor. 1.0);

	// FragColor = texture(notexture, TexCoord) * vec4(ourColor, 1.0);

	// FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);

	FragColor = mix(
		texture(texture1, TexCoord), 
		texture(texture2, TexCoord), 0.3
	) * vec4(ourColor, 1.0);

	// FragColor = texture(texture1, TexCoord) * vec4(ourColor, 0.1); 

	// FragColor = mix(
	// 	texture(texture1, TexCoord) * vec4(ourColor, 0.2),
	// 	texture(texture2, TexCoord), 0.2
	// );

	// FragColor = vec4(ourColor, 1.0);
}