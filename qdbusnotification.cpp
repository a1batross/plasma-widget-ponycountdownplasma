/*
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 *
 *  Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 *
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include "qdbusnotification.h"
#include <KIconLoader>
#include <QVariant>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusInterface>

void showNotification(const QString appname, 
		      const QString title, 
		      const QString message, 
		      const QString icon)
{
  KIconLoader *sysicon = new KIconLoader("apps");
  
  QDBusInterface notify("org.freedesktop.Notifications", "/org/freedesktop/Notifications",
			"org.freedesktop.Notifications");
  
  QVariantList args;
  args << appname;
  args << uint(0);
  args << sysicon->iconPath(icon, 0, false); //return a path to the icon 48x48. If not found, NOT return a null string.
  args << title;
  args << message;
  args << QStringList();
  args << QVariantMap();
  args << (int)5000;
  
  QDBusMessage reply = notify.callWithArgumentList(QDBus::AutoDetect, "Notify", args);
  qDebug() << "DBus Message:" << reply.errorMessage();
}
