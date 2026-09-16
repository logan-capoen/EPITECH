# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                             |
|----------------------------|-----------------------------------------------------|
| **Type**                   | IDOR (Référence directe non sécurisée à un objet)    |
| **Composant affecté**      | API REST — endpoint \`POST /api/Feedbacks\`      |
| **Sévérité**               | 🟠 Élevée   |

---

## Méthodologie

### Techniques utilisées
- Tests manuels
- Interception et modification de requêtes HTTP

### Outils utilisés
| Outil        | Objectif                              |
|--------------|---------------------------------------|
| DevTools (Chrome)   | Analyse du trafic réseau et interception des appels API           |
| Console navigateur     | Exécution de requêtes HTTP forgées manuellement            |

### Étapes

1. **Analyse du trafic réseau** — Lors de la soumission d'un feedback, l'outil DevTools révèle qu'une requête POST /api/Feedbacks est envoyée avec un champ UserId dans le corps de la requête.
2. **Identification de la surface d'attaque** — Le champ UserId est contrôlé côté client et n'est pas validé par le serveur par rapport à l'identité de l'utilisateur authentifié (token JWT).
3. **Forgeage de la requête** — Depuis la console du navigateur, une requête est construite manuellement en remplaçant le UserId par celui d'une autre victime.
4. **Contournement du CAPTCHA** — Le mécanisme de CAPTCHA est contourné en passant captchaId: 0 et captcha: "0".
5. **Confirmation de l'exploitation** — Le serveur retourne une réponse 200 OK et publie le feedback au nom de la victime, confirmant la vulnérabilité.

---

### Preuve de concept
```
fetch('/api/Feedbacks', {
  method: 'POST',
  headers: {
    'Authorization': 'Bearer ' + localStorage.getItem('token'),
    'Content-Type': 'application/json'
  },
  body: JSON.stringify({
    comment: "blablablou",
    rating: 5,
    UserId: 2,  // <- ID de la victime
    captchaId: 0, // captcha 0 answer is 0
    captcha: "0"
  })
}).then(r => r.json()).then(console.log)
```

---

## Risques

### Impact
- **Usurpation d'identité partielle** — un attaquant peut publier du contenu (avis, commentaires) au nom de n'importe quel utilisateur
- **Violation de l'intégrité des données** — les données de feedback ne reflètent plus fidèlement les actions réelles des utilisateurs
- **Violation réglementaire** — exploitation de données d'identification utilisateur sans consentement (RGPD)
- **Surface d'attaque élargie** — si d'autres endpoints suivent le même pattern, la manipulation de ressources tierces (modification, suppression) est possible

---

## Correction

### Correctifs

- Refactoriser tous les endpoints sensibles pour que l'identité soit toujours résolue depuis le token d'authentification, jamais depuis le payload client 
- Mettre en place des tests d'autorisation automatisés

### Bonnes pratiques de sécurité recommandées
- Suivre les directives OWASP Top 10
- Appliquer le principe du moindre privilège sur tous les endpoints
- Ne jamais faire confiance aux données fournies par le client pour identifier la ressource cible
