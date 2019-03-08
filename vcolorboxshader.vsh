uniform sampler2D s2DTexture;
varying highp vec4 v4Vertex;
//varying highp mat4 m4ModelViewProjectionMatrix;

void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
    v4Vertex = gl_Position;
    //m4ModelViewProjectionMatrix = gl_ModelViewProjectionMatrix;
}
