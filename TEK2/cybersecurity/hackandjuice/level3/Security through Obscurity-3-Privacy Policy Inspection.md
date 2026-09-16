# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition d'endpoint caché — Easter Egg    |
| **Composant affecté**      | Page Privacy Policy + endpoint `GET /we/may/also/instruct/you/to/refuse/all/reasonably/necessary/responsibility` |
| **Sévérité**               | 🟢 Faible                                                               |

---

## Méthodologie

### Techniques utilisées
- Analyse manuelle du contenu de la page

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Lecture de la Privacy Policy et observation visuelle des indices |

### Étapes

1. **Lecture de la Privacy Policy** — En parcourant intégralement la page de politique de confidentialité de l'application, on remarque que certains mots s'affichent avec un effet visuel brillant au survol.

2. **Collecte des mots mis en évidence** — En relevant chaque mot mis en évidence dans l'ordre d'apparition, on reconstitue une phrase cohérente :
   > *"we may also instruct you to refuse all reasonably necessary responsibility"*

3. **Construction de l'URL** — Les mots collectés forment un chemin d'URL une fois concaténés avec des `/`.

4. **Accès à l'endpoint caché** — En naviguant sur l'URL reconstituée, on accède à un endpoint non référencé et non documenté de l'application.

---

### Preuve de concept


**URL obtenue :**
```
GET /we/may/also/instruct/you/to/refuse/all/reasonably/necessary/responsibility HTTP/2
Host: ctf.juice.cyber.epitest.eu
```

---

## Risques

### Impact

- **Exposition d'un endpoint non protégé** — des fonctionnalités ou données non prévues pour le public peuvent être accessibles
- **Surface d'attaque élargie** — les endpoints non documentés échappent aux audits de sécurité classiques
- **Fuite d'informations** — selon le contenu retourné, des données sensibles peuvent être exposées

---

## Correction

### Correctifs

- Supprimer ou protéger les endpoints cachés non destinés à la production
- Retirer tout indice visuel dans les pages publiques qui pourrait guider un attaquant vers des ressources non documentées

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne pas cacher d'indices