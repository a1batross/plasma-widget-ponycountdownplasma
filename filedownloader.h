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

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

class fileDownloader : public QObject
{
  Q_OBJECT
public:
  explicit fileDownloader(QObject * parent = 0);
  
  virtual ~fileDownloader();
  
  void getFile(QUrl qUrl); // Set URL and start Downloading :)
  void getFile(QString qUrl);
  
  QString downloadedData() const;
  
signals:
  void downloaded();
  
private slots:
  void fileDownloaded(QNetworkReply* pReply);
  
private:
    QByteArray m_gotJSON;
    QNetworkAccessManager m_WebCtrl;
};

#endif // FILEDOWNLOADER_H
