uniform sampler2D s2DTexture;
varying highp vec4 v4Vertex;
varying highp mat4 m4ModelViewProjectionMatrix;

mat4 fnInverse(mat4 m4In)
{
    mat4 m4Result;

    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            m4Result[i][j] = -m4In[i][j];
        }
    }

    return m4Result;
}

void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
    v4Vertex = gl_Position;
    m4ModelViewProjectionMatrix = gl_ModelViewProjectionMatrix;
}
