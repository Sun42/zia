/// \file

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include "ui_Preferences.h"

/*! \class Preferences
 * \brief Boite de dialogue
 *
 * Permet de configurer l'hote, le port, l'identifiant ainsi que le mot de passe.
 */
class	Preferences : public QDialog, public Ui_PreferencesDialog
{
  Q_OBJECT

	public:
  Preferences(QWidget* parent = 0);
  ~Preferences(void);

  void	readSettings(void);
  void	writeSettings(void);
  void	update(void);

  private slots:
  void	save(void);

 private:
  QString	_ip;
  QString	_port;
  QString	_login;
  QString	_password;
  bool		_savePassword;
};

#endif // PREFERENCES_H
