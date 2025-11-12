#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Client
{
public:
    Client();

        Client(int,QString,QString,QString,QString,QString,QDate,QString,int,QString,int);

        int getID();
        QString getNom();
        QString getPrenom();
        QString getAdresse();
        QString getEmail();
        QString getNumeroTel();
        QDate getDateinsc();
        QString getCartecredit();
        int getSoldeCompte();
        QString getCompteActif();
        int getReductionAvantage();


        void setId(int);
        void setNom(QString);
        void setPrenom(QString );
        void setAdresse(QString );
        void setEmail(QString );

        void setNumeroTel(QString );
        void setDateinsc(QDate );
        void setCarteCredit(QString);
        void setSoldeCopmte(int);
        void setCompteActif(QString);
        void setReductionAvantage(int);

        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(int);



private:

       int id;
       int soldecompte,reductionavantage;
       QString nom,prenom,adresse,email,numtel,compteactif,cartecredit;
       QDate dateinsc;

};

#endif // CLIENT_H
