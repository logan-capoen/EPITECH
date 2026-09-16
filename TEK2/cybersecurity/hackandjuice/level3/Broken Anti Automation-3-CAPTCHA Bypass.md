# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Contournement de CAPTCHA — Réponses statiques et prévisibles            |
| **Composant affecté**      | API REST — endpoint `POST /api/Feedbacks/`                              |
| **Sévérité**               | 🟡 Moyenne                                                              |

---

## Méthodologie

### Techniques utilisées
- Interception de requêtes HTTP
- Analyse du mécanisme de validation

### Outils utilisés

| Outil       | Objectif                                              |
|-------------|-------------------------------------------------------|
| Burp Suite  | Interception et modification de la requête HTTP       |

### Étapes

1. **Interception de la requête** — En utilisant Burp Suite, on intercepte la requête `POST /api/Feedbacks/` émise lors de la soumission d'un feedback. Le corps JSON contient un `captchaId` et un champ `captcha` correspondant à la réponse attendue.

2. **Analyse du mécanisme CAPTCHA** — En observant les différents `captchaId` disponibles, on constate que les réponses associées sont statiques et prévisibles. Par exemple, le `captchaId: 0` attend systématiquement la réponse `"0"`.

3. **Forgeage de la requête** — Il suffit de fournir un `captchaId` connu et sa réponse statique associée pour passer la validation, sans jamais avoir à résoudre un vrai CAPTCHA.

4. **Confirmation de l'exploitation** — Le serveur retourne une réponse `200 OK` et enregistre le feedback, confirmant que le CAPTCHA est contournable par simple connaissance des couples `id`/`réponse`.

---

### Preuve de concept

```http
POST /api/Feedbacks/ HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
Content-Type: application/json

{"UserId":1,"captchaId":0,"captcha":"0","comment":"coucou","rating":1}
```

---

## Risques

### Impact

- **Contournement total de la protection anti-bot** — le CAPTCHA n'assure plus son rôle
- **Spam de contenu automatisé** — des feedbacks peuvent être soumis en masse de manière scriptée
- **Pollution des données** — les avis et statistiques de la plateforme peuvent être faussés à volonté

---

## Correction

### Correctifs

- Générer des CAPTCHAs dynamiquement côté serveur avec des réponses aléatoires à chaque requête
- Ne jamais stocker les réponses CAPTCHA de façon statique

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Coupler le CAPTCHA à un rate limiting côté serveur