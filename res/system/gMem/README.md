Conception
==========

- Au moment de la création du contexte, appel à init_mem, qui créé la
liste chaînée avec un bloc libre faisant la taille totale du tas.
- Les blocs sont enregistrés dans une liste chaînée.
- A chaque gmalloc, first_fit permet de trouver le premier bloc de
taille suffisante, puis ce bloc est éventuellement découpé en deux blocs
dont un qui sera retiré de la liste dans tous les cas. Le bloc est alors
renvoyé à l'utilisateur.
- Les blocs sont triés dans l'ordre croissant des pointeurs, ce qui
favorise l'utilisation de first_fit.

Tests
=====

- Le test 0 vérifie que l'allocation d'une zone trop grande aboutit à un
pointeur NULL.
- Le test 1 vérifie que l'allocation et la désallocation d'une seule
zone mémoire fonctionnent correctement.
- Le test 2 fait la même chose sur deux zones allouées et vérifie que
les zones sont fusionnées après gfree.
- Le test 3 fait la même chose sur 10 variables, pendant un gros nombre
de tests (50000 allocations et désallocations effectuées dans un ordre
aléatoire).

