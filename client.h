#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#define PORT_SERVEUR 8000 // Port du serveur distant

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    void demarrer();

private:
    QTcpSocket *tcpSocket; // La socket TCP

signals:

public slots:
    void estConnectee();
    void estDeconnectee();
    void gestionErreur(QAbstractSocket::SocketError erreur);
    void recevoir();
    void envoyer(QByteArray message);
};

#endif // CLIENT_H
