# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection NoSQL — Manipulation de requête MongoDB (`$exists`)           |
| **Composant affecté**      | API REST — endpoint `PATCH /rest/products/reviews`                      |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Interception et modification de requêtes HTTP
- Injection d'opérateurs NoSQL MongoDB

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Burp Suite         | Interception, modification de la méthode HTTP et injection du payload NoSQL |

### Étapes

1. **Interception de la requête** — En utilisant Burp Suite, on intercepte la requête `PUT /rest/products/24/reviews` émise lors de la soumission d'un avis sur un produit. Le corps contient `message` et `author`.

2. **Changement de méthode HTTP** — On remplace la méthode `PUT` par `PATCH` et on supprime le paramètre `id` du chemin (`/24`) pour cibler l'endpoint générique `/rest/products/reviews`.

3. **Injection de l'opérateur MongoDB** — Dans le corps de la requête, on remplace le champ `id` par un objet contenant l'opérateur MongoDB `{ "$exists": true }`. Cet opérateur sélectionne **tous les documents** dont le champ `id` existe, c'est-à-dire la totalité des avis.

4. **Mise à jour en masse** — Le serveur exécute la mise à jour sur tous les avis correspondant à la condition  et applique le nouveau message à l'ensemble des reviews de tous les produits.

5. **Confirmation de l'exploitation** — Le message est modifié sur l'intégralité des avis de la plateforme en une seule requête.

---

### Preuve de concept

**Requête originale (PUT — un seul produit) :**
```http
PUT /rest/products/24/reviews HTTP/1.1
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
Content-Type: application/json

{"message":"coucou c'est l'avis","author":"acc0unt4nt@juice-sh.op"}
```

**Requête modifiée (PATCH — tous les produits) :**
```http
PATCH /rest/products/reviews HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
Content-Type: application/json

{
  "id": { "$exists": true },
  "message": "coucou c'est l'avis"
}
```

---

## Risques

### Impact

- **Modification en masse de données** — l'intégralité des avis de la plateforme peut être écrasée en une seule requête
- **Atteinte à l'intégrité des données** — les avis légitimes des utilisateurs sont définitivement altérés
- **Déni de service applicatif partiel** — la suppression ou l'altération de toutes les reviews dégrade l'expérience utilisateur
- **Escalade possible** — si d'autres opérateurs MongoDB sont acceptés, une exfiltration de données est envisageable

---

## Correction

### Correctifs

- Valider strictement les champs acceptés dans le body, rejeter tout objet JSON contenant des clés commençant par `$` :
- Vérifier côté serveur que l'utilisateur authentifié est bien l'auteur de l'avis avant toute mise à jour

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Utiliser un ODM comme Mongoose avec des schémas stricts qui rejettent les clés inconnues
- Auditer tous les endpoints `PATCH` et `PUT` pour s'assurer qu'ils ne permettent pas de mises à jour en masse non intentionnelles