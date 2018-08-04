?-op(50,fy,ne).
?-op(55,yfx,an).
?-op(60,yfx,or).
?-op(65,yfx,im).
?-op(70,yfx,eq).

laz(fa):-
  !.
laz(ne(P)):-
  istina(P).
laz(an(P,Q)):-
  laz(P).
laz(an(P,Q)):-
  laz(Q).
laz(or(P,Q)):-
  laz(P),
  laz(Q).
laz(im(P,Q)):-
  istina(P),
  laz(Q).
laz(eq(P,Q)):-
  istina(P),
  laz(Q).
laz(eq(P,Q)):-
  laz(P),
  istina(Q).

istina(tr):-
  !.
istina(ne(P)):-
  laz(P).
istina(an(P,Q)):-
  istina(P),
  istina(Q).
istina(or(P,Q)):-
  istina(P).
istuina(or(P,Q)):-
  istina(Q).
istina(im(P,Q)):-
  laz(P).
istina(im(P,Q)):-
  istina(P),
  istina(Q).
istina(eq(P,Q)):-
  laz(P),
  laz(Q).
istina(eq(P,Q)):-
  istina(P),
  istina(Q).

taut(F):-
  not(laz(F)).
