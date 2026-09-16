# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition d'endpoint caché — Encodage multi-couches (Base64 + ROT13 + URL) |
| **Composant affecté**      | Fichier `eastere.gg` — endpoint FTP                                     |
| **Sévérité**               | 🟢 Faible                                                               |

---

## Méthodologie

### Techniques utilisées
- Énumération de fichiers exposés
- Décodage multi-couches (Base64, ROT13, URL)

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Accès au fichier `eastere.gg` via null byte injection |
| CyberChef / Terminal | Décodage Base64, ROT13 et URL                   |

### Étapes

1. **Accès au fichier `eastere.gg`** — Via la technique de null byte injection documentée précédemment, on accède au contenu du fichier `eastere.gg` exposé dans `/ftp/`.

2. **Décodage Base64** — Le contenu du fichier est encodé en Base64. On le décode une première fois pour obtenir une chaîne intermédiaire.

3. **Décodage ROT13** — La chaîne obtenue est ensuite chiffrée par ROT13. On applique le déchiffrement ROT13 pour obtenir une URL encodée.

4. **Décodage URL** — Enfin, on décode l'URL encodée pour obtenir l'URL finale pointant vers un endpoint caché de l'application.

5. **Accès à l'endpoint final** — En naviguant sur l'URL reconstituée, on accède au contenu de l'Easter Egg imbriqué.

---

### Preuve de concept

**Étape 1 — Récupération du fichier :**
```
GET /ftp/eastere.gg%2500.md HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ contenu Base64
```

**Étape 2 — Décodage en chaîne :**
```bash
echo "<contenu_base64>" | base64 -d
echo "<résultat>" | tr 'A-Za-z' 'N-ZA-Mn-za-m'
python3 -c "import urllib.parse; print(urllib.parse.unquote('<résultat>'))"
```

**Résultat final :**
```
GET /the/devs/are/so/funny/they/hid/an/easter/egg/in/an/easter/egg HTTP/2
Host: ctf.juice.cyber.epitest.eu
```

---

## Risques

### Impact

- **Sécurité par l'obscurité inefficace** — les encodages en cascade (Base64, ROT13) ne sont pas des mécanismes de chiffrement et sont  réversibles
- **Exposition d'endpoints non documentés** — des ressources ou fonctionnalités non prévues pour le public peuvent être accessibles
- **Mauvaise pratique de développement** — dissimuler des chemins sensibles dans des fichiers encodés

---

## Correction

### Correctifs

- Supprimer tout endpoint ou fichier non destiné à la production de l'environnement accessible
- Ne pas stocker de chemins ou d'URLs sensibles dans des fichiers accessibles publiquement, même encodés
- Protéger les endpoints sensibles par une authentification forte plutôt que par l'obscurité

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Ne jamais considérer Base64 ou ROT13 comme des mécanismes de sécurité, ce sont des encodages, pas des chiffrements
