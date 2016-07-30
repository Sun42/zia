/********************************************************************************
** Form generated from reading ui file 'Preferences.ui'
**
** Created: Mon Sep 21 14:41:34 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PREFERENCES_H
#define UI_PREFERENCES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QLabel *labelLogin;
    QLabel *labelPassword;
    QLabel *labelIp;
    QLineEdit *lineEditIp;
    QLineEdit *lineEditPort;
    QLineEdit *lineEditLogin;
    QPushButton *pushButtonAccept;
    QPushButton *pushButtonReject;
    QLineEdit *lineEditPassword;
    QLabel *labelPort;
    QCheckBox *checkBoxSavePassword;
    QCheckBox *checkBoxAutoConnect;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QString::fromUtf8("PreferencesDialog"));
        PreferencesDialog->setWindowModality(Qt::ApplicationModal);
        PreferencesDialog->resize(350, 200);
        PreferencesDialog->setMinimumSize(QSize(350, 200));
        PreferencesDialog->setMaximumSize(QSize(350, 200));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/images/options.png")), QIcon::Normal, QIcon::Off);
        PreferencesDialog->setWindowIcon(icon);
        labelLogin = new QLabel(PreferencesDialog);
        labelLogin->setObjectName(QString::fromUtf8("labelLogin"));
        labelLogin->setGeometry(QRect(10, 70, 141, 18));
        labelPassword = new QLabel(PreferencesDialog);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));
        labelPassword->setGeometry(QRect(10, 100, 141, 18));
        labelIp = new QLabel(PreferencesDialog);
        labelIp->setObjectName(QString::fromUtf8("labelIp"));
        labelIp->setGeometry(QRect(10, 10, 141, 18));
        lineEditIp = new QLineEdit(PreferencesDialog);
        lineEditIp->setObjectName(QString::fromUtf8("lineEditIp"));
        lineEditIp->setGeometry(QRect(160, 10, 181, 24));
        lineEditPort = new QLineEdit(PreferencesDialog);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));
        lineEditPort->setGeometry(QRect(160, 40, 181, 24));
        lineEditLogin = new QLineEdit(PreferencesDialog);
        lineEditLogin->setObjectName(QString::fromUtf8("lineEditLogin"));
        lineEditLogin->setGeometry(QRect(160, 70, 181, 24));
        pushButtonAccept = new QPushButton(PreferencesDialog);
        pushButtonAccept->setObjectName(QString::fromUtf8("pushButtonAccept"));
        pushButtonAccept->setGeometry(QRect(150, 160, 88, 27));
        pushButtonReject = new QPushButton(PreferencesDialog);
        pushButtonReject->setObjectName(QString::fromUtf8("pushButtonReject"));
        pushButtonReject->setGeometry(QRect(250, 160, 88, 27));
        lineEditPassword = new QLineEdit(PreferencesDialog);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(160, 100, 181, 24));
        lineEditPassword->setEchoMode(QLineEdit::Password);
        labelPort = new QLabel(PreferencesDialog);
        labelPort->setObjectName(QString::fromUtf8("labelPort"));
        labelPort->setGeometry(QRect(10, 40, 141, 18));
        checkBoxSavePassword = new QCheckBox(PreferencesDialog);
        checkBoxSavePassword->setObjectName(QString::fromUtf8("checkBoxSavePassword"));
        checkBoxSavePassword->setGeometry(QRect(10, 160, 131, 23));
        checkBoxAutoConnect = new QCheckBox(PreferencesDialog);
        checkBoxAutoConnect->setObjectName(QString::fromUtf8("checkBoxAutoConnect"));
        checkBoxAutoConnect->setGeometry(QRect(10, 130, 131, 23));
        checkBoxAutoConnect->setChecked(true);
        QWidget::setTabOrder(lineEditIp, lineEditPort);
        QWidget::setTabOrder(lineEditPort, lineEditLogin);
        QWidget::setTabOrder(lineEditLogin, lineEditPassword);
        QWidget::setTabOrder(lineEditPassword, checkBoxSavePassword);
        QWidget::setTabOrder(checkBoxSavePassword, pushButtonAccept);
        QWidget::setTabOrder(pushButtonAccept, pushButtonReject);

        retranslateUi(PreferencesDialog);
        QObject::connect(pushButtonAccept, SIGNAL(clicked()), PreferencesDialog, SLOT(accept()));
        QObject::connect(pushButtonReject, SIGNAL(clicked()), PreferencesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0, QApplication::UnicodeUTF8));
        labelLogin->setText(QApplication::translate("PreferencesDialog", "Login:", 0, QApplication::UnicodeUTF8));
        labelPassword->setText(QApplication::translate("PreferencesDialog", "Password:", 0, QApplication::UnicodeUTF8));
        labelIp->setText(QApplication::translate("PreferencesDialog", "Ip:", 0, QApplication::UnicodeUTF8));
        pushButtonAccept->setText(QApplication::translate("PreferencesDialog", "&Ok", 0, QApplication::UnicodeUTF8));
        pushButtonReject->setText(QApplication::translate("PreferencesDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        labelPort->setText(QApplication::translate("PreferencesDialog", "Port:", 0, QApplication::UnicodeUTF8));
        checkBoxSavePassword->setText(QApplication::translate("PreferencesDialog", "Save password", 0, QApplication::UnicodeUTF8));
        checkBoxAutoConnect->setText(QApplication::translate("PreferencesDialog", "Auto-connect", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(PreferencesDialog);
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_H
