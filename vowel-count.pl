is_vowel(a).
is_vowel(e).
is_vowel(i).
is_vowel(o).
is_vowel(u).

vowel_count(String, Total) :-
  string_chars(String, Chars),
  vowel_count_aux(Chars, Total).

vowel_count_aux([Ch | Rest], Total) :-
  is_vowel(Ch),
  vowel_count_aux(Rest, Vowels),
  Total is Vowels + 1.

vowel_count_aux([_ | Rest], Total) :- vowel_count_aux(Rest, Total).

vowel_count_aux([], 0).
