--[[

Zadatak:

U dve koverte se nalaze dve sume novca (dva pozitivna razlicita broja, neogranicena)
Igrac bira jednu kovertu, otvara je i ima pravo da se predomisli.
Da li postoji ikakva strategija koja nudi vise od 0.5 verovatnoce da se uzme veci iznos.

Resenje:

Neka su u iznosi u kovertama A i B, a i b, i pretpostavimo da je a > b.
Uvedimo funkciju f(x) koja daje verovatnocu (x > 0, kodomen funkcije je [0, 1]) promene koverte.
Izracunajmo sada verovatnocu da smo izabrali vecu sumu:

P(izabran A) = P(prvo izabran A)*(1-f(a)) + P(prvo izabran b)*f(b)

Ako je prvo izabran A, onda f(a) oznacava verovatnocu promene, a 1-f(a) verovatnocu zadrzavanja koverte.
Bitno je da je ova jednacina gore tacna.

Na sta se svodi, P(prvog izbora) je uvek 0.5, tu nemamo uticaja.

P(izabran A) = 0.5*(1-f(a)) + 0.5*f(b)

Mi trazimo da P(izabran A) bude veci od 0.5.
Dakle:

0.5*(1-f(a)) + 0.5*f(b) > 0.5 (pomnozimo sa 2)
1-f(a)+f(b) > 1 (oduzmimo 1)
-f(a)+f(b) > 0 (dodajmo f(a))
f(b) > f(a)

Hm, stanimo ovde i razmislimo, znamo da vazi a > b i f(b) > f(a).
Znaci ako je nasa funkcija izbora opadajuca, onda ce ukupna verovatnoca biti strogo veca od 0.5.

Recimo lep izbor funkcije je 1/(x+1), vazi za svako pozitivno x, kako je x+1 vece od 1, rezultat ce biti
u [0, 1]. A da je opadajuca ... izvod je -1/(x+1)^2 sto je negativno uvek, prekid je na -1, pa ne utice.

Optimizacija:

Ako funkciju ispravimo u a/(x+a) dobicemo i dalje da zadovoljava, ali veca je verovatnoca (bolje raspodeljeno).

Simulacija:

N - broj serija za racunanje verovatnoce.
M - maksimalan broj koji se moze naci u kovertama (uslovi zadatka su da nema ogranicanje,
    ali budimo realni :).

Za funkciju cemo uzeti f(x) = M/(x+M)

--]]

N = 10000000
M = 100000

function random()
  local r
  repeat
    r = math.random()*M
  until r > 0
  return r
end

function fill_envelopes()
  local a = random()
  local b
  repeat
    b = random()
  until b ~= a
  return a, b
end

function f_M(x)
  return M/(x+M)
end

function f_1(x)
  return 1/(x+1)
end

function simulation(a, b, f)
  local best = math.max(a, b)
  local selected
  local other

  -- slucajno biramo a ili b
  if math.random() > 0.5 then
    selected = a
    other = b
  else
    selected = b
    other = a
  end

  -- ako je slucajan broj manji od funkcije za izabranu vrednost, menjamo
  if math.random() < f(selected) then
    selected, other = other, selected
  end

  -- vracamo da li je "pobedio"
  return selected == best
end

function first(a, b)
  local best = math.max(a, b)
  return a == best
end

function second(a, b)
  local best = math.max(a, b)
  return b == best
end

math.randomseed(os.time())
simulation_1_count = 0
simulation_m_count = 0
first_count = 0
second_count = 0

for i = 1, N do
  local a, b = fill_envelopes()

  if simulation(a, b, f_1) then
    simulation_1_count = simulation_1_count+1
  end

  if simulation(a, b, f_M) then
    simulation_m_count = simulation_m_count+1
  end

  if first(a, b) then
    first_count = first_count+1
  end

  if second(a, b) then
    second_count = second_count+1
  end
end
print('simulation 1', simulation_1_count/N)
print('simulation M', simulation_m_count/N)
print('first', first_count/N)
print('second', second_count/N)
