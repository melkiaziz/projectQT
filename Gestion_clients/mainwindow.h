#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Commandes.h"
#include "Clients.h"


#include <QMainWindow>

#include <QMovie>
#include <QtGui>
#include <QtWidgets/QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:







    //void on_lineEdit_rechercheCLIENT_textChanged(const QString &arg1);

//    void on_lineEdit_recherchecommande_textChanged(const QString &arg1);

    void on_pb_ajouterCLIENT_clicked();

    void on_GOTOGESTIONCLIENT_clicked();


    void on_pb_modifierCLIENT_clicked();

    void on_pb_afficherCLIENT_clicked();

    void on_pb_supprimerCLIENT_clicked();

    void on_GOTOGESTIONCOMMANDE_clicked();

    void on_qrcodegen_CLIENT_clicked();

    void on_ajoutercommande_clicked();

    void on_modifiercommande_clicked();

    void on_affichercommande_clicked();

    void on_supprimercommande_clicked();

    void on_statistique_client_clicked();

    void on_statistique_commande_clicked();


    void on_PDF_commande_clicked();

    void on_PDF_client_clicked();
    void ajouterHistorique(const QString &message);

    void on_historique_clicked();

    void on_trier_commande_clicked();


    void on_trier_client_clicked();


    void on_recherche_client_clicked();

    void on_recherche_commande_clicked();

private:
    Ui::MainWindow *ui;
    Clients C;
    Commandes Co;

};
#endif // MAINWINDOW_H
