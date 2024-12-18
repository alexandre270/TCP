#include "client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{
    qDebug() << QString::fromUtf8("Instancie un objet QTcpSocket");
    tcpSocket = new QTcpSocket(this); // Création de la socket
    qDebug() << QString::fromUtf8("État initial de la socket :") << tcpSocket->state();

    // Connexion des signaux aux slots
    connect(tcpSocket, &QTcpSocket::connected, this, &Client::estConnectee);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::estDeconnectee);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::recevoir);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &Client::gestionErreur);

    // Connexion au serveur
    tcpSocket->connectToHost(QHostAddress::LocalHost, PORT_SERVEUR);
}

Client::~Client()
{
    qDebug() << QString::fromUtf8("Fermeture de la socket...");
    tcpSocket->close();
}

void Client::demarrer()
{
    qDebug() << QString::fromUtf8("Connexion au serveur...");
    tcpSocket->connectToHost(QHostAddress::LocalHost, PORT_SERVEUR);
    qDebug() << QString::fromUtf8("État de la socket :") << tcpSocket->state();
}

void Client::estConnectee()
{
    qDebug() << QString::fromUtf8("Connecté au serveur !");
    qDebug() << "Adresse du serveur :" << tcpSocket->peerAddress().toString();
    qDebug() << "Port du serveur :" << tcpSocket->peerPort();

    envoyer("Hello"); // Envoi du premier message
}

void Client::estDeconnectee()
{
    qDebug() << QString::fromUtf8("Déconnecté du serveur.");
}

void Client::gestionErreur(QAbstractSocket::SocketError erreur)
{
    qDebug() << QString::fromUtf8("Erreur de connexion (code) :") << erreur;
    qDebug() << QString::fromUtf8("Erreur de connexion (description) :") << tcpSocket->errorString();
}

void Client::recevoir()
{
    QByteArray donnees = tcpSocket->readAll();
    qDebug() << QString::fromUtf8("Message reçu :") << QString::fromUtf8(donnees);
}

void Client::envoyer(QByteArray message)
{
    qint64 ecrits = tcpSocket->write(message);
    if (ecrits == -1) {
        qDebug() << QString::fromUtf8("Erreur lors de l'envoi du message !");
    } else {
        qDebug() << QString::fromUtf8("Message envoyé :") << message;
    }
}
