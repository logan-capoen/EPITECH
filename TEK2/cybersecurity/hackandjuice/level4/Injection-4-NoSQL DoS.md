# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection NoSQL       |
| **Composant affecté**      | API REST — endpoint `GET /rest/products/:id/reviews`                    |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Injection NoSQL

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur / Burp Suite | Modification du paramètre `:id` dans l'URL  |

### Étapes

1. **Identification de l'endpoint** — Lors d'un challenge précédent (Forged Review), on identifie que l'endpoint `GET /rest/products/:id/reviews` utilise le paramètre `id` pour interroger directement une base MongoDB.

2. **Analyse de la surface d'attaque** — Le paramètre `id` est transmis sans sanitisation à la couche MongoDB. Il est possible d'y injecter des opérateurs ou fonctions MongoDB natives.

3. **Injection de la fonction `sleep()`** — On remplace la valeur `id` par un appel à la fonction MongoDB `sleep(500)`, qui force le serveur à attendre 500 millisecondes avant de répondre.

4. **Confirmation du DoS** — La page met anormalement de temps à répondre, confirmant que la fonction `sleep()` est bien exécutée côté serveur. En multipliant les requêtes simultanées.

---

### Preuve de concept

```
GET /rest/products/sleep(500)/reviews HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ Réponse retardée de 500ms
```

---

## Risques

### Impact

- **Déni de service applicatif** — en spammant des requêtes avec `sleep()`, le pool de connexions MongoDB peut être saturé et rendre l'application indisponible
- **Injection NoSQL générale** — si `sleep()` fonctionne, d'autres opérateurs MongoDB  peuvent être injectés pour exfiltrer ou manipuler des données

---

## Correction

### Correctifs

- Valider et caster le paramètre `id` en entier avant tout usage
- Ne jamais passer de paramètres utilisateur directement à une requête MongoDB sans validation stricte

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Utiliser un ODM comme Mongoose avec des schémas typés pour forcer la validation des entrées
- Mettre en place un rate limiting sur les endpoints pour limiter l'impact d'un DoS