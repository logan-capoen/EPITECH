# Documentation Technique & Architecture du Projet

Bienvenue dans le guide technique du projet. Ce document est conçu pour les développeurs et contributeurs qui souhaitent comprendre le fonctionnement interne du système, modifier les flux existants ou ajouter de nouvelles fonctionnalités à notre écosystème n8n.

---

## Architecture Globale

Le projet repose sur une architecture conteneurisée légère et modulaire :

* Orchestration : n8n (exécuté via Docker Compose).
* Base de données interne : n8n Data Tables (stockage des utilisateurs).
* Services tiers (API) : Google Gemini (Génération IA), GNews & NewsAPI (Agrégation de contenu), Gmail SMTP (Routage e-mail).

Toutes les variables de configuration sensibles sont centralisées dans le fichier .env.

---

## Analyse des Workflows (Scénarios n8n)

Le système est découpé en 4 workflows indépendants et spécialisés. Pour faciliter la maintenance, chaque flux possède une responsabilité unique.

### 1. auth_persona.json (Gestion des accès et OTP)
* Rôle : Gérer l'authentification sécurisée des utilisateurs.
* Déclencheur (Trigger) : Nœud form (welcome).
* Logique interne : 
    1. Réception de la demande de connexion de l'utilisateur.
    2. Génération d'un jeton temporaire à usage unique (One-Time Password - OTP).
    3. Envoi du code par e-mail via le nœud Send OTP (Relais SMTP Gmail).
* Points d'amélioration possibles : Ajouter une expiration stricte du jeton en base.

### 2. chatbot_persona.json (Moteur d'interactions IA)
* Rôle : Gérer la logique de discussion et de requêtage avec l'agent conversationnel.
* Déclencheur (Trigger) : webhook / Interface de chat.
* Logique interne : 
    1. Réception du prompt utilisateur.
    2. Appel au nœud Gemini pour mettre à jour la base de donnée avec les informations reçu.

### 3. send_mail.json (Génération et envoi de la Newsletter)
* Rôle : Automatiser la veille informationnelle, la synthèse IA et l'envoi de la newsletter.
* Déclencheur (Trigger) : Nœud Schedule (Planification temporelle).
* Logique interne : 
    1. Requêtes simultanées sur les API GNews et NewsAPI pour récupérer l'actualité fraîche.
    2. Nettoyage et fusion des flux de données reçus.
    3. Le nœud Gemini synthétise les articles selon une charte éditoriale précise.
    4. Boucle d'envoi e-mail (Send news) sur l'ensemble des contacts actifs présents dans la table users.

### 4. unsubscribe.json (Gestion du désabonnement)
* Rôle : Garantir la conformité RGPD en permettant un désengagement instantané.
* Déclencheur (Trigger) : Webhook lié au lien "Se désabonner" présent en bas des e-mails.
* Logique interne : 
    1. Réception du token du destinataire.
    2. Requête de suppression dans la Data Table users.
    3. Redirection de l'utilisateur vers une page de confirmation épurée.

---

## Modèle de Données (n8n Data Tables)

Le projet utilise une table nommée users. Si vous devez altérer le comportement du système, veillez à respecter ou faire évoluer ce schéma de données :

| Champ | Type | Description |
| :--- | :--- | :--- |
| id | String / UUID | Identifiant unique de l'utilisateur |
| email | String | Adresse e-mail principale (Sert d'index pour l'envoi) |
| created_at | DateTime | Date d'inscription initiale |
| tokenAuth | String | token du user servant à l'identifié |
| interests | string | intérêt du user |
| ProgrammedAt | string | heure à laquelle le email sera envoyé|


---

## Comment contribuer et améliorer le projet ?

Pour ajouter une fonctionnalité ou corriger un bug, nous vous conseillons de suivre ce flux de travail :

1.  Mode Test : Ne travaillez jamais directement sur les workflows actifs. Modifiez le workflow en local ou dupliquez-le.
2.  Utilisation des expressions : Pour lier les variables d'environnement dans vos nouveaux nœuds, utilisez impérativement la syntaxe des expressions n8n : {{ $env.NOM_DE_LA_VAR }}.
3.  Export : Une fois vos modifications testées et validées, cliquez sur les trois petits points en haut à droite du workflow, faites Export to file et remplacez le fichier JSON correspondant dans le dossier /workflows du dépôt.