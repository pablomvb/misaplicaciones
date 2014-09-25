#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QUrl>

class QDialogButtonBox;
class QFile;
class QLabel;
class QLineEdit;
class QProgressDialog;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;


class HttpWindow : public QDialog
{
    Q_OBJECT

public:
    HttpWindow(QWidget *parent = 0);

    void startRequest(QUrl url);

private slots:
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
    void enableDownloadButton();
   // void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
#ifndef QT_NO_SSL
    //void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif

private:
    QLabel *statusLabel;
    QLabel *urlLabel;
    QLineEdit *urlLineEdit;
    QProgressDialog *progressDialog;
    QPushButton *downloadButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;
    HttpWindow *ui;

};

#endif
