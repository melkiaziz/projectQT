#include "Commandes.h"

#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include<QDate>
#include<QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>


Commandes::Commandes()
{

}

Commandes::Commandes(int ID_COMMANDE,QString REF_COMMANDE,QString STATUT,int MONTANT_ESTIME,QDate DATE_LIVRAISON_SOUHAITEE,int ID_CLIENT)
{this->ID_COMMANDE=ID_COMMANDE;
    this->REF_COMMANDE = REF_COMMANDE;
    this->STATUT = STATUT;
    this->MONTANT_ESTIME=MONTANT_ESTIME;
    this->DATE_LIVRAISON_SOUHAITEE = DATE_LIVRAISON_SOUHAITEE;
    this->ID_CLIENT = ID_CLIENT;

}

  int Commandes::getID_COMMANDE(){return ID_COMMANDE;}
  QString Commandes::getREF_COMMANDE(){return REF_COMMANDE;}
  QString Commandes::getSTATUT(){return STATUT;}
  int Commandes::getMONTANT_ESTIME(){return MONTANT_ESTIME;}
  QDate Commandes::getDATE_LIVRAISON_SOUHAITEE(){return DATE_LIVRAISON_SOUHAITEE;}
  int Commandes::getID_CLIENT(){return ID_CLIENT;}

  void Commandes::setID_COMMANDE(int ID_COMMANDE){this->ID_COMMANDE=ID_COMMANDE;}
  void Commandes::setREF_COMMANDE(QString REF_COMMANDE){this->REF_COMMANDE=REF_COMMANDE;}
  void Commandes::setSTATUT(QString STATUT){this->STATUT=STATUT;}
  void Commandes::setMONTANT_ESTIME(int MONTANT_ESTIME){this->MONTANT_ESTIME=MONTANT_ESTIME;}
  void Commandes::setDATE_LIVRAISON_SOUHAITEE(QDate DATE_LIVRAISON_SOUHAITEE ){this->DATE_LIVRAISON_SOUHAITEE=DATE_LIVRAISON_SOUHAITEE;}
  void Commandes::setID_CLIENT(int ID_CLIENT){this->ID_CLIENT=ID_CLIENT;}



bool Commandes::ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO Commandes (ID_COMMANDE,REF_COMMANDE,STATUT,MONTANT_ESTIME,DATE_LIVRAISON_SOUHAITEE,ID_CLIENT)"
                  "values(:ID_COMMANDE,:REF_COMMANDE,:STATUT,:MONTANT_ESTIME,:DATE_LIVRAISON_SOUHAITEE,:ID_CLIENT)");
    query.bindValue(":ID_COMMANDE",ID_COMMANDE);
        query.bindValue(":REF_COMMANDE",REF_COMMANDE);
         query.bindValue(":STATUT",STATUT);
         query.bindValue(":MONTANT_ESTIME",MONTANT_ESTIME);
         query.bindValue(":DATE_LIVRAISON_SOUHAITEE",DATE_LIVRAISON_SOUHAITEE);
         query.bindValue(":ID_CLIENT",ID_CLIENT);


          return query.exec();

   };



QSqlQueryModel * Commandes::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Commandes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COMMANDE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("REF_COMMANDE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("STATUT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MONTANT_ESTIME"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE_LIVRAISON_SOUHAITEE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_CLIENT"));

    return model;
}
bool Commandes::supprimer(int ID_COMMANDE)
{
    QSqlQuery query;
         query.prepare("Delete from Commandes where ID_COMMANDE=:ID_COMMANDE");
         query.bindValue(":ID_COMMANDE",ID_COMMANDE);
         return query.exec();
}

bool Commandes::modifier(int ID_COMMANDE)
{
QSqlQuery query;


        query.prepare("UPDATE Commandes SET REF_COMMANDE=:REF_COMMANDE,STATUT=:STATUT,MONTANT_ESTIME=:MONTANT_ESTIME,DATE_LIVRAISON_SOUHAITEE=:DATE_LIVRAISON_SOUHAITEE,ID_CLIENT=:ID_CLIENT where ID_COMMANDE=:ID_COMMANDE");
        query.bindValue(":ID_COMMANDE", ID_COMMANDE);
        query.bindValue(":REF_COMMANDE",REF_COMMANDE);
         query.bindValue(":STATUT",STATUT);
         query.bindValue(":MONTANT_ESTIME",MONTANT_ESTIME);
         query.bindValue(":DATE_LIVRAISON_SOUHAITEE",DATE_LIVRAISON_SOUHAITEE);
          query.bindValue(":ID_CLIENT",ID_CLIENT);
        return    query.exec();
}
bool Commandes::checkIfIdExists(int ID_COMMANDE)
{
    QSqlQuery query;
    query.prepare("SELECT ID_COMMANDE FROM Commandes WHERE ID_COMMANDE =:ID_COMMANDE");
    query.bindValue(":ID_COMMANDE", ID_COMMANDE);

    if (query.exec() && query.next()) {
        // The ID exists in the database
        return true;
    } else {
        // The ID does not exist in the database
        return false;
    }
}

bool Commandes::tri(QString tr){

    QSqlQuery query;
        query.prepare("SELECT * FROM Commandes "+tr);
        return query.exec() ;

}
bool Commandes::idDisponible(int id_commande) {
    QSqlQuery query;
    query.prepare("SELECT id_commande FROM commandes WHERE id_commande = :id_commande");
    query.bindValue(":id_commande", id_commande);

    if (query.exec() && query.next()) {

        return true;
    } else {

        return false;
    }
}
bool Commandes::rech(QString rch) {
    QSqlQuery query;
    query.prepare("SELECT * FROM commandes WHERE " + rch);
    return query.exec();
}
