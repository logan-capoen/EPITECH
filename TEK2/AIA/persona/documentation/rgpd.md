# Conformité RGPD

La protection des données personnelles de nos utilisateurs est une priorité absolue. Ce projet a été conçu en intégrant les principes fondamentaux du Règlement Général sur la Protection des Données (RGPD).

---

## Principes appliqués dans le projet

### Minimisation des données
Nous collectons uniquement les informations strictement nécessaires au bon fonctionnement du service (l'adresse e-mail pour l'envoi de la newsletter). Aucun historique de navigation, donnée biométrique ou information superflue n'est stocké dans notre base de données.

### Transparence et contrôle
Chaque utilisateur dispose d'un contrôle total sur ses données :
* **Droit de rectification :** La mise à jour des informations se fait à l'aide du chatbot, de manière sécurisé.
* **Droit à l'effacement (Droit à l'oubli) :** Un lien de désabonnement est obligatoirement intégré en bas de chaque newsletter envoyée.

---

## Logique technique du désabonnement

Le respect du RGPD est automatisé grâce au workflow dédié `unsubscribe.json` :

1. **Action utilisateur :** Un clic sur le lien "Se désabonner" en bas de page déclenche instantanément un webhook vers n8n.
2. **Traitement immédiat :** Le système supprime ou met à jour le statut de l'adresse e-mail dans la table interne `users`.
3. **Arrêt des communications :** L'utilisateur est immédiatement exclu des futures boucles d'envoi du workflow `send_mail.json`.

---

## Sécurité des données

* **Pas de stockage en dur :** Aucune clé d'accès ou identifiant n'est inscrit directement dans le code. Tout est centralisé de manière sécurisée dans le fichier `.env`.
* **Hébergement local ou contrôlé :** En utilisant Docker, l'intégralité de la base de données reste sous le contrôle de l'administrateur qui déploie la solution.