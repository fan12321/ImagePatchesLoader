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

    // Could be either of the following...
    // 1.)
    // ├──root folder
    //     └──images
    //         ├──img_0
    //         ├──img_1
    //         ├──img_2
    //         └── ...
    // 2.)
    // ├──root folder
    //     ├──image_0
    //         └──img_0
    //     ├──image_1
    //         └──img_1
    //     ├──image_2
    //         └──img_2
    //     └── ...
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
