# Sécurité du Projet

La sécurité est au cœur de la conception de notre plateforme. En complément de notre conformité RGPD, nous avons mis en place des mécanismes stricts pour garantir l'intégrité des données, empêcher l'usurpation d'identité et sécuriser l'accès de chaque utilisateur.

---

## Authentification sécurisée par OTP (One-Time Password)

Pour empêcher quiconque d'utiliser ou d'inscrire l'adresse e-mail d'une autre personne à son insu, la création de compte et la connexion s'appuient sur un système de vérification à double facteur par jeton unique (OTP).

* **Validation de propriété :** Lors de la demande d'accès, un code temporaire unique est généré et envoyé exclusivement sur l'adresse e-mail saisie.
* **Preuve de détention :** L'utilisateur doit obligatoirement récupérer ce code dans sa boîte de réception pour valider son action. Cela garantit que seul le véritable détenteur de l'adresse e-mail peut activer ou accéder au compte.

---

## Résolution de la faille de sécurité : Passage aux jetons d'authentification (Tokens)

Dans les premières versions du projet, l'adresse e-mail de l'utilisateur était transmise directement en clair dans les paramètres de l'URL (Query Parameters). Cette méthode présentait un risque critique d'usurpation d'identité, car n'importe qui pouvait modifier l'adresse e-mail dans l'URL pour accéder aux données d'un tiers.

### La solution implémentée
Nous avons corrigé cette vulnérabilité en remplaçant l'exposition des e-mails par un système de **`tokenAuth` personnel** :

1. **Anonymisation des requêtes :** L'adresse e-mail n'apparaît plus jamais dans les URLs de navigation ou de désabonnement.
2. **Génération d'un token unique :** Chaque utilisateur se voit attribuer un identifiant de session chiffré et aléatoire (`tokenAuth`).
3. **Vérification opaque :** Les workflows de n8n valident le `tokenAuth` en base de données pour identifier l'utilisateur de manière sécurisée, rendant toute tentative de manipulation d'URL totalement inoffensive.

---

## Bonnes pratiques et étanchéité des données

* **Fichier d'environnement isolé :** Toutes les variables sensibles (mots de passe d'application Gmail, clés API Gemini, GNews et NewsAPI) sont stockées en dehors du code dans le fichier `.env`.