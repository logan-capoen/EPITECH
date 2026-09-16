# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | CSP Bypass + XSS Stocké — Page legacy `/profile`                        |
| **Composant affecté**      | Page `/profile` — champs `username` et `image URL`                      |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Identification de page legacy non protégée par Angular
- Injection XSS via champ username
- Manipulation de la Content Security Policy via champ image URL

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Navigation sur `/profile` et injection des payloads |

### Étapes

1. **Identification de la page legacy** — La page `/profile` est une ancienne page qui ne passe pas par le routeur Angular (`/#/`). Contrairement aux autres pages de l'application, elle n'est pas protégée par les mécanismes de sanitisation d'Angular.

2. **Injection XSS dans le champ username** — Le champ username accepte du HTML non sanitisé. On injecte un payload XSS en utilisant un pattern qui bypasse les filtres basiques :
   ```html
   <<a|ascript>alert(`xss`)</script>
   ```
   La syntaxe `<<a|` perturbe les parseurs HTML naïfs qui voient un tag `<a` malformé, mais le navigateur interprète finalement le `<script>` et exécute le code.

3. **Manipulation de la CSP via le champ image** — Le champ d'URL d'image est utilisé par le serveur pour construire l'en-tête `Content-Security-Policy`. En injectant une directive CSP dans l'URL :
   ```
   https://placekitten.com/300/300; script-src 'unsafe-inline'
   ```
   Le serveur concatène naïvement cette valeur dans le header CSP, ajoutant `script-src 'unsafe-inline'` qui autorise l'exécution de tout JavaScript inline.

4. **Exécution du XSS** — La combinaison des deux injections permet l'exécution du script injecté dans le username : la CSP est assouplie par le champ image, et le XSS dans le username est alors exécuté sans être bloqué.

---

### Preuve de concept

**Champ username :**
```html
<<a|ascript>alert(`xss`)</script>
```

**Champ image URL :**
```
https://placekitten.com/300/300; script-src 'unsafe-inline'
```

**Header CSP résultant (corrompu) :**
```
Content-Security-Policy: img-src 'self' https://placekitten.com/300/300; script-src 'unsafe-inline'
```

---

## Risques

### Impact

- **XSS stocké** — le payload est persisté en base et s'exécute pour chaque visiteur de la page profil
- **Neutralisation de la CSP** — la protection principale contre le XSS est désactivée par l'attaquant lui-même
- **Vol de session** — `document.cookie` et tokens JWT peuvent être exfiltrés
- **Défiguration et phishing** — injection de contenu arbitraire dans la page
- **Propagation** — si un admin visite le profil, son compte peut être compromis

---

## Correction

### Correctifs

- Ne jamais construire un header CSP à partir d'une entrée utilisateur
- Sanitiser le champ `username` avec une bibliothèque à jour avant stockage et affichage
- Mettre à jour la page `/profile` pour utiliser le framework Angular avec sa sanitisation native, ou la supprimer si elle est obsolète

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Définir une CSP stricte et statique côté serveur, jamais dynamique à partir d'entrées utilisateur
- Auditer régulièrement les pages legacy pour s'assurer qu'elles bénéficient des mêmes protections que les pages modernes