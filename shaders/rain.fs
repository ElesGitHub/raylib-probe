#version 330

#define PI 3.14159265359

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 pixelColor;

uniform vec2 res;
uniform float t;

void main() {
    vec2 FC = vec2(fragTexCoord.x * res.x, -fragTexCoord.y * res.y);
    vec4 o = vec4(0.);
    o.a = 1.0;

    vec2 p = (FC * 2.0 - res) / res.y;
    p *= vec2(10.0, 1.0);

    float wobble = sin(ceil(p.x) / .1 + t);

    vec2 a = vec2(.5, .1);
    vec2 f = fract(vec2(
        p.x,
        p.y + t * 4. / PI + wobble
    )) - a;

    vec2 m = 1. - max(
        -f / a,
        f / (1. - a)
    );

    float shade = m.x * m.y * tanh(.1 / (1. - m.x));
    vec3 c = vec3(.2, .8, .2);

    o.rgb = c * shade;
    pixelColor = o;
}
