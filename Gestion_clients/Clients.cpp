#include "Clients.h"

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


// Clients(int,QString,QString,QString,QString,QString,QString,QString,QString);
// int ID_CLIENT;
// QString PRENOM,NOM,EMAIL,TEL,TYPE,ADRESSE,VILLE,CODE_POSTAL;
 //   ID_CLIENT,PRENOM,NOM,EMAIL,TEL,TYPE,ADRESSE,VILLE,CODE_POSTAL
Clients::Clients()
{

}

Clients::Clients(int ID_CLIENT,QString PRENOM,QString NOM,QString EMAIL,QString TEL,QString TYPE,QString ADRESSE,QString VILLE,QString CODE_POSTAL)
{this->ID_CLIENT=ID_CLIENT;
    this->PRENOM = PRENOM;
    this->NOM = NOM;
    this->EMAIL=EMAIL;
    this->TEL = TEL;
    this->TYPE = TYPE;
    this->ADRESSE = ADRESSE;
    this->VILLE = VILLE;
    this->CODE_POSTAL = CODE_POSTAL;

}

  int Clients::getID_CLIENT(){return ID_CLIENT;}
  QString Clients::getPRENOM(){return PRENOM;}
  QString Clients::getNOM(){return NOM;}
  QString Clients::getEMAIL(){return EMAIL;}
  QString Clients::getTEL(){return TEL;}
  QString Clients::getTYPE(){return TYPE;}
  QString Clients::getADRESSE(){return ADRESSE;}
  QString Clients::getVILLE(){return VILLE;}
  QString Clients::getCODE_POSTAL(){return CODE_POSTAL;}

  void Clients::setID_CLIENT(int ID_CLIENT){this->ID_CLIENT=ID_CLIENT;}
  void Clients::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
  void Clients::setNOM(QString NOM){this->NOM=NOM;}
  void Clients::setEMAIL(QString EMAIL){this->EMAIL=EMAIL;}
  void Clients::setTEL(QString TEL ){this->TEL=TEL;}
  void Clients::setTYPE(QString TYPE){this->TYPE=TYPE;}
  void Clients::setADRESSE(QString ADRESSE){this->ADRESSE=ADRESSE;}
  void Clients::setVILLE(QString VILLE){this->VILLE=VILLE;}
  void Clients::setCODE_POSTAL(QString CODE_POSTAL){this->CODE_POSTAL=CODE_POSTAL;}



bool Clients::ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO Clients (ID_CLIENT,PRENOM,NOM,EMAIL,TEL,TYPE,ADRESSE,VILLE,CODE_POSTAL)"
                  "values(:ID_CLIENT,:PRENOM,:NOM,:EMAIL,:TEL,:TYPE,:ADRESSE,:VILLE,:CODE_POSTAL)");
    query.bindValue(":ID_CLIENT",ID_CLIENT);
        query.bindValue(":PRENOM",PRENOM);
         query.bindValue(":NOM",NOM);
         query.bindValue(":EMAIL",EMAIL);
         query.bindValue(":TEL",TEL);
         query.bindValue(":TYPE",TYPE);
         query.bindValue(":ADRESSE",ADRESSE);
         query.bindValue(":VILLE",VILLE);
         query.bindValue(":CODE_POSTAL",CODE_POSTAL);
          return query.exec();

   };



QSqlQueryModel * Clients::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Clients");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("VILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("CODE_POSTAL"));

    return model;
}
bool Clients::supprimer(int ID_CLIENT)
{
    QSqlQuery query;
         query.prepare("Delete from Clients where ID_CLIENT=:ID_CLIENT");
         query.bindValue(":ID_CLIENT",ID_CLIENT);
         return query.exec();
}

bool Clients::modifier(int ID_CLIENT)
{
QSqlQuery query;


        query.prepare("UPDATE Clients SET PRENOM=:PRENOM,NOM=:NOM,EMAIL=:EMAIL,TEL=:TEL,TYPE=:TYPE,ADRESSE=:ADRESSE,VILLE=:VILLE,CODE_POSTAL=:CODE_POSTAL where ID_CLIENT=:ID_CLIENT");
        query.bindValue(":ID_CLIENT",ID_CLIENT);
            query.bindValue(":PRENOM",PRENOM);
             query.bindValue(":NOM",NOM);
             query.bindValue(":EMAIL",EMAIL);
             query.bindValue(":TEL",TEL);
             query.bindValue(":TYPE",TYPE);
             query.bindValue(":ADRESSE",ADRESSE);
             query.bindValue(":VILLE",VILLE);
             query.bindValue(":CODE_POSTAL",CODE_POSTAL);


        return    query.exec();
}

bool Clients::checkIfIdExists(int ID_CLIENT)
{
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT FROM Clients WHERE ID_CLIENT = :ID_CLIENT");
    query.bindValue(":ID_CLIENT", ID_CLIENT);

    if (query.exec() && query.next()) {
        // The ID exists in the database
        return true;
    } else {
        // The ID does not exist in the database
        return false;
    }
}
/*

QSqlQueryModel* Clients::rechercher(QString a)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Clients WHERE ID_CLIENT LIKE '" + a + "%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("VILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("CODE_POSTAL"));
    return model;
}*/
/*
QSqlQueryModel *Clients::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;

    if(x=="ID (DES)")
        model->setQuery("select*  from Clients order by ID_CLIENT desc");
    else if(x=="Nom (A->Z)")
        model->setQuery("select*  from Clients order by NOMFORMATEUR");  //tri par defaut asc
    else if (x=="Solde (Asc)")
        model->setQuery("select*  from Clients order by EXPERIENCE");
    else if (x=="Default")
            model->setQuery("select * from Clients");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("VILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("CODE_POSTAL"));

        return model;

}
*/
bool Clients::verif_email(QString email)
 {

     if (!email.contains("@")) {
         return false;
     }

     int index = email.indexOf("@");
     if (email.indexOf(".", index) == -1) {
         return false;
     }
     if (email.startsWith(".") || email.startsWith("@") || email.endsWith(".") || email.endsWith("@")) {
         return false;
     }

     QRegExp regExp("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
     return regExp.exactMatch(email);
 }

bool Clients::tri(QString tr){

    QSqlQuery query;
        query.prepare("SELECT * FROM Clients "+tr);
        return query.exec() ;

}
bool Clients::idDisponible(int id_client) {
    QSqlQuery query;
    query.prepare("SELECT id_client FROM clients WHERE id_client = :id_client");
    query.bindValue(":id_client", id_client);

    if (query.exec() && query.next()) {

        return true;
    } else {

        return false;
    }
}
bool Clients::rech(QString rch) {
    QSqlQuery query;
    query.prepare("SELECT * FROM clients WHERE " + rch);
    return query.exec();
}
