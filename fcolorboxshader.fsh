uniform sampler2D s2DEarthTexture;
uniform sampler2D s2DEarthPoliticalTexture;
uniform bool bShowCenters;
uniform bool bShowPoliticalEarthMap;
uniform float fCentersRadius;
uniform lowp mat4 m4Projection;
uniform lowp mat4 m4ModelView;

varying highp vec4 v4Vertex;
highp mat4 m4ModelViewProjectionMatrix = m4Projection*m4ModelView;

float random()
{
    return fract(sin(dot(v4Vertex.xyz/vec3(100.0, 100.0, 100.0), vec3(12.9898, 78.233, 23.11)))*43758.5453123);
}

vec3 fmMiddle(vec3 v3V1, vec3 v3V2)
{
    vec3 v3Result;
    v3Result[0] = (v3V1[0] + v3V2[0])/2.0;
    v3Result[1] = (v3V1[1] + v3V2[1])/2.0;
    v3Result[2] = (v3V1[2] + v3V2[2])/2.0;
    return v3Result;
}

float fnVectorPlaneDistanse(vec3 v3Vertex, vec3 v3PlanePoint, vec3 v3PlaneNormal)
{
    float fSn, fSd, fSb;
    vec3 v3B;

    fSn = -dot(v3PlaneNormal, (v3Vertex-v3PlanePoint));
    fSd = dot(v3PlaneNormal, v3PlaneNormal);
    fSb = fSn / fSd;
    v3B = v3Vertex + fSb * v3PlaneNormal;
    return distance(v3Vertex, v3B);
}

vec3 fnGetColorByPosition()
{
    vec3 v3_h_h_h = (vec4(1.0, 1.0, 1.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_h_h_l = vec3(1.0, 1.0, -1.0);
    vec3 v3_l_h_l = vec3(-1.0, 1.0, -1.0);
    vec3 v3_l_h_h = vec3(-1.0, 1.0, 1.0);

    vec3 v3_h_l_h = vec3(1.0, -1.0, 1.0);
    vec3 v3_h_l_l = vec3(1.0, -1.0, -1.0);
    vec3 v3_l_l_l = (vec4(-1.0, -1.0, -1.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_l_l_h = vec3(-1.0, -1.0, 1.0);

    vec3 v3Vertex = v4Vertex.xyz;

    vec3 v3_normal_p_0_0 = (vec4(1.0, 0.0, 0.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_normal_n_0_0 = (vec4(-1.0, 0.0, 0.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_normal_0_p_0 = (vec4(0.0, 1.0, 0.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_normal_0_n_0 = (vec4(0.0, -1.0, 0.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_normal_0_0_p = (vec4(0.0, 0.0, 1.0, 0.0)*m4ModelViewProjectionMatrix).xyz;
    vec3 v3_normal_0_0_n = (vec4(0.0, 0.0, -1.0, 0.0)*m4ModelViewProjectionMatrix).xyz;

    float fD_p_x = fnVectorPlaneDistanse(v3Vertex, v3_h_h_h, v3_normal_p_0_0);
    float fD_n_x = fnVectorPlaneDistanse(v3Vertex, v3_l_l_l, v3_normal_n_0_0);
    float fD_p_y = fnVectorPlaneDistanse(v3Vertex, v3_h_h_h, v3_normal_0_p_0);
    float fD_n_y = fnVectorPlaneDistanse(v3Vertex, v3_l_l_l, v3_normal_0_n_0);
    float fD_p_z = fnVectorPlaneDistanse(v3Vertex, v3_h_h_h, v3_normal_0_0_p);
    float fD_n_z = fnVectorPlaneDistanse(v3Vertex, v3_l_l_l, v3_normal_0_0_n);

    float fMinD;

    fMinD = min(fD_p_x, fD_n_x);
    fMinD = min(fMinD, fD_p_y);
    fMinD = min(fMinD, fD_n_y);
    fMinD = min(fMinD, fD_p_z);
    fMinD = min(fMinD, fD_n_z);

    if (bShowCenters) {
        if (distance(normalize(v3Vertex), v3_normal_0_0_n)<fCentersRadius) {
            return vec3(1.0, 0.0, 0.0);
        }
        if (distance(normalize(v3Vertex), v3_normal_0_0_p)<fCentersRadius) {
            return vec3(1.0, 0.0, 0.0);
        }
        if (distance(normalize(v3Vertex), v3_normal_0_p_0)<fCentersRadius) {
            return vec3(1.0, 1.0, 0.0);
        }
        if (distance(normalize(v3Vertex), v3_normal_0_n_0)<fCentersRadius) {
            return vec3(1.0, 0.0, 0.0);
        }
        if (distance(normalize(v3Vertex), v3_normal_p_0_0)<fCentersRadius) {
            return vec3(1.0, 0.0, 0.0);
        }
        if (distance(normalize(v3Vertex), v3_normal_n_0_0)<fCentersRadius) {
            return vec3(1.0, 0.0, 0.0);
        }
    }
    if (fMinD==fD_p_x) {
        return vec3(0.0, 1.0, 0.0);
    }
    if (fMinD==fD_n_x) {
        return vec3(0.0, 0.0, 1.0);
    }
    if (fMinD==fD_p_y) {
        return vec3(1.0, 0.0, 0.0);
    }
    if (fMinD==fD_n_y) {
        return vec3(1.0, 1.0, 0.0);
    }
    if (fMinD==fD_p_z) {
        return vec3(0.0, 0.0, 0.0);
    }
    if (fMinD==fD_n_z) {
        return vec3(1.0, 1.0, 1.0);
    }

    /*
    float fDot_h_h_h = dot(v3Vertex, v3_h_h_h)/(length(v3Vertex)*length(v3_h_h_h));
    float fDot_h_h_l = dot(v3Vertex, v3_h_h_l)/(length(v3Vertex)*length(v3_h_h_l));
    */

    return vec3(0);
}

void main(void)
{
    gl_FragColor = mix(
        vec4(fnGetColorByPosition(), 1.0),
        vec4(texture2D(s2DEarthTexture, gl_TexCoord[0].xy).rgb, 1.0),
        vec4(0.5)
    );

    if (bShowPoliticalEarthMap) {
        vec2 v2EarthPoliticalTextureCoords = gl_TexCoord[0].xy;
        v2EarthPoliticalTextureCoords[0] += 0.417;

        gl_FragColor = mix(
            gl_FragColor,
            vec4(texture2D(s2DEarthPoliticalTexture, v2EarthPoliticalTextureCoords).rgb, 1.0),
            vec4(0.5)
        );
    }
    //gl_FragColor = vec4(vertex[0]/length(vertex), vertex[1]/length(vertex), vertex[2]/length(vertex), 0.5) + gl_Color;
    //texture2D(texture, gl_TexCoord[0].xy);
}
