# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Élévation de privilèges à l'inscription               |
| **Composant affecté**      | API REST — endpoint `POST /api/Users/`                                  |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Interception et modification de requêtes HTTP

### Outils utilisés

| Outil       | Objectif                                              |
|-------------|-------------------------------------------------------|
| Burp Suite  | Interception et modification de la requête d'inscription |

### Étapes

1. **Interception de la requête** — En utilisant Burp Suite, on intercepte la requête `POST /api/Users/` émise lors de la création d'un compte. Le corps JSON contient les champs classiques d'inscription (`email`, `password`, `securityQuestion`, `securityAnswer`).

2. **Analyse de la surface d'attaque** — Le serveur accepte et mappe directement les champs JSON reçus sur le modèle utilisateur en base de données, sans filtrer les propriétés sensibles comme `role`.

3. **Injection du champ `role`** — On ajoute le champ `"role": "admin"` au corps de la requête avant de l'envoyer.

4. **Confirmation de l'exploitation** — Le serveur crée le compte avec le rôle administrateur, permettant un accès complet à l'interface d'administration sans aucune autorisation préalable.

---

### Preuve de concept

```http
POST /api/Users/ HTTP/2
Host: ctf.juice.cyber.epitest.eu
Content-Type: application/json

{
  "email": "admin2@test.com",
  "password": "password",
  "passwordRepeat": "password",
  "securityQuestion": { "id": 1, ... },
  "securityAnswer": "yes",
  "role": "admin"
}
```
---

## Risques

### Impact

- **Élévation de privilèges totale** — n'importe quel utilisateur peut se créer un compte administrateur
- **Compromission complète de la plateforme** — accès à l'ensemble des fonctionnalités d'administration
- **Contournement de tout contrôle d'accès** — les restrictions basées sur les rôles deviennent inopérantes
- **Violation réglementaire** — accès non autorisé à des données personnelles (RGPD)

---

## Correction

### Correctifs

- Ne jamais mapper directement le corps de la requête sur le modèle de données
- Définir une liste blanche explicite des champs autorisés à l'inscription
- Forcer le rôle à `"customer"` côté serveur lors de la création d'un compte, indépendamment des données reçues

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Utiliser des DTOs (Data Transfer Objects) pour valider et filtrer les entrées avant persistance
- Ne jamais exposer les propriétés internes du modèle (rôle, permissions, flags) dans les réponses ou les formulaires clients