#version 330
uniform sampler2D tex;
in vec2 TexCoord;
out vec4 fragcolor;
void main() {
    fragcolor = texture(tex, TexCoord);
//    fragcolor = vec4(1.0, 1.0, 1.0, 1.0);
}
