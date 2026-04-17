#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 pixelColor;

vec2 squareComplex(vec2 z) {
    return vec2(
        z.x * z.x - z.y * z.y,
        2.0 * z.x * z.y
    );
}

void main() {
    vec2 uv = (fragTexCoord * 2 - 1) * 2;
    vec2 p = uv;
    for (int i = 1; i < 100; i++) {
        p = squareComplex(p) + uv;
        if ((p.x * p.x + p.y * p.y) > 4) break;
    }

    float color = 1;
    if ((p.x * p.x + p.y * p.y) < 4) color = 0;

    pixelColor = vec4(color, color, color, 1);
}