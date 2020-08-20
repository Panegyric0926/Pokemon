#include "logondlg.h"
#include "ui_logondlg.h"
#include <QGridLayout>
#include <QHostAddress>
#include "netconfig.h"
#include "authentication.h"

LogonDlg::LogonDlg(QWidget* parent) : QDialog(parent),
ui(new Ui::LogonDlg)
{
	ui->setupUi(this);

	setWindowTitle(tr("���û�ע��"));

	// setup ui
	leUsername = new QLineEdit(this);
	lePassword = new QLineEdit(this);
	leRepeat = new QLineEdit(this);
	btnOK = new QPushButton(tr("ȷ��"), this);
	btnCancel = new QPushButton(tr("ȡ��"), this);
	leUsername->setPlaceholderText(tr("�������û���"));
	leUsername->setToolTip(tr("���ܰ����հ��ַ�������Ϊ6-30λ"));
	lePassword->setPlaceholderText(tr("����������"));
	lePassword->setToolTip(tr("����ĸ�����֡��»�����ɣ�����Ϊ6-30λ"));
	leRepeat->setPlaceholderText(tr("���ٴ�����������ȷ��"));
	lePassword->setEchoMode(QLineEdit::Password);
	leRepeat->setEchoMode(QLineEdit::Password);

	connect(btnOK, &QPushButton::clicked, this, &LogonDlg::logon);
	connect(btnCancel, &QPushButton::clicked, this, [this] { reject(); });

	// about layout
	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(leUsername, 0, 0);
	layout->addWidget(lePassword, 1, 0);
	layout->addWidget(leRepeat, 2, 0);
	layout->addWidget(btnOK, 3, 0);
	layout->addWidget(btnCancel, 4, 0);
	setLayout(layout);

	// about network
	client = new QTcpSocket(this);
	connect(client, &QTcpSocket::readyRead, this, &LogonDlg::readServerMsg);
}

LogonDlg::~LogonDlg()
{
	delete client;
	delete ui;
}

QString LogonDlg::getUsername() const
{
	return leUsername->text();
}

QString LogonDlg::getPassword() const
{
	return lePassword->text();
}

void LogonDlg::logon()
{
	if (!isValidUsername(leUsername->text()))
	{
		QMessageBox::warning(this, tr("���Ϸ����û���"), tr("�˺ű�������ĸ�����֡��»�������ҳ��Ƚ���6-30"));
		return;
	}
	else if (!isValidPassword(lePassword->text()))
	{
		QMessageBox::warning(this, tr("���Ϸ�������"), tr("�����������ĸ�����֡��»�������ҳ��Ƚ���6-30"));
		return;
	}
	else if (lePassword->text() != leRepeat->text())
	{
		QMessageBox::warning(this, tr("����"), tr("�����������벻һ��"));
		return;
	}
	client->connectToHost(QHostAddress("127.0.0.1"), 7500);

	QString msg = "logon";
	msg += ' ';
	msg += leUsername->text();
	msg += ' ';
	msg += lePassword->text();

	btnOK->setDisabled(true);

	if (client->write(msg.toLocal8Bit(), BUF_LENGTH) == -1)
	{
		// error occur
		QMessageBox::warning(this, tr("����"), tr("����������"));
		btnOK->setDisabled(false);
	}
}

void LogonDlg::readServerMsg()
{
	auto ret = client->read(BUF_LENGTH);

	btnOK->setDisabled(false);
	client->disconnectFromHost();

	if (QString(ret) == "Accept.\n")
	{
		QMessageBox::information(this, tr("ע��ɹ�"), tr("ע��ɹ�"));
		accept(); // back to mainwindow
	}
	else
	{
		QMessageBox::warning(this, tr("����"), QString::fromLocal8Bit(ret));
	}
}

int LogonDlg::exec()
{
	// clear all lineEdits
	leUsername->clear();
	lePassword->clear();
	leRepeat->clear();
	leUsername->setFocus();
	return QDialog::exec();
}

void LogonDlg::reject()
{
	client->disconnectFromHost(); // force disconnect socket
	QDialog::reject();
}