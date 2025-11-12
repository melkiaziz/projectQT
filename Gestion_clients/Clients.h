#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Clients
{
public:
Clients();
        Clients(int,QString,QString,QString,QString,QString,QString,QString,QString);

        int getID_CLIENT();
        QString getNOM();
        QString getPRENOM();
        QString getEMAIL();

        QString getTEL();
        QString getTYPE();
        QString getADRESSE();

        QString getVILLE();
        QString getCODE_POSTAL();


        void setID_CLIENT(int);
        void setNOM(QString);
        void setPRENOM(QString );
        void setEMAIL(QString );
        void setTEL(QString );
        void setTYPE(QString);
        void setADRESSE(QString);
        void setVILLE(QString);
        void setCODE_POSTAL(QString);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(int);
        bool idDisponible(int);


       // QSqlQueryModel *rechercher(QString);
//        QSqlQueryModel *trier(QString);
        bool verif_email(QString email);
        bool tri(QString);
        bool rech(QString);



private:

       int ID_CLIENT;
       QString PRENOM,NOM,EMAIL,TEL,TYPE,ADRESSE,VILLE,CODE_POSTAL;


};


#endif // CLIENTS_H
