#ifndef COMMANDES_H
#define COMMANDES_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Commandes
{
public:
        Commandes();
        Commandes(int,QString,QString,int,QDate,int);


        int getID_COMMANDE();
        QString getREF_COMMANDE();
        QString getSTATUT();
        int getMONTANT_ESTIME();
        QDate getDATE_LIVRAISON_SOUHAITEE();
        int getID_CLIENT();


        void setID_COMMANDE(int);
        void setREF_COMMANDE(QString);
        void setSTATUT(QString );
        void setMONTANT_ESTIME(int );
        void setDATE_LIVRAISON_SOUHAITEE(QDate );
        void setID_CLIENT(int);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(int);
      //  QSqlQueryModel *rechercher(QString);
       // QSqlQueryModel *trier(QString);
        bool tri(QString);
        bool idDisponible(int);
        bool rech(QString);


private:

       int ID_COMMANDE,ID_CLIENT,MONTANT_ESTIME;
       QString REF_COMMANDE,STATUT;
       QDate DATE_LIVRAISON_SOUHAITEE;

};

#endif // COMMANDES_H
