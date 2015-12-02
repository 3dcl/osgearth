OPTION(ENABLE_ENGINE_VT "Set to ON to build optional virtual texturing terrain engine." OFF)
IF(ENABLE_ENGINE_VT)

find_package(VT REQUIRED)

INCLUDE_DIRECTORIES(
    ${VT_INCLUDE_DIR}
)

SET(TARGET_COMMON_LIBRARIES ${TARGET_COMMON_LIBRARIES} ${VT_LIBRARIES} osgEarthSymbology)

set(TARGET_GLSL
    VTEngine.vert.model.glsl
    VTEngine.vert.view.glsl
    VTEngine.frag.glsl)

set(TARGET_IN
    VTShaders.cpp.in)

set(SHADERS_CPP "${CMAKE_CURRENT_BINARY_DIR}/AutoGenShaders.cpp")

configure_shaders(
    VTShaders.cpp.in
    ${SHADERS_CPP}
    ${TARGET_GLSL} )

SET(TARGET_SRC
    HeightFieldCache.cpp
    KeyNodeFactory.cpp
    VTGeometry.cpp
    VTTerrainEngineNode.cpp
    VTTerrainEngineDriver.cpp
    SingleKeyNodeFactory.cpp
    TerrainNode.cpp
    TileGroup.cpp
    TileModel.cpp
    TileModelCompiler.cpp
    TileNode.cpp
    TileNodeRegistry.cpp
    TileModelFactory.cpp
    TilePagedLOD.cpp
    ${SHADERS_CPP}
)

SET(TARGET_H
    Common
    DynamicLODScaleCallback
    HeightFieldCache
    FileLocationCallback
    KeyNodeFactory
    VTGeometry
    VTShaders
    VTTerrainEngineNode
    VTTerrainEngineOptions
    QuickReleaseGLObjects
    SingleKeyNodeFactory
    TerrainNode
    TileGroup
    TileModel
    TileModelCompiler
    TileNode
    TileNodeRegistry
    TileModelFactory
    TilePagedLOD
)

setup_plugin(osgearth_engine_vt)

# to install public driver includes:
SET(LIB_NAME engine_vt)
SET(LIB_PUBLIC_HEADERS ${TARGET_H})
INCLUDE(ModuleInstallOsgEarthDriverIncludes OPTIONAL)

ENDIF()
