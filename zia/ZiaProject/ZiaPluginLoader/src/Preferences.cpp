#include <iostream>
#include <QSettings>
#include "Preferences.h"

Preferences::Preferences(QWidget* parent) : QDialog(parent)
{
	setupUi(this);
	readSettings();
	update();
	connect(this, SIGNAL(accepted()), SLOT(save()));
}

Preferences::~Preferences(void)
{
}

void	Preferences::readSettings(void)
{
	QSettings	settings("Epitech", "ZiaPluginLoader");

	settings.beginGroup("Preferences");
	this->_ip = settings.value("ip", QString("127.0.0.1")).toString();
	this->_port = settings.value("port", QString("42000")).toString();
	this->_login = settings.value("login", QString("")).toString();
	this->_password = settings.value("password", QString("")).toString();
	this->_savePassword = settings.value("savepassword", bool(false)).toBool();
	settings.endGroup();
}

void	Preferences::writeSettings(void)
{
	QSettings	settings("Epitech", "ZiaPluginLoader");

	settings.beginGroup("Preferences");
	settings.setValue("ip", this->_ip);
	settings.setValue("port", this->_port);
	settings.setValue("login", this->_login);
	if (true == this->_savePassword)
	{
		settings.setValue("password", this->_password);
		settings.setValue("savepassword", true);
	}
	else
	{
		settings.remove("password");
		settings.setValue("savepassword", false);
	}
	settings.endGroup();
}

void	Preferences::update(void)
{
	this->lineEditIp->setText(this->_ip);
	this->lineEditPort->setText(this->_port);
	this->lineEditLogin->setText(this->_login);
	this->lineEditPassword->setText(this->_password);
	if (this->_savePassword == true)
		this->checkBoxSavePassword->setCheckState(Qt::Checked);
	else
		this->checkBoxSavePassword->setCheckState(Qt::Unchecked);
}

void	Preferences::save(void)
{
	this->_ip = this->lineEditIp->text();
	this->_port = this->lineEditPort->text();
	this->_login = this->lineEditLogin->text();
	this->_password = this->lineEditPassword->text();
	if (Qt::Checked == this->checkBoxSavePassword->checkState())
		this->_savePassword = true;
	else
		this->_savePassword = false;
}
