# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection de Null Byte — Contournement de validation d'extension        |
| **Composant affecté**      | Endpoint FTP — `GET /ftp/`                                              |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Énumération de fichiers exposés
- Injection de Null Byte (`%2500`)

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Navigation sur l'endpoint FTP et test du contournement |

### Étapes

1. **Découverte de l'endpoint FTP** — En énumérant les répertoires de l'application, on découvre un endpoint `/ftp/` listant des fichiers accessibles publiquement.

2. **Identification de la restriction** — En tentant d'accéder directement au fichier `eastere.gg`, le serveur refuse la requête. Seuls les fichiers avec une extension `.md` ou `.pdf` sont autorisés.

3. **Analyse du mécanisme de validation** — La vérification de l'extension est effectuée côté serveur en lisant le nom du fichier fourni dans l'URL. Elle ne tient pas compte des caractères nuls encodés.

4. **Injection du Null Byte** — En ajoutant `%2500.md` à la fin du nom de fichier, le serveur voit l'extension `.md` et autorise la requête, mais le système de fichiers tronque le nom au niveau du caractère nul et ouvre `eastere.gg`.

5. **Confirmation de l'exploitation** — Le fichier `eastere.gg` est retourné par le serveur.

---

### Preuve de concept

**Tentative directe — refusée :**
```
GET /ftp/eastere.gg HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 403 Forbidden
```

**Avec injection Null Byte — succès :**
```
GET /ftp/eastere.gg%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 200 OK — contenu de eastere.gg retourné
```

---

## Risques

### Impact

- **Contournement du contrôle d'accès sur les fichiers** — n'importe quel fichier présent dans `/ftp/` est accessible quel que soit son extension
- **Exposition de fichiers sensibles** — des fichiers de configuration, clés, ou données internes pourraient être exfiltrés de la même manière
- **Surface d'attaque élargie** — si d'autres répertoires sont accessibles via le même mécanisme, la fuite peut être bien plus large

---

## Correction

### Correctifs

- Décoder complètement l'URL avant toute validation d'extension
- Rejeter toute requête contenant un caractère nul (`\x00` / `%00`) dans le nom de fichier
- Utiliser une liste blanche stricte de fichiers autorisés plutôt qu'une validation par extension

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais construire un chemin de fichier à partir d'une entrée utilisateur sans sanitisation complète
