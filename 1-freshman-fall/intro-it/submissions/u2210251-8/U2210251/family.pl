male(james1).
male(charles1).
male(charles2).
male(james2).
male(george1).

female(catherine).
female(elizabeth).
female(sophia).

parent(charles1 , james1).
parent(elizabeth , james1).
parent(charles2 , charles1).
parent(catherine , charles1).
parent(james2 , charles1).
parent(sophia , elizabeth).
parent(george1 , sophia).

mother(X):-
  parent(_,X),
  female(X).

father(X):-
  parent(_,X),
  male(X).

sibling(X,Y):-
  parent(X,Z),
  parent(Y,Z),
  X\=Y.

brother(X,Y):-
  parent(X,Z),
  parent(Y,Z),
  male(Y),
  X\=Y.

sister(X,Y):-
  parent(X,Z),
  parent(Y,Z),
  female(Y),
  X\=Y.

mohter(X,Y):-
  parent(X,Y),
  female(Y).
  
father(X,Y):-
  parent(X,Y),
  male(Y).

grandfather(X,Y):-
  parent(Z,X),
  parent(Y,Z),
  male(X).

grandmother(X,Y):-
  parent(Z,X),
  parent(Y,Z),
  female(X).

nephew(X,Y):-
  parent(X,Z),
  parent(Y,W),
  sibling(Z,W).
  male(Y).

niece(X,Y):-
  parent(X,Z),
  parent(Y,W),
  sibling(Z,W).
  female(Y).
