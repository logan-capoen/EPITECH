# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Composant vulnérable — XSS via `sanitize-html` 1.4.2                   |
| **Composant affecté**      | Dépendance npm `sanitize-html` — version `1.4.2`                        |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Analyse du fichier `package.json.bak` récupéré via null byte injection
- Recherche de CVE sur les versions de dépendances identifiées

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Accès à `package.json.bak` via null byte et recherche de CVE |
| npmjs.com / Snyk   | Identification des vulnérabilités connues de `sanitize-html` 1.4.2 |

### Étapes

1. **Récupération du `package.json.bak`** — Via la technique de null byte injection documentée précédemment, on accède au fichier `package.json.bak` et on identifie la version exacte de `sanitize-html` utilisée : `1.4.2`.

2. **Recherche de vulnérabilités** — En croisant la version `1.4.2` avec les bases de CVE, on identifie que cette version contient une vulnérabilité permettant de bypasser la sanitisation et d'injecter du code XSS.

3. **Analyse du bypass** — La version `1.4.2` ne gère pas correctement certains patterns HTML imbriqués ou des attributs spécifiques, permettant à du code JavaScript malveillant de passer à travers la sanitisation.

4. **Impact** — Tout champ de l'application qui utilise `sanitize-html` pour filtrer les entrées utilisateur avant affichage est potentiellement vulnérable à une attaque XSS stockée.

---

### Preuve de concept

**Dans `package.json.bak` :**
```json
{
  "dependencies": {
    "sanitize-html": "1.4.2",
    ...
  }
}
```

**Payload XSS bypassant sanitize-html 1.4.2 :**
```html
<<img src=""/>alert('XSS')>
```
ou
```html
<p onclick="alert('XSS')">cliquez ici</p>
```

---

## Risques

### Impact

- **XSS stocké** — du code JavaScript malveillant peut être persisté en base et exécuté dans le navigateur de chaque visiteur
- **Vol de session** — les cookies de session (`document.cookie`) peuvent être exfiltrés vers un serveur attaquant
- **Phishing in-app** — injection de faux formulaires de login dans les pages de l'application
- **Propagation** — un XSS dans un espace admin peut compromettre l'ensemble de la plateforme
- **Défiguration** — modification visuelle de l'application pour tous les utilisateurs

---

## Correction

### Correctifs

- Mettre à jour `sanitize-html` vers la dernière version corrigée :
- Vérifier dans `package.json` que la version est bien mise à jour :
- Auditer les autres dépendances avec `npm audit` pour détecter d'autres vulnérabilités similaires

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Ne jamais fixer les versions de dépendances à une version majeure ancienne sans suivi actif des CVE
- Appliquer une politique de mise à jour régulière des dépendances dans le cycle de développement