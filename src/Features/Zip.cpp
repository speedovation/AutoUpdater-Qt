/****************************************************************************
**
** Copyright (C) 2015 Yash Pal, Speedovation
** Copyright (C) 2012 Linas Valiukas
**
** Contact: Speedovation Lab (info@speedovation.com)
**
** KineticWing Auto Updater
** http:// kineticwing.com
** This file is part of the KiWi Editor (IDE)
**
** Author: Yash Pal, Linas Valiukas
** License : Apache License 2.0
**
** All rights are reserved.
**
**/

#include "Zip.h"
#include "UpdaterWindow.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QNetworkReply>

#ifdef Q_OS_MAC
#include "CoreFoundation/CoreFoundation.h"
#endif

//#include "zip_file.hpp"


Zip::Zip(UpdaterWindow* window) : d(window)
{

}

Zip::~Zip()
{

}



bool Zip::unzipUpdate(const QString & filePath, const QString & extDirPath, const QString & singleFileName )
{
    //	QuaZip zip(filePath);

    //    if (!zip.open(QuaZip::mdUnzip)) {
    //		qWarning()<<tr("Error: Unable to open zip archive %1 for unzipping: %2").arg(filePath).arg(zip.getZipError());
    //		return false;
    //	}

    //	zip.setFileNameCodec("IBM866");

    //	//qWarning("Update contains %d files\n", zip.getEntriesCount());

    //	QuaZipFileInfo info;
    //	QuaZipFile file(&zip);
    //	QFile out;
    //	QString name;
    //	QDir appDir(extDirPath);
    //	for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
    //	{
    //		if (!zip.getCurrentFileInfo(&info)) {
    //			qWarning()<<tr("Error: Unable to retrieve fileInfo about the file to extract: %2").arg(zip.getZipError());
    //			return false;
    //		}

    //		if (!singleFileName.isEmpty())
    //			if (!info.name.contains(singleFileName))
    //				continue;

    //		if (!file.open(QIODevice::ReadOnly)) {
    //			qWarning()<<tr("Error: Unable to open file %1 for unzipping: %2").arg(filePath).arg(file.getZipError());
    //			return false;
    //		}

    //		name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

    //		if (file.getZipError() != UNZ_OK) {
    //			qWarning()<<tr("Error: Unable to retrieve zipped filename to unzip from %1: %2").arg(filePath).arg(file.getZipError());
    //			return false;
    //		}

    //		QFileInfo fi(name);
    //		appDir.mkpath(fi.absolutePath() );	// Ensure that subdirectories - if required - exist
    //		out.setFileName(name);
    //		out.open(QIODevice::WriteOnly);
    //		out.write( file.readAll() );
    //		out.close();

    //		if (file.getZipError() != UNZ_OK) {
    //			qWarning()<<tr("Error: Unable to unzip file %1: %2").arg(name).arg(file.getZipError());
    //			return false;
    //		}

    //		if (!file.atEnd()) {
    //			qWarning()<<tr("Error: Have read all available bytes, but pointer still does not show EOF: %1").arg(file.getZipError());
    //			return false;
    //		}

    //		file.close();

    //		if (file.getZipError() != UNZ_OK) {
    //			qWarning()<<tr("Error: Unable to close zipped file %1: %2").arg(name).arg(file.getZipError());
    //			return false;
    //		}
    //	}

    //	zip.close();

    //	if (zip.getZipError() != UNZ_OK) {
    //		qWarning()<<tr("Error: Unable to close zip archive file %1: %2").arg(filePath).arg(file.getZipError());
    //		return false;
    //	}

    return true;
}

/*!
 * \brief Zip::extract
 *
 *
 *
 *  Updater mode
 *
 *    Requires admin permission. Add manifest.
 *    Check chmod permission on current folders
 *
 *    Update mode
 *      App handler will notify about new update
 *      Launch Updater in update mode
 *      Download Latest App zip from server
 *      Extract in folder  app.version name
 *      Execute this latest Updater in install mode
 *
 *    Install mode
 *      Run Updater saying you're latest and app is old folder
 *      Make a copy of app (with version name) This may be used for rollback actions
 *      Copy all files from app.version to app
 *
 *    Clean mode
 *      Run latest updater again but from app dir
 *      Remove this extracted folder
 *      Run Updater for cleaning up folder
 *
 *
 *
 *
 * \param reply
 */

void Zip::extract(QNetworkReply* reply)
{
#ifdef Q_OS_MAC
    CFURLRef appURLRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(appURLRef, TRUE, (UInt8 *)path, PATH_MAX)) {
        // error!
    }

    CFRelease(appURLRef);
    QString filePath = QString(path);
    QString rootDirectory = filePath.left(filePath.lastIndexOf("/"));
#else
    QString rootDirectory = QCoreApplication::applicationDirPath() + "/";
#endif

    // Write download into File
    QFileInfo fileInfo=reply->url().path();
    QString fileName = rootDirectory + fileInfo.fileName();
    //qDebug()<<"Writing downloaded file into "<<fileName;

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();

    zip_file zipFile(fileName.toStdString());
    try
    {
    // Retrieve List of updated files (Placed in an extra scope to avoid QuaZIP handles the archive permanently and thus avoids the deletion.)
//            if (!zip.open(QuaZip::mdUnzip)) {
//                qWarning("testRead(): zip.open(): %d", zip.getZipError());
//                return;
//            }

//     		zip.setFileNameCodec("IBM866");

        std::vector <zip_info> updateFiles = zipFile.infolist();

        // Rename all current files with available update.
        for (int i=0;i<updateFiles.size();i++)
        {
        	QString sourceFilePath = rootDirectory + QString::fromStdString(updateFiles[i].filename);
        	QDir appDir( QCoreApplication::applicationDirPath() );

        	QFileInfo file(	sourceFilePath );
        	if(file.exists())
        	{
        		//qDebug()<<tr("Moving file %1 to %2").arg(sourceFilePath).arg(sourceFilePath+".oldversion");
        		appDir.rename( sourceFilePath, sourceFilePath+".oldversion" );
        	}
        }

        // Install updated Files
        ///unzipUpdate(fileName, rootDirectory);
        zipFile.extractall(rootDirectory.toStdString());


    }

    catch(std::exception const& e)
    {
        qDebug() << "Exception: " << e.what() << "\n";
    }



    // Delete update archive
    while(QFile::remove(fileName) )
    {
    };

    // Restart ap to clean up and start usual business
    d->manager()->helper()->restartApplication();
}
