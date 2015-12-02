#version $GLSL_VERSION_STR
$GLSL_DEFAULT_PRECISION_FLOAT

#pragma vp_entryPoint "oe_vt_vertModel"
#pragma vp_location   "vertex_model"
#pragma vp_order      "-FLT_MAX"

varying vec4 oe_layer_texc;
varying vec4 oe_layer_tilec;

void oe_vt_vertModel(inout vec4 vertexModel)
{
    oe_layer_texc  = gl_MultiTexCoord$VT_PRIMARY_UNIT;
    oe_layer_tilec = gl_MultiTexCoord$VT_SECONDARY_UNIT;
}
