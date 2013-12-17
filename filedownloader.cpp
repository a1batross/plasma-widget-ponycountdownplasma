#include "filedownloader.h"
#include <QDebug>

fileDownloader::fileDownloader(QObject * parent): 
  QObject(parent)
{
  
}

fileDownloader::~fileDownloader()
{
    
}


void fileDownloader::setUrl(const QUrl qUrl)
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