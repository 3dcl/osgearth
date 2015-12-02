#version $GLSL_VERSION_STR
$GLSL_DEFAULT_PRECISION_FLOAT

#pragma vp_entryPoint "oe_vt_vertView"
#pragma vp_location   "vertex_view"
#pragma vp_order      "0.5"

uniform float oe_layer_minRange;
uniform float oe_layer_maxRange;
uniform float oe_layer_attenuationRange;

varying float oe_layer_rangeOpacity;

void oe_vt_vertView(inout vec4 vertexView)
{
    float range = -vertexView.z;

    float attenMin    = oe_layer_minRange - oe_layer_attenuationRange;
    float attenMax    = oe_layer_maxRange + oe_layer_attenuationRange;

    oe_layer_rangeOpacity =
        oe_layer_minRange >= oe_layer_maxRange                   ? 1.0 :
        range >= oe_layer_minRange && range < oe_layer_maxRange  ? 1.0 :
        range < oe_layer_minRange                                ? clamp((range-attenMin)/oe_layer_attenuationRange, 0.0, 1.0) :
        range > oe_layer_maxRange                                ? clamp((attenMax-range)/oe_layer_attenuationRange, 0.0, 1.0) :
        0.0;
}
