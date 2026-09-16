# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                             |
|----------------------------|-----------------------------------------------------|
| **Type**                   | IDOR (Référence directe non sécurisée à un objet)    |
| **Composant affecté**      | API REST — endpoint \`/rest/products/:id/reviews\`      |
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

1. **Analyse du trafic réseau** — En naviguant sur la page d'un produit, DevTools révèle qu'une requête PUT /rest/products/1/reviews est émise lors de la soumission d'un avis. Le corps de la requête contient un champ author contrôlé côté client.
2. **Identification de la surface d'attaque** — Le champ author accepte une adresse e-mail arbitraire sans que le serveur ne la compare à l'identité de l'utilisateur authentifié via le token JWT.
3. **Forgeage de la requête** — Depuis la console du navigateur, une requête est construite manuellement en remplaçant le champ author par l'adresse d'un autre compte.
4. **Confirmation de l'exploitation** — Le serveur accepte la requête et publie l'avis sous l'identité de l'administrateur, sans aucune erreur d'autorisation.

---

### Preuve de concept
```
fetch('/rest/products/1/reviews', {
  method: 'PUT',
  headers: {
    'Authorization': 'Bearer ' + localStorage.getItem('token'),
    'Content-Type': 'application/json'
  },
  body: JSON.stringify({
    message: "neuille",
    author: "admin@juice-sh.op"
  })
}).then(r => r.json()).then(console.log)
```

---

## Risques

### Impact
- **Usurpation d'identité partielle** — un attaquant peut publier du contenu (avis, commentaires) au nom de n'importe quel utilisateur
- **Violation de l'intégrité des données** — les données de review ne reflètent plus fidèlement les actions réelles des utilisateurs
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
