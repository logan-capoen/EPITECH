# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Données cachées — Stéganographie (LSB dans image PNG)                   |
| **Composant affecté**      | Assets publics — images du site (`/assets/public/images/`)              |
| **Sévérité**               | 🟢 Faible                                                               |

---

## Méthodologie

### Techniques utilisées
- OSINT
- Analyse stéganographique des assets publics

### Outils utilisés

| Outil        | Objectif                                                    |
|--------------|-------------------------------------------------------------|
| OpenStego    | Extraction de données cachées via algorithme RandomLSB      |
| Navigateur   | Téléchargement de l'ensemble des images du site             |

### Étapes

1. **Collecte des assets** — Téléchargement de toutes les images présentes sur le site.

2. **Analyse stéganographique** — Chaque image est analysée avec OpenStego en utilisant l'algorithme **RandomLSB** (Least Significant Bit) sans mot de passe.

3. **Extraction du contenu caché** — Le fichier `5.png` contient des données stéganographiées. La commande suivante permet d'extraire le contenu 

4. **Découverte** — Le fichier extrait est une image de **Pickle Rick**, confirmant la présence d'un Easter Egg caché dans les assets publics du site.

---

### Preuve de concept

```bash
java -jar lib/openstego.jar extract -a RandomLSB -sf /workspace/5.png -xd /workspace/output/ -p ""
```

---

## Risques

### Impact

- **Exfiltration de données potentielle** — la technique LSB peut être utilisée pour dissimuler des données sensibles (clés, credentials, messages) dans des images publiques
- **Canal de communication caché** — un attaquant ayant accès au serveur pourrait utiliser cette technique pour exfiltrer des données à travers des images en apparence anodines
---

## Correction

### Correctifs

- Analyser et retraiter les images uploadées ou stockées côté serveur pour supprimer les métadonnées et données cachées
- Mettre en place une détection stéganographique dans le pipeline d'upload d'images

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Normaliser systématiquement les images lors de l'upload (recompression, suppression des métadonnées)
- Surveiller les assets publics pour détecter des modifications anormales de fichiers images