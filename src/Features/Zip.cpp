#include "Zip.h"

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

