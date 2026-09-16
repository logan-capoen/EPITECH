# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | GDPR Data Theft — Collision d'obfuscation d'email                       |
| **Composant affecté**      | Interface d'administration — Customer Feedbacks + Système d'obfuscation  |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Analyse du mécanisme d'obfuscation
- Création de compte avec collision volontaire

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| Navigateur         | Observation des feedbacks dans le panneau admin et création du compte collision |

### Étapes

1. **Observation de l'obfuscation** — Dans le panneau d'administration, les adresses email des auteurs de feedbacks sont partiellement masquées — les 3 premiers caractères sont remplacés par `***` :
   ```
   ***@juice-sh.op
   ***in@juice-sh.op
   ```

2. **Identification de la faiblesse** — L'obfuscation ne masque que les 3 premiers caractères du nom d'utilisateur. 

3. **Construction de l'email collision** — En créant un compte dont les caractères à partir du 4ème correspondent exactement à ceux d'une victime, l'obfuscation produit le même résultat pour les deux comptes.

4. **Accès aux données de la victime** — La collision d'obfuscation permet à l'attaquant d'être confondu avec la victime dans l'interface, donnant potentiellement accès à ses données personnelles affichées.

---

### Preuve de concept

**Email victime :**
```
admin@juice-sh.op → affiché : ***in@juice-sh.op
```

**Email de collision créé :**
```
xyzin@juice-sh.op → affiché : ***in@juice-sh.op  ← identique
```

**Résultat :**
```
Les deux comptes produisent le même affichage obfusqué.
L'interface ne peut plus distinguer les deux utilisateurs,
permettant une confusion d'identité et un accès aux données de la victime.
```

---

## Risques

### Impact

- **Violation du RGPD** — accès non autorisé aux données personnelles d'un autre utilisateur
- **Usurpation d'identité** — l'attaquant peut se faire passer pour la victime dans l'interface
- **Fuite de données personnelles** — historique de commandes, adresse, informations de profil potentiellement exposés
- **Perte de confiance** — un mécanisme censé protéger la vie privée devient un vecteur d'attaque

---

## Correction

### Correctifs

- Augmenter significativement le nombre de caractères masqués, ou utiliser un masquage basé sur un pourcentage de la longueur totale :
- Ne pas afficher les emails même partiellement dans des interfaces accessibles — utiliser un identifiant anonyme à la place

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10
- Traiter l'obfuscation comme une mesure d'affichage uniquement, jamais comme un contrôle de sécurité ou d'identité
- Appliquer les principes RGPD de minimisation des données — n'afficher que ce qui est strictement nécessaire
- Ne jamais utiliser des données obfusquées comme base de comparaison ou d'identification côté serveur