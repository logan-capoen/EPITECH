# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection de Null Byte — Accès à un fichier de signature mal placé      |
| **Composant affecté**      | Endpoint FTP — `GET /ftp/suspicious_errors.yml`                         |
| **Sévérité**               | 🟠 Élevée                                                               |

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

1. **Découverte du fichier** — En naviguant sur `/ftp/`, on identifie un fichier `suspicious_errors.yml` — un fichier de configuration ou de signature qui n'a pas sa place dans un répertoire accessible publiquement.

2. **Identification de la restriction** — L'accès direct au fichier `.yml` retourne une erreur `403 Forbidden`. Seules les extensions `.md` et `.pdf` sont autorisées.

3. **Injection du Null Byte** — On applique la technique de double encodage URL du null byte pour contourner la validation d'extension

4. **Confirmation de l'exploitation** — Le serveur retourne le contenu du fichier `suspicious_errors.yml` avec un code `200 OK`, exposant son contenu.

---

### Preuve de concept

**Tentative directe — refusée :**
```
GET /ftp/suspicious_errors.yml HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 403 Forbidden
```

**Avec Poison Null Byte — succès :**
```
GET /ftp/suspicious_errors.yml%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 200 OK — contenu du fichier retourné
```

---

## Risques

### Impact

- **Exposition de fichiers de configuration internes** — un fichier `.yml` peut contenir des signatures d'erreurs, des règles de monitoring, des credentials ou des détails d'infrastructure
- **Aide à la reconnaissance** — les informations contenues facilitent l'identification de nouvelles surfaces d'attaque
- **Fichier mal placé** — sa présence dans `/ftp/` indique une mauvaise gestion des fichiers de configuration en production

---

## Correction

### Correctifs

- Retirer immédiatement le fichier `suspicious_errors.yml` du répertoire `/ftp/` et le placer dans un répertoire non accessible via HTTP
- Appliquer le double décodage URL et rejeter tout null byte avant validation d'extension

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Ne jamais stocker de fichiers de configuration, signature ou monitoring dans des répertoires accessibles publiquement
- Mettre en place un processus de revue des déploiements pour s'assurer qu'aucun fichier sensible n'est exposé accidentellement