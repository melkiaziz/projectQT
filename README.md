# Gestion Clients & Commandes — Application Desktop Qt/C++

Application de bureau développée en **C++ avec Qt** pour gérer les clients d'une entreprise et le suivi de leurs commandes. Elle est connectée à une base de données via ODBC.

Projet réalisé dans le cadre de la formation d'ingénieur à **ESPRIT School of Engineering**.

---

## Fonctionnalités

### Gestion des clients
- **CRUD complet** : ajouter, afficher, modifier et supprimer un client
- **Contrôle de saisie** : vérification du format de l'e-mail et de l'unicité de l'identifiant
- **Recherche** dynamique d'un client
- **Tri** par identifiant, code postal ou ville
- **Export PDF** de la liste des clients
- **QR code** : génération d'un QR code contenant la fiche complète d'un client
- **Statistiques** : graphique de répartition des clients par type (Particulier / Professionnel)

### Gestion des commandes
- **CRUD complet** des commandes (référence, statut, montant estimé, date de livraison souhaitée, client associé)
- **Recherche** et **tri** par identifiant, montant ou date de livraison
- **Export PDF** de la liste des commandes
- **Statistiques** : graphique de répartition des commandes par statut (En cours / Livrée / Annulée)
- **Historique** : chaque ajout, modification ou suppression est horodaté et consultable depuis l'application

## Technologies

| Domaine | Outils |
| --- | --- |
| Langage | C++11 |
| Framework | Qt 5 (Widgets, SQL, Charts, PrintSupport) |
| Base de données | Oracle, via un pilote ODBC (`QODBC`) |
| QR code | Bibliothèque QR Code Generator (Nayuki) |
| IDE | Qt Creator |

## Structure du projet

```
Gestion_clients/
├── main.cpp            # Point d'entrée, ouverture de la connexion
├── connection.cpp/.h   # Connexion à la base via ODBC
├── Clients.cpp/.h      # Classe métier Client (CRUD, tri, recherche, validation e-mail)
├── Commandes.cpp/.h    # Classe métier Commande (CRUD, tri, recherche)
├── mainwindow.cpp/.h   # Logique de l'interface (PDF, stats, QR code, historique)
├── mainwindow.ui       # Interface graphique (Qt Designer)
├── QrCode.cpp/.hpp     # Génération des QR codes
├── img.qrc             # Ressources (images, logo)
└── Gestion_clients.pro # Fichier projet qmake
```

## Base de données

Tables utilisées par l'application :

```sql
CREATE TABLE CLIENTS (
  ID_CLIENT    NUMBER PRIMARY KEY,
  PRENOM       VARCHAR2(50),
  NOM          VARCHAR2(50),
  EMAIL        VARCHAR2(100),
  TEL          VARCHAR2(20),
  TYPE         VARCHAR2(20),   -- 'Particulier' ou 'Professionnel'
  ADRESSE      VARCHAR2(150),
  VILLE        VARCHAR2(50),
  CODE_POSTAL  VARCHAR2(10)
);

CREATE TABLE COMMANDES (
  ID_COMMANDE               NUMBER PRIMARY KEY,
  REF_COMMANDE              VARCHAR2(50),
  STATUT                    VARCHAR2(20),   -- 'En cours', 'Livree' ou 'Annulee'
  MONTANT_ESTIME            NUMBER,
  DATE_LIVRAISON_SOUHAITEE  DATE,
  ID_CLIENT                 NUMBER REFERENCES CLIENTS(ID_CLIENT)
);
```

## Installation et lancement

1. Installe **Qt 5** et **Qt Creator** avec les modules *Charts* et *PrintSupport*.
2. Crée les tables ci-dessus dans ta base Oracle.
3. Configure une source de données ODBC nommée `test-bd` qui pointe vers cette base.
4. Dans `connection.cpp`, renseigne ton nom d'utilisateur et ton mot de passe.
5. Ouvre `Gestion_clients/Gestion_clients.pro` dans Qt Creator, puis compile et lance le projet.

> Les chemins des fichiers PDF et `historique.txt` sont définis dans `mainwindow.cpp`. Adapte-les à ton poste avant de lancer l'application.

## Auteur

**Melki Mohamed Aziz** — Ingénieur en Génie Informatique (ESPRIT)

- Portfolio : [melkiaziz.github.io](https://melkiaziz.github.io/portfolioMelkiAziz.io/)
- LinkedIn : [melki-mohamed-aziz](https://www.linkedin.com/in/melki-mohamed-aziz-4a6bb1260)
