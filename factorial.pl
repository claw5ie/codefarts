factorial(0, 1).

factorial(N, R) :-
  Prev is N - 1,
  factorial(Prev, PrevR),
  R is PrevR * N.
