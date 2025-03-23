#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D ballTexture;
uniform vec3 color;
uniform bool useTexture;

void main() {
    if (useTexture) 
    {
        FragColor = texture(ballTexture, TexCoords);
        if (FragColor.a < 0.1) {
            discard;  // This will discard very transparent pixels
        }
    }
    else
    {
        FragColor = vec4(color, 1.0);
    }
}
