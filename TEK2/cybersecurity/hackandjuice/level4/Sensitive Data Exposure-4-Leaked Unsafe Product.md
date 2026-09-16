# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| **Type**                   | Exposition de données supprimées + Injection HTML dans un champ produit |
| **Composant affecté**      | Base de données — Table `Products` (produit `id: 11` soft-deleted)      |
| **Sévérité**               | 🟠 Élevée                                                               |

---

## Méthodologie

### Techniques utilisées
- Exfiltration de base de données (via SQLi précédemment documentée)
- OSINT — recherche sur les ingrédients des fruits listés

### Outils utilisés

| Outil              | Objectif                                          |
|--------------------|---------------------------------------------------|
| SQLmap / SQLi manuelle | Dump de la table `Products` incluant les entrées soft-deleted |
| Recherches OSINT   | Identification des propriétés dangereuses des fruits listés  |

### Étapes

1. **Dump de la table `Products`** — Via l'injection SQL documentée précédemment, on exfiltre l'intégralité de la table `Products`.

2. **Découverte du produit supprimé** — Le produit `id: 11` — *"Rippertuer Special Juice"* — apparaît dans le dump avec `deletedAt: 2026-02-24`. Il n'est plus visible dans l'interface mais reste présent en base.

3. **Analyse de la description** — La description contient du **HTML injecté** directement dans le champ texte :
   ```html
   <br/><span style="color:red;">This item has been made unavailable because of lack of safety standards.</span> (This product is unsafe! We plan to remove it from the stock!)
   ```

4. **Recherche OSINT sur les ingrédients** — Les fruits listés dans la description sont identifiés comme potentiellement dangereux :
   - **Cherimoya** (*Annona cherimola*) — les graines contiennent de l'annonacine, neurotoxine liée à des syndromes parkinsoniens atypiques
   - **Jabuticaba** (*Myrciaria cauliflora*) — fermentation rapide produisant des composés potentiellement toxiques à haute dose
   - **Bael** (*Aegle marmelos*) — peut interagir avec certains médicaments et provoquer des effets indésirables

5. **Confirmation** — Le produit a été retiré de la vente pour non-respect des normes de sécurité alimentaire, mais ses données restent accessibles en base via l'injection SQL.

---

### Preuve de concept

**Données extraites via SQLi :**
```json
{
  "id": 11,
  "name": "Rippertuer Special Juice",
  "description": "Contains a magical collection of the rarest fruits gathered from all around the world, like Cherymoya Annona cherimola, Jabuticaba Myrciaria cauliflora, Bael Aegle marmelos... and others, at an unbelievable price! <br/><span style=\"color:red;\">This item has been made unavailable because of lack of safety standards.</span> (This product is unsafe! We plan to remove it from the stock!)",
  "price": 16.99,
  "deletedAt": "2026-02-24 09:49:24.767 +00:00"
}
```

---

## Risques

### Impact

- **Exposition de données supprimées** — un soft-delete ne protège pas contre l'exfiltration par injection SQL
- **Risque sanitaire** — des informations sur un produit retiré pour raisons de sécurité sont encore accessibles et pourraient être exploitées
- **Responsabilité légale** — la conservation de données sur un produit dangereux en base peut engager la responsabilité de l'entreprise

---

## Correction

### Correctifs

- Remplacer le soft-delete par une **anonymisation ou suppression physique** des données sensibles une fois le produit retiré
- Corriger l'injection SQL qui permet d'accéder aux données soft-deleted 

### Bonnes pratiques de sécurité recommandées

- Suivre les directives OWASP Top 10 
- Appliquer le principe de minimisation des données, ne conserver que ce qui est strictement nécessaire
- Valider et encoder toutes les entrées utilisateur avant persistance en base de données
- Mettre en place une politique de rétention et de suppression définitive des données sensibles