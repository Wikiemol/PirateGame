#version 330

uniform vec2 translation;
uniform vec2 objectDimensions;
uniform vec2 screenDimensions;
uniform vec4 color;

in vec3 fragposition;
out vec4 outputColor;
void main() {
    vec2 distVector = fragposition.xy;
    distVector -= (translation);
    float distsquared = dot(distVector, distVector);
    outputColor = distsquared > objectDimensions.x * objectDimensions.x / (16) ? vec4(0.0, 0.0, 0.0, 0.0) : color;
}
