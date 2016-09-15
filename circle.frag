#version 330

uniform vec2 translation;
uniform vec2 objectDimensions;
uniform vec2 screenDimensions;

in vec3 fragposition;
out vec4 color;
void main() {
    vec2 distVector = fragposition.xy;
    distVector -= (translation);
    float distsquared = dot(distVector, distVector);
    color = distsquared > objectDimensions.x * objectDimensions.x / 4 ? vec4(0.0, 0.0, 0.0, 0.0) : vec4(1.0, 1.0, 1.0, 1.0);
}
