h1. Conception

- Au moment de la création du contexte, appel à init_mem, qui créé la
liste chaînée avec un bloc libre faisant la taille totale du tas.
- Les blocs sont enregistrés dans une liste chaînée circulaire.
- A chaque gmalloc, first_fit permet de trouver le premier bloc de
taille suffisante, puis ce bloc est éventuellement découpé en deux blocs
dont un qui sera retiré de la liste dans tous les cas. Le bloc est alors
renvoyé à l'utilisateur.


