#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "clientmodel.h"

#include "version.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

void AboutDialog::setModel(ClientModel *model)
{
    if(model)
    {
	QString version = "";
	version += model->formatFullVersion();

	/* On x86 add a bit specifier to the version so that users can distinguish between
	 * 32 and 64 bit builds. On other architectures, 32/64 bit may be more ambiguous.
	 */
#if defined(__x86_64__)
	version += " " + tr("(%1-bit)").arg(64);
#elif defined(__i386__)
	version += " " + tr("(%1-bit)").arg(32);
#endif

        ui->versionLabel->setText(version);
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    close();
}
