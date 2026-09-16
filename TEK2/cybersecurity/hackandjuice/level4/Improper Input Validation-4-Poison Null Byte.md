# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Poison Null Byte — Contournement de validation d'extension de fichier   |
| **Composant affecté**      | Endpoint FTP — `GET /ftp/`                                              |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Injection de Null Byte (`%2500`)
- Énumération de fichiers exposés

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Accès direct à l'endpoint et test du payload      |

### Étapes

1. **Découverte de l'endpoint FTP** — En naviguant sur `/ftp/`, on obtient la liste des fichiers présents sur le serveur, dont certains avec des extensions non autorisées (`.gg`, `.bak`, etc.).

2. **Identification de la restriction** — L'accès direct à un fichier non `.md` ou `.pdf` retourne une erreur `403 Forbidden`. La validation de l'extension est effectuée côté serveur sur le nom de fichier brut de l'URL.

3. **Construction du payload Null Byte** — On encode un caractère nul en double encodage URL : `%00` devient `%2500` (`%25` étant l'encodage URL du caractère `%`). On l'insère entre le nom du fichier cible et une fausse extension autorisée :
   ```
   eastere.gg%2500.md
   ```

4. **Exploitation** — Le serveur de validation décode l'URL une fois et voit `eastere.gg%00.md` → extension `.md` valide . Le système de fichiers décode à son tour et tronque la chaîne au null byte → ouvre `eastere.gg` .

5. **Confirmation** — Le fichier est retourné avec un code `200 OK`.

---

### Preuve de concept

**Sans null byte — refusé :**
```
GET /ftp/eastere.gg HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 403 Forbidden
```

**Avec Poison Null Byte — succès :**
```
GET /ftp/eastere.gg%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 200 OK
```

---

## Risques

### Impact

- **Contournement total du filtre d'extension** — tout fichier présent dans `/ftp/` est accessible quelle que soit son extension
- **Accès à des fichiers sensibles** — sauvegardes (`.bak`), fichiers de configuration, données internes
- **Exfiltration de données** — des informations confidentielles peuvent être récupérées sans authentification

---

## Correction

### Correctifs

- Appliquer un double décodage URL avant toute validation d'extension
- Rejeter explicitement toute requête contenant un null byte (`%00`, `%2500`, `\x00`)
- Utiliser une liste blanche de fichiers autorisés plutôt qu'une validation par extension

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais construire un chemin de fichier à partir d'une entrée utilisateur sans sanitisation complète