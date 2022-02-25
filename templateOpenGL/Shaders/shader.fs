// #version 330 core
// out vec4 FragColor;
// in vec3 ourColor;
// void main()
// {
//    FragColor = vec4 (ourColor, 1.0f);
   
// }

// #version 330 core
// out vec4 FragColor;
// in vec3 ourColor;
// in vec3 ourPosition;
// in vec3 TexCoord;

// void main()
// {
//     FragColor = vec4(ourPosition, 1.0);    // note how the position value is linearly interpolated to get all the different colors
// }

//只有一个纹理
// #version 330 core
// out vec4 FragColor;

// in vec3 ourColor;
// in vec2 TexCoord;

// uniform sampler2D ourTexture;

// void main()
// {
//     //FragColor = texture(ourTexture, TexCoord);
//     FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
// }

//两个纹理
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}

 
