# Rapport de Vulnérabilité

## Vulnérabilité

| Champ                      | Détails                                             |
|----------------------------|-----------------------------------------------------|
| **Type**                   | ex. Injection SQL / XSS / Mauvaise configuration    |
| **Composant affecté**      | ex. Système d'authentification, Base de données     |
| **Sévérité**               | 🔴 Critique / 🟠 Élevée / 🟡 Moyenne / 🟢 Faible   |

---

## Méthodologie

### Techniques utilisées
- [ ] OSINT
- [ ] Énumération
- [ ] Scan
- [ ] Force brute
- [ ] Tests manuels
- [ ] Autre : ___

### Outils utilisés
| Outil        | Objectif                              |
|--------------|---------------------------------------|
| Burp Suite   | Interception du trafic HTTP           |
| SQLmap       | Détection d'injections SQL            |
| Nmap         | Scan des ports et services            |
| *...*        | *...*                                 |

### Étapes

1. **Titre de l'étape** — description de ce qui a été effectué
2. **Titre de l'étape** — description de ce qui a été effectué
3. **Titre de l'étape** — description de ce qui a été effectué

---

### Preuve de concept
```http
GET /endpoint-vulnerable?id=1' OR '1'='1 HTTP/1.1
Host: cible.com
```

> ⚠️ *Inclure ici les captures d'écran, charges utiles ou journaux*

---

## Risques

### Impact
- Fuite ou exposition de données sensibles
- Atteinte à la réputation
- Violation réglementaire / de conformité (RGPD, PCI-DSS…)
- Perte financière

---

## Correction

### Correctifs

- Action 1
- Action 2

### Bonnes pratiques de sécurité recommandées
- Suivre les directives OWASP Top 10
- Mettre en place une validation des entrées et un encodage des sorties
- Réaliser des audits de sécurité et des tests d'intrusion réguliers
- ...