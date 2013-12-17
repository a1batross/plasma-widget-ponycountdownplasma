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
  
  void setUrl(QUrl qUrl); // Set URL and start Downloading :)
  
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
