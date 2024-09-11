#include "ImagePatchesLoaderPlugin.h"

#include "PointData/PointData.h"
#include <TextData/TextData.h>
#include "Set.h"

#include <QtCore>
#include <QtDebug>
#include <QFile>
#include <QFileDialog>
#include <set>

#include <filesystem>

Q_PLUGIN_METADATA(IID "nl.tudelft.ImagePatchesLoaderPlugin")

using namespace mv;

// =============================================================================
// View
// =============================================================================

ImagePatchesLoaderPlugin::ImagePatchesLoaderPlugin(const PluginFactory* factory):
    LoaderPlugin(factory),
    _dataSetName("")
{
    
}

ImagePatchesLoaderPlugin::~ImagePatchesLoaderPlugin(void)
{
    
}

/**
 * Mandatory plugin override function. Any initial state can be set here.
 * This function gets called when an instance of the plugin is created.
 * In this case when someone select the loader option from the menu.
 */
void ImagePatchesLoaderPlugin::init()
{

}

/**
 * Mandatory override function. Gets called when someone selects the Example Loader option
 * from the menu containing loader plugins. This function is responsible for opening the
 * file(s) the user wants to open, process them appropriately and pass the final data to the core.
 */
void ImagePatchesLoaderPlugin::loadData()
{

    _rootFolder = QFileDialog::getExistingDirectory(
        nullptr,
        tr("Root folder"),
        _rootFolder,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    QString imageDir;
    std::set<QString> filenameSet;
    for (const auto & entry: std::filesystem::directory_iterator(_rootFolder.toStdString())) {
        if (std::filesystem::is_directory(entry)) {
            imageDir = entry.path().c_str();
            for (const auto &filename: std::filesystem::directory_iterator(imageDir.toStdString())) {
                filenameSet.insert(filename.path().c_str());
            }
        }
    }

    auto rootFolder = mv::data().createDataset<Text>("Text", "Root folder");
    std::vector<QString> rootFolder_stdvec{_rootFolder};
    rootFolder->addColumn("root folder", rootFolder_stdvec);

    auto filenames = mv::data().createDataset<Text>("Text", "Filenames", rootFolder);
    std::vector<QString> filenameVec(filenameSet.begin(), filenameSet.end());
    filenames->addColumn(imageDir, filenameVec);

    events().notifyDatasetAdded(rootFolder);
    events().notifyDatasetAdded(filenames);

    // qDebug() << filenames->getColumnNames()[0];
}

ImagePatchesLoaderPlugin* ImagePatchesLoaderPluginFactory::produce()
{
    return new ImagePatchesLoaderPlugin(this);
}

mv::DataTypes ImagePatchesLoaderPluginFactory::supportedDataTypes() const
{
    DataTypes supportedTypes;
    supportedTypes.append(PointType);
    return supportedTypes;
}
