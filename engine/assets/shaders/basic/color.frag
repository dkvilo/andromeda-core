#version 450 core

in VS_OUT
{
	vec3 Color;
	vec2  TexCoords;
	float Time;
} vs_in;

out vec4 outColor;

uniform sampler2D u_Tex0;

vec2 random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(st)*43758.5453123);
}

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise based on Morgan McGuire @morgan3d
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

#define NUM_OCTAVES 5

float fbm ( in vec2 _st) {
    float v = 0.0;
    float a = 0.5;
    vec2 shift = vec2(100.0);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5),
                    -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(_st);
        _st = rot * _st * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}

void main()
{


	vec3 col = vs_in.Color;
	vec2 st = vec2(
			vs_in.TexCoords.x 
		,
			vs_in.TexCoords.y 
	);
    
	vec3 color = vs_in.Color;

    // Scale
    st *= 7.5;

    // Tile the space
    vec2 i_st = floor(st);
    vec2 f_st = fract(st);

    float m_dist = 1.;  // minimum distance

    for (int y= -1; y <= 1; y++) {
        for (int x= -1; x <= 1; x++) {
            // Neighbor place in the grid
            vec2 neighbor = vec2(float(x),float(y));

            // Random position from current + neighbor place in the grid
            vec2 point = random2(i_st + neighbor);

			// Animate the point
            point = 0.5 + 0.5*sin(vs_in.Time + 6.2831*point);

			// Vector between the pixel and the point
            vec2 diff = neighbor + point - f_st;

            // Distance to the point
            float dist = length(diff);

            // Keep the closer distance
            m_dist = min(m_dist, dist);
        }
    }

    // Draw the min distance (distance field)
    // outColor += m_dist * vec4(color, 0.001);


	// st += noise2(st * 20.) * 1.1;

	// col += vec3(1.) * smoothstep(.15, .2, noise(st * 10.)); // Black splatter
	// col += smoothstep(.15, .2, noise(st * 10.)); // Black splatter
    // col -= smoothstep(.35, .4, noise(st * 10.)); // Holes on splatter

	// outColor = texture(u_Tex0, vs_in.TexCoords) * vec4(col, 1.0);

	float Time = vs_in.Time ;

	vec2 q = vec2(0.);
    q.x = fbm( st + 0.00 * Time);
    q.y = fbm( st + vec2(1.0));

    vec2 r = vec2(0.);
    r.x = fbm( st + 1.0 * q + vec2(1.7,9.2) + 0.15 * Time);
    r.y = fbm( st + 1.0 * q + vec2(8.3,2.8) + 0.126 * Time);

    float f = fbm(st + r);

    color = mix(vec3(0.101961, 0.619608, 0.666667),
                vec3(0.666667, 0.666667, 0.498039),
                clamp((f * f) * 4.0, 0.0, 1.0));

    color = mix(color,
                vec3(0, 0, 0.164706),
                clamp(length(q), 0.0, 1.0));

    color = mix(color,
                vec3(0.666667, 1, 1),
                clamp(length(r.x), 0.0, 1.0));

    outColor = vec4((f * f * f + .6 * f * f + .5 * f) * color, 1.);
}
