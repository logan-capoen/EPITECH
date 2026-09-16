# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | IDOR (Référence directe non sécurisée à un objet)           |
| **Composant affecté**      | API REST — endpoint `POST /api/BasketItems`                             |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Tests manuels
- Interception et modification de requêtes HTTP

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Burp Suite         | Interception et modification des requêtes HTTP    |

### Étapes

1. **Analyse du trafic réseau** — En utilisant Burp Suite, on intercepte la requête `POST /api/BasketItems` émise lors de l'ajout d'un article au panier. Le corps de la requête contient un champ `BasketId` contrôlé côté client.

2. **Identification de la surface d'attaque** — Le serveur utilise le `BasketId` fourni dans le corps de la requête pour identifier le panier cible, la vérification de celui ci est trop faible et l'on peut donc bypass cette vérification.

3. **Tentative directe** — Modifier le `BasketId` directement vers celui d'une victime est refusé par le serveur (contrôle partiel côté serveur).

4. **Contournement par double clé JSON** — En envoyant deux occurrences du champ `BasketId` dans le même objet JSON (`BasketId: 6` pour l'autorisation, puis `BasketId: 3` pour la cible), le serveur autorise la requête via la première valeur mais l'applique sur le panier cible via la seconde.

5. **Confirmation de l'exploitation** — Le serveur retourne une réponse `200 OK` et ajoute l'article dans le panier de la victime (BasketId: 3), confirmant la vulnérabilité.

---

### Preuve de concept

```http
POST /api/BasketItems HTTP/2
Host: ctf.juice.cyber.epitest.eu
Authorization: Bearer <token>
Content-Type: application/json

{"ProductId": 1, "BasketId": 6, "BasketId": 3, "quantity": 1}
```

---

## Risques

### Impact

- **Manipulation de panier tiers** — un attaquant peut ajouter des articles dans le panier de n'importe quel utilisateur à son insu
- **Violation de l'intégrité des données** — le contenu des paniers ne reflète plus les actions réelles des utilisateurs
- **Surface d'attaque élargie** — si d'autres endpoints suivent le même pattern, des opérations de suppression ou modification sur des ressources tierces sont possibles

---

## Correction

### Correctifs

- Ne jamais utiliser le `BasketId` fourni par le client pour déterminer le panier cible,  l'extraire systématiquement depuis le token JWT côté serveur
- Rejeter toute requête JSON contenant des clés dupliquées (parser strictement le JSON)

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Appliquer le principe du moindre privilège sur tous les endpoints
- Ne jamais faire confiance aux données fournies par le client pour identifier la ressource cible