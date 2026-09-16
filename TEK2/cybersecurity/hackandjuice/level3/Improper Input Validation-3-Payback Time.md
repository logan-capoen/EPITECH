# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Validation insuffisante des entrées — Quantité négative |
| **Composant affecté**      | API REST — endpoint `PUT /api/BasketItems/:id`                          |
| **Sévérité**               | 🔴 Critique                                    |

---

## Méthodologie

### Techniques utilisées
- Interception et modification de requêtes HTTP

### Outils utilisés

| Outil       | Objectif                                              |
|-------------|-------------------------------------------------------|
| Burp Suite  | Interception et modification de la requête de mise à jour du panier |

### Étapes

1. **Interception de la requête** — En utilisant Burp Suite, on intercepte la requête `PUT /api/BasketItems/2` émise lors de la modification de la quantité d'un article dans le panier. Le corps JSON contient un champ `quantity` avec une valeur entière positive.

2. **Analyse de la surface d'attaque** — Le serveur accepte et applique directement la valeur `quantity` fournie par le client sans vérifier qu'elle est strictement positive.

3. **Injection d'une valeur négative** — On remplace la valeur du champ `quantity` par `-100` avant d'envoyer la requête.

4. **Confirmation de l'exploitation** — Le serveur accepte la valeur négative et l'applique, entraînant un total de panier négatif

---

### Preuve de concept

```http
PUT /api/BasketItems/2 HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
Content-Type: application/json

{"quantity": -100}
```

---

## Risques

### Impact

- **Obtention de produits gratuits** — en combinant des articles à quantité positive et négative, le total peut être ramené à zéro
- **Génération de crédit frauduleux** — si le total négatif est remboursé sous forme de crédit wallet, l'attaquant génère de l'argent fictif
- **Perte financière directe** pour la plateforme

---

## Correction

### Correctifs

- Valider côté serveur que la quantité est un entier strictement positif avant toute mise à jour
- Définir une valeur maximale de quantité pour éviter les abus par valeurs extrêmes

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais faire confiance aux valeurs numériques fournies par le client sans validation
- Appliquer des contraintes de validation à la fois au niveau de l'API et au niveau du schéma de base de données