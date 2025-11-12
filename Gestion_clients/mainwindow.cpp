#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QDebug>
#include <QSqlError>
#include <QDebug>

#include "QrCode.hpp"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPen>
#include <QPainter>
#include <QTextDocument>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
using namespace QtCharts;

using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_NOM->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
    ui->le_PRENOM->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
    ui->le_VILLE->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
    ui->le_NOM->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
    ui->le_NOM->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));
    ui->le_NOM->setValidator(new QRegExpValidator(QRegExp("[A-Z,a-z]*")));


    ui->le_ID_CLIENT->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
    ui->le_ID_COMMANDE->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
    ui->le_TEL->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
    ui->le_CODEPOSTAL->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
    ui->le_MONTANTESTIME->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
    ui->le_idclientFK->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouterCLIENT_clicked()
{


        // Réinitialisez les étiquettes d'erreur à vide
        ui->lblErreurle_ID_CLIENT->setText("");
        ui->lblErreurle_PRENOM->setText("");

        ui->lblErreurNOM->setText("");
        ui->lblErreurle_EMAIL->setText("");

        ui->lblErreurle_TEL->setText("");
        ui->lblErreurTYPE->setText("");
        ui->lblErreurADRESSE->setText("");
        ui->lblErreurle_VILLE->setText("");
        ui->lblErreurle_CODEPOSTAL->setText("");

        // Récupérez les valeurs d'entrée

        QString str_id = ui->le_ID_CLIENT->text();
        int ID_CLIENT=str_id.toInt();
        QString NOM = ui->le_NOM->text();
        QString PRENOM = ui->le_PRENOM->text();
        QString EMAIL = ui->le_EMAIL->text();
        QString TEL = ui->le_TEL->text();
        QString TYPE = ui->comboBox_TYPE->currentText();
        QString ADRESSE = ui->le_ADRESSE->text();
        QString VILLE = ui->le_VILLE->text();
        QString CODEPOSTAL = ui->le_CODEPOSTAL->text();





        // Validez les champs d'entrée
        bool isValid = true;

        if (str_id.isEmpty()) {
            ui->lblErreurle_ID_CLIENT->setText("<font color='red'>ID_CLIENT ne peut pas être vide!!!!</font>");
            isValid = false;
        }

        // Validation pour le titre (exemplaire, assurez-vous qu'il n'est pas vide)
        if (PRENOM.isEmpty()) {
            ui->lblErreurle_PRENOM->setText("<font color='red'>PRENOM ne peut pas être vide!!!</font>");
            isValid = false;
        }

        if (NOM.isEmpty()) {
            ui->lblErreurNOM->setText("<font color='red'>NOM ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (EMAIL.isEmpty()) {
            ui->lblErreurle_EMAIL->setText("<font color='red'>EMAIL ne peut pas être vide!!!</font>");
            isValid = false;
        }

                // 🔹 Vérif format e-mail ici

                if (!C.verif_email(EMAIL)) {
                    ui->lblErreurle_EMAIL->setText("<font color='red'>Format e-mail invalide !!!</font>");
                    isValid = false;
                }
        if (TEL.isEmpty()) {
            ui->lblErreurle_TEL->setText("<font color='red'>TEL ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (TYPE.isEmpty()) {
            ui->lblErreurTYPE->setText("<font color='red'>TYPE CLIENT ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (ADRESSE.isEmpty()) {
            ui->lblErreurADRESSE->setText("<font color='red'>ADRESSE ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (VILLE.isEmpty()) {
            ui->lblErreurle_VILLE->setText("<font color='red'>VILLE ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (CODEPOSTAL.isEmpty()) {
            ui->lblErreurle_CODEPOSTAL->setText("<font color='red'>CODE POSTAL ne peut pas être vide!!!</font>");
            isValid = false;
        }


        // Ajouter une vérification de l'existence de l'ID dans la base de données
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT ID_CLIENT FROM CLIENTS WHERE ID_CLIENT = :ID_CLIENT");
        checkQuery.bindValue(":ID_CLIENT", ID_CLIENT);
        if (checkQuery.exec() && checkQuery.next()) {
            ui->lblErreurle_ID_CLIENT->setText("<font color='red'>ID CLIENT existe déjà!!!!</font>");
            isValid = false;
        }

        // Continuez avec les autres validations d'entrée...

        if (isValid) {
            // Si l'entrée est valide et que l'ID n'existe pas, procédez à l'ajout de l'activité
            Clients C(ID_CLIENT,PRENOM,NOM,EMAIL,TEL,TYPE,ADRESSE,VILLE,CODEPOSTAL);

            QSqlQuery query;
            bool test = C.ajouter();
            if (test) {
                ui->tab_CLIENT->setModel(C.afficher()); // Rafraîchir la vue

                QMessageBox::information(nullptr, QObject::tr("Ajout CLIENT"),
                    QObject::tr("Client ajoutée avec succès.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);





            } else {
                QMessageBox::critical(nullptr, QObject::tr("Ajout CLIENT"),
                    QObject::tr("Erreur lors de l'ajout de Client.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        } else {
            // Gérez l'erreur d'entrée invalide ou d'ID existant
        }
    }



void MainWindow::on_pb_modifierCLIENT_clicked()
    {



    QString str_id = ui->le_ID_CLIENT->text();
    int ID_CLIENT=str_id.toInt();
    QString NOM = ui->le_NOM->text();
    QString PRENOM = ui->le_PRENOM->text();
    QString EMAIL = ui->le_EMAIL->text();
    QString TEL = ui->le_TEL->text();
    QString TYPE = ui->comboBox_TYPE->currentText();
    QString ADRESSE = ui->le_ADRESSE->text();
    QString VILLE = ui->le_VILLE->text();
    QString CODEPOSTAL = ui->le_CODEPOSTAL->text();

      // Vérification si l'ID existe
      QSqlQuery checkQuery;
      checkQuery.prepare("SELECT * FROM clients WHERE ID_CLIENT = :ID_CLIENT");
      checkQuery.bindValue(":ID_CLIENT", ID_CLIENT);

      if (!checkQuery.exec())
      {
          // Erreur lors de l'exécution de la requête
          qDebug() << "Erreur lors de la vérification de l'ID CLIENT n'existe pas pour le modifier :" << checkQuery.lastError().text();
          return;
      }

      if (!checkQuery.next())
      {
          // L'ID n'existe pas, affichez un message d'erreur
          QMessageBox::critical(nullptr, QObject::tr("Modifier CLIENT"),
                                QObject::tr("L'ID CLIENT n'existe pas dans la base de données.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
          return;
      }

      // L'ID existe, vous pouvez maintenant effectuer la modification
      Clients C(ID_CLIENT,PRENOM,NOM,EMAIL,TEL,TYPE,ADRESSE,VILLE,CODEPOSTAL);

      QSqlQuery query;

      bool test = C.modifier(ID_CLIENT);
      if (test)
      {
          ui->tab_CLIENT->setModel(C.afficher()); // Rafraîchir la vue

          QMessageBox::information(nullptr, QObject::tr("Modifier CLIENT"),
                                   QObject::tr("Client Modifiée.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Modifier CLIENT"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
      }
    }




void MainWindow::on_pb_afficherCLIENT_clicked()
{
    ui->tab_CLIENT->setModel(C.afficher());

}

void MainWindow::on_pb_supprimerCLIENT_clicked()
{

        int ID = ui->lineEdit_suppCLIENT->text().toInt();

        if (C.checkIfIdExists(ID)) {
            bool test =C.supprimer(ID);
            ui->tab_CLIENT->setModel(C.afficher());
            if (test) {
                QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                    QObject::tr("Suppression effectuée avec succès.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);



            } else {
                QMessageBox::critical(nullptr, QObject::tr("Erreur de suppression"),
                    QObject::tr("Erreur lors de la suppression de client.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("ID Client introuvable"),
                QObject::tr("ID Client que vous avez saisi n'existe pas.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    }












//2EME GESTION COMMANDE


void MainWindow::on_ajoutercommande_clicked()
{
    // Réinitialisez les étiquettes d'erreur à vide
    ui->lblErreurle_ID_COMMANDE->setText("");
    ui->lblErreurIdle_REFERENCE->setText("");

    ui->lblErreurle_STATUT->setText("");
    ui->lblErreurle_MONTANTESTIME->setText("");

    ui->lblErreurle_idclientfk->setText("");


    // Récupérez les valeurs d'entrée

    QString str_id = ui->le_ID_COMMANDE->text();
    int ID_COMMANDE=str_id.toInt();
    QString reference = ui->le_REFERENCE->text();
    QString statut = ui->comboBox_STATUT->currentText();

    QString MONTANTESTIME_str = ui->le_MONTANTESTIME->text();
    int MONTANTESTIME =MONTANTESTIME_str.toInt();

    QDate DATELIVRAISON = ui->le_DATELIVRAISON->date();

    QString id_client_str =ui->le_idclientFK->text();
    int id_client=id_client_str.toInt();


    // Validez les champs d'entrée
    bool isValid = true;

    if (str_id.isEmpty()) {
        ui->lblErreurle_ID_COMMANDE->setText("<font color='red'>ID COMMANDE ne peut pas être vide!!!!</font>");
        isValid = false;
    }

    // Validation pour le titre (exemplaire, assurez-vous qu'il n'est pas vide)
    if (reference.isEmpty()) {
        ui->lblErreurIdle_REFERENCE->setText("<font color='red'>REFERENCE ne peut pas être vide!!!</font>");
        isValid = false;
    }

    if (statut.isEmpty()) {
        ui->lblErreurle_STATUT->setText("<font color='red'>STATUT ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (MONTANTESTIME_str.isEmpty()) {
        ui->lblErreurle_MONTANTESTIME->setText("<font color='red'>MONTANTESTIME ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (id_client_str.isEmpty()) {
        ui->lblErreurle_idclientfk->setText("<font color='red'>ID CLIENT ne peut pas être vide!!!</font>");
        isValid = false;
    }



    // Ajouter une vérification de l'existence de l'ID dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID_COMMANDE FROM COMMANDEs WHERE ID_COMMANDE = :ID_COMMANDE");
    checkQuery.bindValue(":ID_COMMANDE", ID_COMMANDE);
    if (checkQuery.exec() && checkQuery.next()) {
        ui->lblErreurle_ID_COMMANDE->setText("<font color='red'>ID COMMANDE existe déjà!!!!</font>");
        isValid = false;
    }

    // Continuez avec les autres validations d'entrée...

    if (isValid) {
        // Si l'entrée est valide et que l'ID n'existe pas, procédez à l'ajout de l'activité
        Commandes Co(ID_COMMANDE,reference,statut,MONTANTESTIME,DATELIVRAISON,id_client);

        QSqlQuery query;
        bool test = Co.ajouter();
        if (test) {
            ui->tab_commandes->setModel(Co.afficher()); // Rafraîchir la vue

            QMessageBox::information(nullptr, QObject::tr("Ajout Commande"),
                QObject::tr("Commande ajoutée avec succès.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);


            //historique
            QString idStr = QString::number(ID_COMMANDE);
              ajouterHistorique("✅ Commande ajoutée avec l'ID : " + idStr);

              QMessageBox::information(this, "Ajout Commande",
                                       "Commande ajoutée avec succès !");


        } else {
            QMessageBox::critical(nullptr, QObject::tr("Ajout Commande"),
                QObject::tr("Erreur lors de l'ajout de Commande.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    } else {
        // Gérez l'erreur d'entrée invalide ou d'ID existant
    }
}


void MainWindow::on_modifiercommande_clicked()
{
// Récupérez les valeurs d'entrée

    QString str_id = ui->le_ID_COMMANDE->text();
    int ID_COMMANDE=str_id.toInt();
    QString reference = ui->le_REFERENCE->text();
    QString statut = ui->comboBox_STATUT->currentText();

    QString MONTANTESTIME_str = ui->le_MONTANTESTIME->text();
    int MONTANTESTIME =MONTANTESTIME_str.toInt();

    QDate DATELIVRAISON = ui->le_DATELIVRAISON->date();

    QString id_client_str =ui->le_idclientFK->text();
    int id_client=id_client_str.toInt();


  // Vérification si l'ID existe
  QSqlQuery checkQuery;
  checkQuery.prepare("SELECT * FROM COMMANDEs WHERE ID_COMMANDE = :ID_COMMANDE");
  checkQuery.bindValue(":ID_COMMANDE", ID_COMMANDE);


  if (!checkQuery.exec())
  {
      // Erreur lors de l'exécution de la requête
      qDebug() << "Erreur lors de la vérification de l'ID COMMANDE n'existe pas pour le modifier :" << checkQuery.lastError().text();
      return;
  }

  if (!checkQuery.next())
  {
      // L'ID n'existe pas, affichez un message d'erreur
      QMessageBox::critical(nullptr, QObject::tr("Modifier COMMANDE"),
                            QObject::tr("L'ID COMMANDE n'existe pas dans la base de données.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
      return;
  }

  // L'ID existe, vous pouvez maintenant effectuer la modification
  Commandes Co(ID_COMMANDE,reference,statut,MONTANTESTIME,DATELIVRAISON,id_client);

  QSqlQuery query;

  bool test = Co.modifier(ID_COMMANDE);
  if (test)
  {
      ui->tab_commandes->setModel(Co.afficher()); // Rafraîchir la vue

      QMessageBox::information(nullptr, QObject::tr("Modifier Commande"),
                               QObject::tr("Commande Modifiée.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

      //historique
      QString idStr = QString::number(ID_COMMANDE);
      ajouterHistorique("✏️ Commande modifiée avec l'ID : " + idStr);

      QMessageBox::information(this, "Modifier Commande",
                               "Commande modifiée avec succès !");
  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("Modifier Commande"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
  }
}




void MainWindow::on_affichercommande_clicked()
{
    ui->tab_commandes->setModel(Co.afficher()); // Rafraîchir la vue

}

void MainWindow::on_supprimercommande_clicked()
{


            int ID = ui->lineEdit_supp_commande2->text().toInt();

            if (Co.checkIfIdExists(ID)) {
                bool test =Co.supprimer(ID);
                ui->tab_commandes->setModel(Co.afficher());
                if (test) {
                    QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                        QObject::tr("Suppression effectuée avec succès.\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                    //historique
                    QString idStr = QString::number(ID);
                        ajouterHistorique("❌ Commande supprimée avec l'ID : " + idStr);

                        QMessageBox::information(this, "Suppression réussie",
                                                 "Commande supprimée avec succès !");

                } else {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur de suppression"),
                        QObject::tr("Erreur lors de la suppression de client.\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
                }
            } else {
                QMessageBox::critical(nullptr, QObject::tr("ID Commande introuvable"),
                    QObject::tr("ID Commande que vous avez saisi n'existe pas.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        }









void MainWindow::on_qrcodegen_CLIENT_clicked()
{
    QString value = ui->qrcode->text();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM CLIENTS WHERE ID_CLIENT = :ID_CLIENT");
    qry.bindValue(":ID_CLIENT", value);
    qry.exec();

    if (qry.next()) {
        // ID exists in the database


        QString ID_CLIENT = qry.value(0).toString();
        QString PRENOM = qry.value(1).toString();
        QString NOM = qry.value(2).toString();
        QString EMAIL    = qry.value(3).toString();
        QString TEL = qry.value(4).toString();
        QString TYPE = qry.value(5).toString();
        QString ADRESSE = qry.value(6).toString();
        QString VILLE = qry.value(7).toString();
        QString CODEPOSTAL = qry.value(8).toString();


        QString text = "ID Client :" + ID_CLIENT + "\n" + "PRENOM :" + PRENOM + "\n" + "NOM :" + NOM + "\n" +
                       "EMAIL :" + EMAIL + "\n" + " TEL :" + TEL+ "\n" + "TYPE :" + TYPE+ "\n" + " ADRESSE :" + ADRESSE + " VILLE :" + VILLE+ " CODEPOSTAL :" + CODEPOSTAL
             ;

        // Create the QR Code object
        QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

        qint32 sz = qr.getSize();
        QImage im(sz, sz, QImage::Format_RGB32);
        QRgb black = qRgb(191, 112, 105);
        QRgb white = qRgb(255, 255, 255);

        for (int y = 0; y < sz; y++) {
            for (int x = 0; x < sz; x++) {
                im.setPixel(x, y, qr.getModule(x, y) ? black : white);
            }
        }

        ui->qrcodecommande_2->setPixmap(QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));
    } else {
        // ID does not exist in the database
        QMessageBox::critical(nullptr, QObject::tr("ID introuvable"),
            QObject::tr("ID Client que vous avez saisi n'existe pas.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_GOTOGESTIONCLIENT_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_GOTOGESTIONCOMMANDE_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}









void MainWindow::on_statistique_commande_clicked()
{
    QSqlQueryModel *mod = new QSqlQueryModel();
    mod->setQuery("SELECT * FROM COMMANDES WHERE STATUT='En cours'");
    float nbEnCours = mod->rowCount();

    mod->setQuery("SELECT * FROM COMMANDES WHERE STATUT='Livree'");
    float nbLivree = mod->rowCount();

    mod->setQuery("SELECT * FROM COMMANDES WHERE STATUT='Annulee'");
    float nbAnnulee = mod->rowCount();

    float total = nbEnCours + nbLivree + nbAnnulee;
    if (total == 0) {
        QMessageBox::information(this, "Statistiques", "Aucune commande trouvée dans la base !");
        return;
    }

    QString a = QString("En cours (%1%)").arg(QString::number((nbEnCours * 100) / total, 'f', 2));
    QString b = QString("Livrées (%1%)").arg(QString::number((nbLivree * 100) / total, 'f', 2));
    QString c = QString("Annulées (%1%)").arg(QString::number((nbAnnulee * 100) / total, 'f', 2));

    QPieSeries *series = new QPieSeries();
    series->append(a, nbEnCours);
    series->append(b, nbLivree);
    series->append(c, nbAnnulee);

    for (int i = 0; i < series->slices().size(); ++i) {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des commandes par statut (" + QString::number((int)total) + " commandes)");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->setTitleBrush(Qt::darkGreen);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(900, 500);
    chartView->show();
}
void MainWindow::on_statistique_client_clicked()
{
    QSqlQueryModel *mod = new QSqlQueryModel();
    mod->setQuery("SELECT * FROM CLIENTS WHERE TYPE='Professionnel'");
    float nbPro = mod->rowCount();

    mod->setQuery("SELECT * FROM CLIENTS WHERE TYPE='Particulier'");
    float nbPart = mod->rowCount();

    float total = nbPro + nbPart;
    if (total == 0) {
        QMessageBox::information(this, "Statistiques", "Aucun client trouvé dans la base !");
        return;
    }

    QString a = QString("Professionnels (%1%)").arg(QString::number((nbPro * 100) / total, 'f', 2));
    QString b = QString("Particuliers (%1%)").arg(QString::number((nbPart * 100) / total, 'f', 2));

    QPieSeries *series = new QPieSeries();
    series->append(a, nbPro);
    series->append(b, nbPart);

    if (nbPro != 0) {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (nbPart != 0) {
        QPieSlice *slice = series->slices().at(1);
        slice->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par type (" + QString::number((int)total) + " clients)");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->setTitleBrush(Qt::darkBlue);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(900, 500);
    chartView->show();
}


void MainWindow::on_PDF_commande_clicked()
{



    QPdfWriter pdf("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/listdescommandes.pdf");

        QPainter painter(&pdf);
               int i = 4000;
               painter.setPen(Qt::black);
               painter.setFont(QFont("Book Script", 20, QFont::Bold));
               painter.drawText(2500, 1400, "LISTE DES COMMANDES");
               painter.setPen(Qt::darkGreen);
               painter.setFont(QFont("Time New Roman", 10));
               painter.drawRect(100, 100, 9200, 2700); // dimension ta3 rectangle
               painter.drawRect(100, 3000, 9200, 500);

               painter.drawText(300,3300,"ID COMMANDE");
               painter.drawText(1000,3300,"REFERENCE");
               painter.drawText(2500,3300,"STATUT");
               painter.drawText(4500,3300,"MONTANT ESTIME");
               painter.drawText(6000,3300,"DATE LIVRAISON");
               painter.drawText(7500,3300,"ID CLIENT");
               QImage image("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/logoEsprit.png");
               painter.drawImage(QRectF(200, 200, 2000, 2000), image);
              /* QImage image1("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/FlexTrack.png");
               painter.drawImage(QRectF(7000, 200, 2000, 2000), image1);
               painter.drawRect(100, 3700, 9200, 9000);*/
               QSqlQuery query;
               query.prepare("select * from commandes");
               query.exec();
               while (query.next())
               {
                   painter.drawText(300, i, query.value(0).toString());
                   painter.drawText(1000, i, query.value(1).toString());
                   painter.drawText(2500, i, query.value(2).toString());
                   painter.drawText(4500, i, query.value(3).toString());
                   painter.drawText(6000, i, query.value(4).toString());
                   painter.drawText(7500, i, query.value(5).toString());
                   i = i + 350;
               }
               QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                   QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_PDF_client_clicked()
{
    QPdfWriter pdf("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/listdesclients.pdf");

        QPainter painter(&pdf);
               int i = 4000;
               painter.setPen(Qt::black);
               painter.setFont(QFont("Book Script", 20, QFont::Bold));
               painter.drawText(2500, 1400, "LISTE DES CLIENTS");
               painter.setPen(Qt::darkGreen);
               painter.setFont(QFont("Time New Roman", 10));
               painter.drawRect(100, 100, 9200, 2700); // dimension ta3 rectangle
               painter.drawRect(100, 3000, 9200, 500);

               painter.drawText(300,3300,"ID CLIENT");
               painter.drawText(1500,3300,"PRENOM");
               painter.drawText(2300,3300,"NOM");
               painter.drawText(3000,3300,"EMAIL");
               painter.drawText(5500,3300,"TEL");
               painter.drawText(6500,3300,"TYPE");
               painter.drawText(8000,3300,"ADRESSE");


               QImage image("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/logoEsprit.png");
               painter.drawImage(QRectF(200, 200, 2000, 2000), image);
              /* QImage image1("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/FlexTrack.png");
               painter.drawImage(QRectF(7000, 200, 2000, 2000), image1);
               painter.drawRect(100, 3700, 9200, 9000);*/
               QSqlQuery query;
               query.prepare("select * from CLIENTS");
               query.exec();
               while (query.next())
               {
                   painter.drawText(300, i, query.value(0).toString());
                   painter.drawText(1500, i, query.value(1).toString());
                   painter.drawText(2300, i, query.value(2).toString());
                   painter.drawText(3000, i, query.value(3).toString());
                   painter.drawText(5500, i, query.value(4).toString());
                   painter.drawText(6500, i, query.value(5).toString());
                   painter.drawText(8000, i, query.value(6).toString());

                   i = i + 350;
               }
               QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                   QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::ajouterHistorique(const QString &message)
{
    QFile file("C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/historique.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "❌ Erreur : impossible d'ouvrir le fichier historique.txt";
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");

    QString dateHeure = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    out << QString("[%1] %2\n").arg(dateHeure, message);

    file.close();
}
void MainWindow::on_historique_clicked()
{
    // 🗂️ Chemin complet du fichier historique
    QString cheminFichier = "C:/Users/21694/Downloads/Gestion_clientsxx/Gestion_clientsxx/Gestion_clients/historique.txt";

    QFile file(cheminFichier);
    if (!file.exists()) {
        QMessageBox::warning(this, "Fichier introuvable",
                             "Le fichier historique.txt n'existe pas encore.\n"
                             "Aucune action n'a été enregistrée pour le moment.");
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8"); // 🔹 pour les caractères spéciaux et accents
        QString contenu = in.readAll();
        file.close();

        if (contenu.trimmed().isEmpty()) {
            ui->histo->setPlainText("⚠️ Aucun historique disponible pour le moment.");
        } else {
            ui->histo->setPlainText(contenu);
        }
    } else {
        QMessageBox::critical(this, "Erreur de lecture",
                              "Impossible d'ouvrir le fichier historique.txt en lecture.");
        qDebug() << "❌ Erreur ouverture fichier :" << file.errorString();
    }
}


void MainWindow::on_trier_commande_clicked()
{        int index=ui->comboBox_tri_commande->currentIndex();
           QString orderByClause;
           QSqlQueryModel* model=new QSqlQueryModel();
           if (index == 0) {
                       orderByClause = " ORDER BY ID_COMMANDE DESC";
                   } else if (index == 1) {
                       orderByClause = " ORDER BY MONTANT_ESTIME ASC";
                   } else if (index == 2) {
                       orderByClause = " ORDER BY DATE_LIVRAISON_SOUHAITEE ASC";
                   }

           if (Co.tri(orderByClause)) {
               QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
                model->setQuery("SELECT *  FROM commandes"+orderByClause);
               ui->tab_commandes->setModel(model);
           } else {
              QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
           }

       }


void MainWindow::on_trier_client_clicked()
{

    int index=ui->comboBox_tri_client->currentIndex();
              QString orderByClause;
              QSqlQueryModel* model=new QSqlQueryModel();
              if (index == 0) {
                          orderByClause = " ORDER BY ID_CLIENT DESC";
                      } else if (index == 1) {
                          orderByClause = " ORDER BY CODE_POSTAL ASC";
                      } else if (index == 2) {
                          orderByClause = " ORDER BY VILLE ASC";
                      }

              if (C.tri(orderByClause)) {
                  QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
                   model->setQuery("SELECT *  FROM CLIENTS"+orderByClause);
                  ui->tab_CLIENT->setModel(model);
              } else {
                 QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
              }

          }


void MainWindow::on_recherche_client_clicked()
{
    int index = ui->comboBox_rech_client->currentIndex();
    QString wh;
    QSqlQueryModel* model = new QSqlQueryModel();
    QString k = ui->lineEdit_rechercheCLIENT->text().trimmed(); // Trimmed to remove leading and trailing whitespace

    if (k.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Empty field.\nClick Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    if (index == 0) {
        if (!C.idDisponible(k.toInt())) {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("ID unavailable.\nClick Cancel to exit."), QMessageBox::Cancel);
            return;
        }
        wh = "ID_CLIENT=" + k;
    } else if (index == 1) {
        wh = "TYPE='" + k + "'";
    } else if (index == 2) {
        wh = "VILLE='" + k + "'";
    }
    if (C.rech(wh)) {
        QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("Search performed.\nClick Cancel to exit."), QMessageBox::Cancel);
        model->setQuery("SELECT * FROM clients WHERE " + wh);
        ui->tab_CLIENT->setModel(model);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Search failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_recherche_commande_clicked()
{

            int index = ui->comboBox_rech_COMMANDE->currentIndex();
            QString wh;
            QSqlQueryModel* model = new QSqlQueryModel();
            QString k = ui->lineEdit_recherchecommande->text().trimmed(); // Trimmed to remove leading and trailing whitespace

            if (k.isEmpty()) {
                QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Empty field.\nClick Cancel to exit."), QMessageBox::Cancel);
                return;
            }

            if (index == 0) {
                if (!Co.idDisponible(k.toInt())) {
                    QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("ID unavailable.\nClick Cancel to exit."), QMessageBox::Cancel);
                    return;
                }
                wh = "ID_COMMANDE=" + k;
            } else if (index == 1) {
                wh = "STATUT='" + k + "'";
            } else if (index == 2) {
                wh = "ID_CLIENT='" + k + "'";
            }
            if (Co.rech(wh)) {
                QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("Search performed.\nClick Cancel to exit."), QMessageBox::Cancel);
                model->setQuery("SELECT * FROM COMMANDES WHERE " + wh);
                ui->tab_commandes->setModel(model);
            } else {
                QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Search failed.\nClick Cancel to exit."), QMessageBox::Cancel);
            }
        }

