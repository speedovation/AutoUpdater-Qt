#ifndef FVUPDATER_H
#define FVUPDATER_H

#include <QObject>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QXmlStreamReader>
class QNetworkReply;
class UpdaterWindow;
class FvUpdateConfirmDialog;
class UpdateFileData;
class UpdateDownloadProgress;


class FvUpdater : public QObject
{
	Q_OBJECT

public:





	void finishUpdate(QString pathToFinish = "");
	void setRequiredSslFingerPrint(QString md5);
	QString getRequiredSslFingerPrint();	// returns md5!




	
public slots:




	//
	// ---------------------------------------------------
	// ---------------------------------------------------
	// ---------------------------------------------------
	// ---------------------------------------------------
	//

protected:

	friend class UpdaterWindow;		// Uses GetProposedUpdate() and others
	friend class FvUpdateConfirmDialog;	// Uses GetProposedUpdate() and others
	UpdateFileData* GetProposedUpdate();


protected slots:

	// Update window button slots
	void InstallUpdate();
	void SkipUpdate();
	void RemindMeLater();

	// Update confirmation dialog button slots
	void UpdateInstallationConfirmed();
	void UpdateInstallationNotConfirmed();
private:

	//
	// Singleton business
	//
	// (we leave just the declarations, so the compiler will warn us if we try
	//  to use those two functions by accident)
	FvUpdater();							// Hide main constructor
	~FvUpdater();							// Hide main destructor


    UpdateDownloadProgress* dlwindow;

	//
	// Windows / dialogs
	//
#ifdef FV_GUI
	UpdaterWindow* m_updaterWindow;								// Updater window (NULL if not shown)
	void showUpdaterWindowUpdatedWithCurrentUpdateProposal();		// Show updater window
	void hideUpdaterWindow();										// Hide + destroy m_updaterWindow
	void updaterWindowWasClosed();									// Sent by the updater window when it gets closed
	FvUpdateConfirmDialog* m_updateConfirmationDialog;						// Update confirmation dialog (NULL if not shown)
	void showUpdateConfirmationDialogUpdatedWithCurrentUpdateProposal();	// Show update confirmation dialog
	void hideUpdateConfirmationDialog();									// Hide + destroy m_updateConfirmationDialog
	void updateConfirmationDialogWasClosed();								// Sent by the update confirmation dialog when it gets closed
#else
	void decideWhatToDoWithCurrentUpdateProposal();                 // Perform an action which is configured in settings
#endif

	// Available update (NULL if not fetched)
	UpdateFileData* m_proposedUpdate;

	// If true, don't show the error dialogs and the "no updates." dialog
	// (silentAsMuchAsItCouldGet from CheckForUpdates() goes here)
	// Useful for automatic update checking upon application startup.
	bool m_silentAsMuchAsItCouldGet;



	void showErrorDialog(QString message, bool showEvenInSilentMode = false);			// Show an error message
	void showInformationDialog(QString message, bool showEvenInSilentMode = false);		// Show an informational message




	//
	// SSL Fingerprint Check infrastructure
	//
	QString m_requiredSslFingerprint;

	bool checkSslFingerPrint(QUrl urltoCheck);	// true=ssl Fingerprint accepted, false= ssl Fingerprint NOT accepted





	bool searchDownloadedFeedForUpdates(QString xmlTitle,
										QString xmlLink,
										QString xmlReleaseNotesLink,
										QString xmlPubDate,
										QString xmlEnclosureUrl,
										QString xmlEnclosureVersion,
										QString xmlEnclosurePlatform,
										unsigned long xmlEnclosureLength,
										QString xmlEnclosureType);


	//
	// Helpers
	//
	void installTranslator();			// Initialize translation mechanism
	void restartApplication();			// Restarts application after update

private slots:



	//
	// Download and install Update infrastructure
	//
	void httpUpdateDownloadFinished();
	bool unzipUpdate(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString(""));	// returns true on success

signals:
	void updatedFinishedSuccessfully();

};

#endif // FVUPDATER_H
