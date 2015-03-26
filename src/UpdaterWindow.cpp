#include "UpdaterWindow.h"
#include "ui_UpdaterWindow.h"

#include "fvupdater.h"
#include "fvavailableupdate.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>


UpdaterWindow::UpdaterWindow(QWidget *parent, bool skipVersionAllowed, bool remindLaterAllowed) :
	QWidget(parent, Qt::CustomizeWindowHint),
	m_ui(new Ui::UpdaterWindow)
{
	m_ui->setupUi(this);

	m_appIconScene = 0;

	if(!skipVersionAllowed)
		m_ui->skipThisVersionButton->hide();
	if(!remindLaterAllowed)
		m_ui->remindMeLaterButton->hide();

	// Delete on close
	setAttribute(Qt::WA_DeleteOnClose, true);

	// Set the "new version is available" string
	QString newVersString = m_ui->newVersionIsAvailableLabel->text().arg(QApplication::applicationName());
	m_ui->newVersionIsAvailableLabel->setText(newVersString);

	// Connect buttons
	connect(m_ui->installUpdateButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(InstallUpdate()));
	connect(m_ui->skipThisVersionButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(SkipUpdate()));
	connect(m_ui->remindMeLaterButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(RemindMeLater()));
}

UpdaterWindow::~UpdaterWindow()
{
//	m_ui->releaseNotesWebView->stop();
	delete m_ui;
}

bool UpdaterWindow::UpdateWindowWithCurrentProposedUpdate()
{
	FvAvailableUpdate* proposedUpdate = FvUpdater::sharedUpdater()->GetProposedUpdate();
	if (! proposedUpdate) {
		return false;
	}

	QString downloadString = m_ui->wouldYouLikeToDownloadLabel->text()
			.arg(QApplication::applicationName(), proposedUpdate->GetEnclosureVersion(), QApplication::applicationVersion());
	m_ui->wouldYouLikeToDownloadLabel->setText(downloadString);

    //Get change notes from download link and set it inside
    //m_ui->releaseNotes

//	m_ui->releaseNotesWebView->stop();
//	m_ui->releaseNotesWebView->load(proposedUpdate->GetReleaseNotesLink());

	return true;
}

void UpdaterWindow::closeEvent(QCloseEvent* event)
{
	///FvUpdater::sharedUpdater()->updaterWindowWasClosed();
	event->accept();
}


