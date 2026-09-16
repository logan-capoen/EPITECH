# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Contournement d'Allowlist — Open Redirect                               |
| **Composant affecté**      | Endpoint `GET /redirect?to=`                                            |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Analyse du code source JavaScript (`main.js`)
- Contournement de validation d'URL par injection de paramètre

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur / DevTools | Lecture du `main.js` pour extraire l'allowlist |
| Navigateur         | Test du payload de contournement                  |

### Étapes

1. **Identification de l'endpoint** — L'application utilise un endpoint de redirection `/redirect?to=` pour tous les liens externes. Une validation côté serveur vérifie que l'URL cible est dans une allowlist.

2. **Extraction de l'allowlist** — En fouillant le fichier `main.js`, on identifie la liste complète des URLs autorisées :
   - `https://github.com/juice-shop/juice-shop`
   - `https://blockchain.info/address/...`
   - `https://etherscan.io/address/...`

3. **Analyse du mécanisme de validation** — Le serveur vérifie que la valeur du paramètre `to` **contient** une URL de l'allowlist, sans vérifier qu'elle **commence** par celle-ci.

4. **Construction du payload** — On forge une URL vers une destination arbitraire (`http://kimminich.de`) en y ajoutant une URL de l'allowlist comme paramètre GET :
   ```
   http://kimminich.de?pwned=https://github.com/juice-shop/juice-shop
   ```
   Le serveur trouve l'URL allowlistée dans la chaîne et valide la redirection.

5. **Confirmation** — L'utilisateur est redirigé vers `http://kimminich.de` au lieu d'une URL autorisée.

---

### Preuve de concept

**Redirection légitime :**
```
GET /redirect?to=https://github.com/juice-shop/juice-shop HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ Redirection vers GitHub ✅
```

**Contournement de l'allowlist :**
```
GET /redirect?to=http://kimminich.de?pwned=https://github.com/juice-shop/juice-shop HTTP/2
Host: ctf.juice.cyber.epitest.eu
→ Redirection vers kimminich.de ✅ (domaine non autorisé)
```

---

## Risques

### Impact

- **Open Redirect** — un attaquant peut forger un lien en apparence légitime (`ctf.juice.cyber.epitest.eu/redirect?to=...`) qui redirige vers un site malveillant
- **Phishing** — la victime voit un domaine de confiance dans l'URL avant de cliquer, augmentant le taux de succès de l'attaque
- **Contournement de CSP/CORS** — dans certains contextes, un open redirect peut être utilisé pour contourner des restrictions de sécurité
- **Vol de tokens** — si des paramètres sensibles sont transmis via l'URL de redirection, ils peuvent être exfiltrés vers le domaine attaquant

---

## Correction

### Correctifs

- Passer par une vérification stricte du domaine via parsing d'URL
- Ne jamais exposer l'allowlist dans le main.js

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Préférer des identifiants opaques aux URLs directes pour les redirections externe