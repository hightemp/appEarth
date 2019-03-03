uniform sampler2D s2DTexture;
varying highp vec4 v4Vertex;
varying highp mat4 m4ModelViewProjectionMatrix;

void main(void)
{
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex * vec4(gl_Vertex[0]+cos(gl_Vertex[0]), gl_Vertex[1]+cos(gl_Vertex[1]), gl_Vertex[2]+cos(gl_Vertex[2]), 1.0);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
    v4Vertex = gl_Position;
    m4ModelViewProjectionMatrix = gl_ModelViewProjectionMatrix;
}
