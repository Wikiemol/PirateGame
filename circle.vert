#version 330
uniform vec2 screenDimensions;
uniform vec2 objectDimensions;
uniform vec2 translation;
uniform mat2x2 rotation;
in vec3 pos;
in vec2 texCoord;
out vec3 fragposition;
out vec2 TexCoord;

void main() {
    //For the circle shader, we don't need the rotation
    //really, but we need this to be complient
    //with rectangle program
    mat2x2 identity = rotation;
    vec3 position = pos;
    position.xy *= objectDimensions.x / 2.0;
    position.xy += translation;
    position.xy /= screenDimensions;

    gl_Position.xyz = position;
    gl_Position.w = 1;
    fragposition = (pos * (objectDimensions.x / 2.0));
    fragposition.xy += translation;
    TexCoord = texCoord;
}

