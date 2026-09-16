# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Contrôle d'accès insuffisant — Contournement de paiement                |
| **Composant affecté**      | API REST — endpoint `POST /rest/deluxe-membership`                      |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Interception et modification de requêtes HTTP

### Outils utilisés

| Outil       | Objectif                                              |
|-------------|-------------------------------------------------------|
| Burp Suite  | Interception et modification de la requête d'achat   |

### Étapes

1. **Interception de la requête** — En utilisant Burp Suite, on intercepte la requête `POST /rest/deluxe-membership` émise lors du clic sur "Devenir membre Deluxe". Le corps JSON contient un champ `paymentMode` avec la valeur `"wallet"`.

2. **Analyse de la surface d'attaque** — Le serveur utilise le champ `paymentMode` fourni par le client pour déterminer le traitement à appliquer, sans valider que la valeur reçue correspond à un moyen de paiement légitime et suffisamment approvisionné.

3. **Modification du champ `paymentMode`** — On remplace la valeur `"wallet"` par `"free"` dans le corps de la requête avant de l'envoyer.

4. **Confirmation de l'exploitation** — Le serveur accorde le statut Deluxe sans déclencher de transaction financière, confirmant que la validation du paiement est effectuée côté client uniquement.

---

### Preuve de concept

```http
POST /rest/deluxe-membership HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
Content-Type: application/json

{"paymentMode":"free"}
```

---

## Risques

### Impact

- **Contournement de paiement** — n'importe quel utilisateur peut obtenir le statut Deluxe gratuitement
- **Perte financière directe** — la plateforme ne perçoit pas le paiement pour les abonnements obtenus frauduleusement
- **Atteinte à l'intégrité des données** — les statuts d'abonnement ne reflètent plus les transactions réelles

---

## Correction

### Correctifs

- Ne jamais faire confiance au champ `paymentMode` fourni par le client pour décider si un paiement est valide
- La validation du paiement doit être effectuée entièrement côté serveur, en vérifiant la transaction avant d'accorder le statut Deluxe
- Supprimer toute logique côté serveur qui accepte `"free"` comme valeur de paiement valide

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais déléguer la logique de validation de paiement au client
