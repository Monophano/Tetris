// Gaussian blur shader
uniform sampler2D texture;
uniform vec2 resolution;

void main() {
    vec2 coord = gl_TexCoord[0].xy;
    vec4 sum = vec4(0);
    sum += texture2D(texture, vec2(coord.x - 4.0, coord.y)) * 0.05;
    sum += texture2D(texture, vec2(coord.x - 3.0, coord.y)) * 0.09;
    sum += texture2D(texture, vec2(coord.x - 2.0, coord.y)) * 0.12;
    sum += texture2D(texture, vec2(coord.x - 1.0, coord.y)) * 0.15;
    sum += texture2D(texture, vec2(coord.x, coord.y)) * 0.16;
    sum += texture2D(texture, vec2(coord.x + 1.0, coord.y)) * 0.15;
    sum += texture2D(texture, vec2(coord.x + 2.0, coord.y)) * 0.12;
    sum += texture2D(texture, vec2(coord.x + 3.0, coord.y)) * 0.09;
    sum += texture2D(texture, vec2(coord.x + 4.0, coord.y)) * 0.05;
    gl_FragColor = sum;
}