Kompajliranje:
  make clean
  make

Testiranje:
  make test

Koriscenje:
  ./parjob [-d] [-n number] job_file

  -d ukljucuje debug izvestaj
  -n podesava koliko ce biti maksimalno procesa u svakom trenutku (+1 za ovaj
  glavni koji ne radi skoro nista, samo startuje)
  job_file je fajl sa komandama. Izvrsava komande iz svakog reda, preskace
  prazne redove i ignorise komentare posle #.
  Komande mogu da imaju redirekciju ili pipe, moze cak i & na kraju, ali nema
  smisla.
  Dakle moze sve sto prolazi kao unix komanda (koristeci sve moguce redirekcije
  i pipelinove)
