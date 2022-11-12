sum_digits_aux(0, 0).

sum_digits_aux(Number, Result) :-
  Rest is Number div 10,
  sum_digits_aux(Rest, RestSum),
  Result is RestSum + Number mod 10.

sum_digits(Number, Result) :-
  abs(Number, Positive),
  sum_digits_aux(Positive, Result).
