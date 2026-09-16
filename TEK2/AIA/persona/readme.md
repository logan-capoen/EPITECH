# Persona Project - Newsletter Personnalisée par IA

Ce projet est une solution d'automatisation complète développée sur n8n qui permet de créer, gérer et envoyer une newsletter automatisée et synthétisée par intelligence artificielle. Grâce à l'agrégation de flux d'actualités et à la puissance des modèles de langage, le système génère du contenu ciblé et pertinent pour les utilisateurs inscrits.

Le projet est conçu de manière modulaire et sécurisée, en mettant un point d'honneur sur la simplicité d'utilisation pour le grand public et la conformité aux réglementations actuelles.

---

## Fonctionnalités Principales

*   **Agrégation d'Actualités :** Récupération automatique des derniers articles via des API de presse.
*   **Synthèse par IA :** Génération d'un résumé éditorial unique grâce au modèle de langage Google Gemini.
*   **Authentification Sécurisée :** Connexion et inscription sécurisé à l'aide de codes uniques par e-mail (OTP).
*   **Gestion du Désabonnement :** Processus de retrait simplifié en un clic pour les utilisateurs.

---

## Structure de la Documentation

Pour vous guider dans l'installation, la compréhension et l'amélioration de ce projet, la documentation a été découpée en quatre sections spécialisées :

### 1. Guide de Lancement et d'Installation
Contient toutes les instructions pour configurer l'environnement local, instancier les conteneurs Docker et initialiser l'interface d'administration. [Consulter la documentation de lancement](README.md)

### 2. Architecture Technique et Workflows
Destiné aux développeurs et aux contributeurs souhaitant comprendre la structure des quatre workflows n8n, le schéma de la base de données et la méthode pour modifier ou améliorer le système. [Consulter la documentation d'architecture](architecture.md)

### 3. Politique de Confidentialité et RGPD
Détaille les mesures appliquées pour respecter la vie privée des utilisateurs, notamment le principe de minimisation des données collectées et l'automatisation du droit à l'oubli. [Consulter la documentation RGPD](rgpd.md)

### 4. Sécurité et Protection de l'Identité
Explications sur les protocoles de sécurité mis en œuvre, le fonctionnement des jetons d'authentification uniques (`tokenAuth`) pour éviter l'usurpation d'identité et la validation par OTP. [Consulter la documentation de sécurité](securite.md)

---

## Technologies Utilisées

*   **Orchestrateur :** n8n
*   **Conteneurisation :** Docker / Docker Compose
*   **Intelligence Artificielle :** Google Gemini API
*   **Sources de Données :** GNews API & NewsAPI
*   **Routage E-mail :** SMTP Gmail

---

## contributors

*    **Ethan Saintot**
*    **Logan Capoen**