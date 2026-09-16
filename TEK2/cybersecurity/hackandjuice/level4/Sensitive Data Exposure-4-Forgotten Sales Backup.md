# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Injection de Null Byte — Accès à un fichier de sauvegarde oublié        |
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
| Navigateur         | Navigation sur l'endpoint FTP et test du contournement |

### Étapes

1. **Découverte de l'endpoint FTP** — En énumérant les répertoires de l'application, on découvre un endpoint `/ftp/` listant des fichiers accessibles publiquement, parmi lesquels un fichier de sauvegarde `coupons_2013.md.bak`.

2. **Identification de la restriction** — En tentant d'accéder directement au fichier `.bak`, le serveur refuse la requête. Seuls les fichiers avec une extension `.md` ou `.pdf` sont autorisés.

3. **Injection du Null Byte** — En ajoutant `%2500.md` à la fin du nom de fichier, le serveur valide l'extension `.md` et autorise la requête, mais le système de fichiers tronque le nom au niveau du null byte et retourne le vrai fichier `.bak`.

4. **Confirmation de l'exploitation** — Le fichier de sauvegarde est retourné par le serveur, exposant potentiellement des données de ventes historiques ou des coupons de réduction.

---

### Preuve de concept

**Tentative directe — refusée :**
```
GET /ftp/coupons_2013.md.bak HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 403 Forbidden
```

**Avec injection Null Byte — succès :**
```
GET /ftp/coupons_2013.md.bak%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 200 OK — contenu du fichier .bak retourné
```

---

## Risques

### Impact

- **Exposition de données commerciales sensibles** — codes de réduction, historique de ventes, données clients potentiellement présentes dans la sauvegarde
- **Abus des codes promotionnels** — si le fichier contient des coupons valides, ils peuvent être exploités frauduleusement
- **Contournement du contrôle d'accès** — même vulnérabilité que l'Easter Egg, applicable à tous les fichiers non `.md`/`.pdf` du répertoire `/ftp/`

---

## Correction

### Correctifs

- Décoder complètement l'URL (double décodage) avant toute validation d'extension :
- Rejeter toute requête contenant un caractère nul (`\x00` / `%00`) dans le nom de fichier
- **Ne jamais exposer des fichiers de sauvegarde** (`.bak`, `.old`, `.backup`) dans un répertoire accessible publiquement

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Stocker les sauvegardes en dehors de la racine web, dans un répertoire non accessible via HTTP