# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition de logs sensibles — Contrôle d'accès insuffisant             |
| **Composant affecté**      | Endpoint `GET /support/logs`                                            |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Énumération d'endpoints
- Accès avec un compte support

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Connexion en tant que `support@juice-sh.op` et navigation vers l'endpoint |

### Étapes

1. **Connexion au compte support**  — On peut se connecter très simplement au compte `support@juice-sh.op` avec un injection SQL.

2. **Accès aux logs** — En naviguant directement sur `https://ctf.juice.cyber.epitest.eu/support/logs`, l'application retourne les logs serveur sans restriction particulière au-delà de l'authentification avec un compte support.

3. **Lecture des logs** — Les fichiers de logs exposent des informations sensibles sur le fonctionnement interne de l'application.

---

### Preuve de concept

**Étape 1 — Connexion :**
```http
POST /rest/user/login HTTP/2
Host: ctf.juice.cyber.epitest.eu
Content-Type: application/json

{"email":"support@juice-sh.op' --","password":"blablabla"}
```

**Étape 2 — Accès aux logs :**
```http
GET /support/logs HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token_support>
```

---

## Risques

### Impact

- **Exposition de données techniques sensibles** — stack traces, requêtes SQL, chemins de fichiers internes, versions de dépendances
- **Fuite de données personnelles** — les logs peuvent contenir des emails, IPs, tokens JWT ou autres données utilisateurs
- **Aide à la reconnaissance** — les informations contenues dans les logs facilitent grandement l'exploitation d'autres vulnérabilités
- **Violation réglementaire** — exposition de données personnelles dans les logs

---

## Correction

### Correctifs

- Restreindre l'accès à `/support/logs` aux seuls administrateurs système, pas aux comptes support généralistes

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais logger de données sensibles
- Stocker les logs dans un système centralisé avec des accès strictement contrôlés
- Appliquer le principe du moindre privilège sur tous les comptes applicatifs, y compris les comptes support