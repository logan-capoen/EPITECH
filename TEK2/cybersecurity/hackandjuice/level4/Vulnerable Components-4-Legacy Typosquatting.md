# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Typosquatting — Dépendance npm malveillante (`epilogue-js`)             |
| **Composant affecté**      | Fichier `package.json.bak` — dépendance `epilogue-js`                   |
| **Sévérité**               | 🔴 Critique                                                             |

---

## Méthodologie

### Techniques utilisées
- Analyse du fichier `package.json.bak` récupéré via null byte injection
- Vérification manuelle des dépendances sur npmjs.com

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Accès à `package.json.bak` via null byte et vérification sur npmjs.com |

### Étapes

1. **Récupération du `package.json.bak`** — Via la technique de null byte injection documentée précédemment, on accède au fichier `package.json.bak` exposé dans `/ftp/`, qui liste l'ensemble des dépendances du projet.

2. **Vérification des dépendances sur npm** — On vérifie manuellement la disponibilité de chaque dépendance sur `npmjs.com` pour détecter d'éventuelles anomalies.

3. **Découverte du typosquatting** — La dépendance `epilogue-js` existe bien sur npm, mais affiche un message explicite :
   ```
   THIS IS NOT THE MODULE YOU ARE LOOKING FOR
   ```
   Le vrai package utilisé par l'application est `epilogue` (sans le suffixe `-js`). `epilogue-js` est un package imposteur enregistré par un tiers pour piéger les développeurs qui tapent le mauvais nom.

4. **Confirmation** — L'application référence `epilogue-js` dans ses dépendances au lieu de `epilogue`, ce qui signifie qu'elle installe potentiellement un package tiers non vérifié.

---

### Preuve de concept

**Dans `package.json.bak` :**
```json
{
  "dependencies": {
    "epilogue-js": "^0.3.6",
    ...
  }
}
```

**Vérification sur npm :**
```
https://www.npmjs.com/package/epilogue-js
→ "THIS IS NOT THE MODULE YOU ARE LOOKING FOR"
```

**Le vrai package :**
```
https://www.npmjs.com/package/epilogue
→ Package légitime REST endpoint library pour Sequelize
```


---

## Risques

### Impact

- **Exécution de code malveillant** — un package typosquatté peut contenir du code exécuté lors de `npm install` (scripts `postinstall`) ou au runtime
- **Compromission de la chaîne d'approvisionnement** — toute l'application et son infrastructure peuvent être compromises via une seule dépendance malveillante
- **Vol de données** — des credentials, tokens ou données sensibles peuvent être exfiltrés silencieusement
- **Persistance** — un package malveillant peut installer des backdoors ou des reverse shells sur le serveur de build ou de production

---

## Correction

### Correctifs

- Remplacer `epilogue-js` par `epilogue` dans le `package.json` :

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Vérifier systématiquement l'authenticité des packages npm avant de les ajouter comme dépendance
