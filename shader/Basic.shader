    #shader vertex

    #version 400 core

    layout(location = 0) in vec3 position;
    layout(location = 1) in vec2 TexCoord;
    layout(location = 2) in float index;

    uniform mat4 u_MVP;

    out vec2 f_TexCoord;
    out float f_index;

    void main()
    {
      gl_Position = u_MVP * vec4(position, 1.0);
      f_TexCoord = TexCoord;
      f_index = index;
    }


    #shader fragment

    #version 400 core

    in vec2 f_TexCoord;
    in float f_index;
    in vec4 gl_FragCoord;

    uniform sampler2D u_Sampler;
    uniform float u_rgb[3];
	vec4 mixing = vec4(u_rgb[0], u_rgb[1], u_rgb[2], 1.0);

    layout(location = 0) out vec4 color;

    void main()
    {
        float dist = length(gl_FragCoord.xy / vec2(1580,720) - vec2(0.3, 0.5));

        if (f_index == 0)
            color = texture(u_Sampler, f_TexCoord) * mixing;
        else if (f_index == -1)
            color = texture(u_Sampler, f_TexCoord);
        else if (f_index == 1)
            color = vec4(1.0, 1.0, 1.0, 1.0) * mixing;
        else if (f_index == 2)
            color = vec4(0.0f, 0.0f, 0.0f, dist * 1.7);
        else if (f_index == 3)
            color = vec4(0.1, 0.1, 0.1, 0.7);
        else if (f_index == 4)
            color = vec4(1.0, 0.6, 0.0, 1.0);
    }