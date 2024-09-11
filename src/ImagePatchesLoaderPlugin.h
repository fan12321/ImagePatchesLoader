#pragma once

#include <LoaderPlugin.h>

using namespace mv::plugin;

// =============================================================================
// Loader
// =============================================================================

class ImagePatchesLoaderPlugin : public LoaderPlugin
{
    Q_OBJECT
public:
    ImagePatchesLoaderPlugin(const PluginFactory* factory);
    ~ImagePatchesLoaderPlugin(void) override;
    
    void init() override;

    void loadData() Q_DECL_OVERRIDE;

private:
    QString _dataSetName;
    QString _rootFolder;
};


// =============================================================================
// Factory
// =============================================================================

class ImagePatchesLoaderPluginFactory : public LoaderPluginFactory
{
    Q_INTERFACES(mv::plugin::LoaderPluginFactory mv::plugin::PluginFactory)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID   "nl.tudelft.ImagePatchesLoaderPlugin"
                      FILE  "ImagePatchesLoaderPlugin.json")
    
public:
    ImagePatchesLoaderPluginFactory(void) {}
    ~ImagePatchesLoaderPluginFactory(void) override {}

    ImagePatchesLoaderPlugin* produce() override;

    mv::DataTypes supportedDataTypes() const override;
};
