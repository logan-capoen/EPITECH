# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection de Null Byte — Accès à une sauvegarde développeur oubliée     |
| **Composant affecté**      | Endpoint FTP — `GET /ftp/`                                              |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Énumération de fichiers exposés
- Injection de Null Byte (`%2500`)

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Navigation sur `/ftp/` et exploitation du null byte |

### Étapes

1. **Découverte du fichier** — En naviguant sur `/ftp/`, on identifie un fichier `package.json.bak` — une sauvegarde du fichier de configuration des dépendances Node.js du projet.

2. **Identification de la restriction** — L'accès direct au fichier `.bak` retourne une erreur `403 Forbidden`. Seules les extensions `.md` et `.pdf` sont autorisées.

3. **Injection du Null Byte** — On applique la technique de double encodage URL du null byte pour contourner la validation d'extension :

4. **Confirmation de l'exploitation** — Le serveur retourne le contenu du fichier `package.json.bak` avec un code `200 OK`, exposant la liste complète des dépendances et leurs versions exactes.

---

### Preuve de concept

**Tentative directe — refusée :**
```
GET /ftp/package.json.bak HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 403 Forbidden
```

**Avec Poison Null Byte — succès :**
```
GET /ftp/package.json.bak%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 200 OK — contenu du package.json retourné
```

---

## Risques

### Impact

- **Cartographie complète de la stack technique** — versions exactes de toutes les dépendances (Express, Sequelize, JWT...) exposées
- **Aide à l'exploitation ciblée** — en croisant les versions avec des CVE connues , l'attaquant identifie précisément quelles vulnérabilités sont exploitables

---

## Correction

### Correctifs

- Ne jamais stocker de fichiers de sauvegarde (`.bak`, `.old`, `.backup`) dans un répertoire accessible publiquement via HTTP
- Appliquer le double décodage URL avant validation d'extension et rejeter tout null byte

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Stocker les sauvegardes dans un système de stockage isolé, non accessible via HTTP
- Ne jamais déployer en production des fichiers temporaires, de debug ou de sauvegarde