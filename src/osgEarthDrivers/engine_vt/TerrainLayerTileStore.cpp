#include "TerrainLayerTileStore"

// vt
#include <vt/Tile.h>

namespace osgEarth { namespace Drivers { namespace VTTerrainEngine {

// extents of EPSG:3857(pseudo mercator)
const double k_minMercatorX = -20026376.39;
const double k_minMercatorY = -20048966.10;
const double k_maxMercatorX = 20026376.39;
const double k_maxMercatorY = 20048966.10;


TerrainLayerTileStore::TerrainLayerTileStore(const Profile* profile, osg::ref_ptr<ImageLayer> imageLayer)
    : _profile(profile)
    , _imageLayer(imageLayer)
    , _mipChainLength(0u)
    , _tileBorder(0u)
    , _tileSize(imageLayer->getTileSize())
{
    const DataExtentList& extents = _imageLayer->getTileSource()->getDataExtents();

    for (auto extent: extents) {
        _mipChainLength = std::max(_mipChainLength, (uint8_t)extent.maxLevel().get());
    }
    _mipChainLength = std::min(_mipChainLength, (uint8_t)15u);
}

bool TerrainLayerTileStore::initialize()
{
    return (m_initialized = _imageLayer.valid());
}

std::shared_ptr<vt::Tile> TerrainLayerTileStore::getTile( std::shared_ptr<vt::Tile> tile, const uint32_t offset /* unused */) {
    GeoImage geoImage = _imageLayer->createImage(TileKey(tile->getMipLevel(), tile->getX(), tile->getY(), _profile));

    if (geoImage.valid()) {
        std::vector<char> data(geoImage.getImage()->getTotalSizeInBytes());
        std::memcpy(data.data(), geoImage.getImage()->data(), data.size() * sizeof(char));
        tile->setData(std::move(data));
    }

    return tile;
}

uint8_t TerrainLayerTileStore::getTileBorder() {
    return _tileBorder;
}

uint16_t TerrainLayerTileStore::getTileSize() {
    return _tileSize;
}

uint8_t TerrainLayerTileStore::getMipChainLength() {
    return _mipChainLength;
}

vt::Tile::Format TerrainLayerTileStore::getTileFormat() {
    return vt::Tile::kFormatRaw;
}

vt::Tile::Compression TerrainLayerTileStore::getTileCompression() {
    return vt::Tile::k_compressionNone;
}

std::vector<char> TerrainLayerTileStore::getLookupTexture() {
    return std::vector<char>(); // empty lookup texture(not needed for terrain texturing)
}

uint32_t TerrainLayerTileStore::getLookupTextureSideSize() {
    return 0u;
}

const std::string& TerrainLayerTileStore::getName() {
    return _imageLayer->getName();
}

const std::string& TerrainLayerTileStore::getSource() {
    return _imageLayer->getTileSource()->getName();
}


} // namespace VTTerrainEngine
} // namespace Drivers
} // namespace osgEarth
