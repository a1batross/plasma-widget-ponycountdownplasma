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
#include "filedownloader.h"
#include <QDebug>

fileDownloader::fileDownloader(QObject * parent): 
  QObject(parent)
{
  
}

fileDownloader::~fileDownloader()
{
    
}

void fileDownloader::getFile(const QString qUrl)
{
    getFile(QUrl(qUrl));
}

void fileDownloader::getFile(const QUrl qUrl)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
	  SLOT(fileDownloaded(QNetworkReply*))
    );

    QNetworkRequest request(qUrl);
    m_WebCtrl.get(request);
    
    qDebug() << "File downloading on " << request.url().toString();
}

void fileDownloader::fileDownloaded(QNetworkReply * pReply)
{
  m_gotJSON = pReply->readAll();
  
  //emit a signal
  pReply->deleteLater();
  emit downloaded();
}

QString fileDownloader::downloadedData() const
{
  return m_gotJSON;
}