# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition d'advisory de sécurité — Dépendance vulnérable non corrigée (`express-jwt`) |
| **Composant affecté**      | Fichier `security.txt` — endpoint `/.well-known/`                |
| **Sévérité**               | 🟡 Moyenne                                                              |

---

## Méthodologie

### Techniques utilisées
- OSINT
- Énumération de fichiers exposés

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Navigation manuelle sur les endpoints exposés     |

### Étapes

1. **Découverte du `security.txt`** — En naviguant sur `https://ctf.juice.cyber.epitest.eu/.well-known/security.txt`, on trouve une référence vers le répertoire CSAF de l'application.

2. **Exploration du CSAF** — En accédant à `https://ctf.juice.cyber.epitest.eu/.well-known/csaf`, on découvre des fichiers d'advisory de sécurité au format CSAF contenant des checksums SHA256 pour vérifier l'intégrité des advisories.

3. **Identification de la vulnérabilité** — Parmi les advisories listés, celui concernant `express-jwt` est marqué comme **"still pending"**, indiquant une vulnérabilité connue non encore corrigée dans la dépendance utilisée par l'application.

4. **Confirmation** — La présence de cet advisory public confirme que l'application tourne avec une version vulnérable d'`express-jwt` et que la correction n'a pas encore été appliquée.

---

### Preuve de concept

**Étape 1 — Accès au `security.txt` :**
```
GET /.well-known/security.txt HTTP/2
Host: ctf.juice.cyber.epitest.eu
```

**Étape 2 — Exploration du CSAF :**
```
GET /.well-known/csaf HTTP/2
Host: ctf.juice.cyber.epitest.eu
```

**Étape 3 — Advisory `express-jwt` :**
```
GET /.well-known/csaf/<advisory-express-jwt>.json HTTP/2
Host: ctf.juice.cyber.epitest.eu
```

---

## Risques

### Impact

- **Exposition de la surface d'attaque** — les advisories CSAF publient les vulnérabilités non corrigées, guidant un attaquant vers les cibles les plus exploitables
- **Exploitation de `express-jwt`** — selon la CVE associée, une version vulnérable d'`express-jwt` peut permettre un contournement d'authentification JWT
- **Compromission de l'authentification** — si la vulnérabilité est exploitée, des tokens JWT forgés peuvent être acceptés comme valides par le serveur

---

## Correction

### Correctifs

- Mettre à jour `express-jwt` vers la dernière version corrigée dès que le patch est disponible
- Surveiller activement le statut des advisories publiés dans le CSAF et traiter les vulnérabilités "pending" en priorité
- Restreindre l'accès au répertoire `/.well-known/csaf` si les advisories contiennent des informations sensibles sur les vulnérabilités non corrigées

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Mettre en place un outil de suivi des dépendances vulnérables
- Ne jamais exposer publiquement le statut de vulnérabilités non corrigées dans des fichiers accessibles sans authentification
- Appliquer une politique de mise à jour régulière des dépendances tierces