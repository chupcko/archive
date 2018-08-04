#!/usr/bin/perl

sub nasa_slova{
  $a=@_[0];
  $a=~s/\\/\\\\/g;
  $a=~s/_/\\_/g;
  $a=~s/Cx/\\v C/g;
  $a=~s/Cy/\\'C/g;
  $a=~s/Dy/Dj/g;
  $a=~s/Ly/Lj/g;
  $a=~s/Ny/Nj/g;
  $a=~s/Sx/\\v S/g;
  $a=~s/Zx/\\v Z/g;
  $a=~s/cx/\\v c/g;
  $a=~s/cy/\\'c/g;
  $a=~s/dy/dj/g;
  $a=~s/ly/lj/g;
  $a=~s/ny/nj/g;
  $a=~s/sx/\\v s/g;
  $a=~s/zx/\\v z/g;
  $a=~s/CHUPCKO/\$\\cal CHUPCKO\$/g;
  $a=~s/\\\\//g;
  return $a;
}

print <<EOF;
\\nopagenumbers
\\splittopskip=0pt
\\newbox\\nbv
\\newbox\\nbh
\\def\\tel#1#2{%
  \\setbox\\nbh=\\hbox to 7.5cm{#1 \\dotfill #2}%
  \\ht\\nbh=8.5pt
  \\dp\\nbh=3.5pt
  \\setbox\\nbv=\\vbox{%
    \\ifvoid\\nbv\\else\\unvcopy\\nbv\\vskip 0pt plus .5pt\\fi
    \\box\\nbh
  }%
}%
\\def\\datum#1#2#3{%
  \\setbox\\nbh=\\hbox to 7.5cm{{\\bf#1.#2.} \\dotfill #3}%
  \\ht\\nbh=8.5pt
  \\dp\\nbh=3.5pt
  \\setbox\\nbv=\\vbox{%
    \\ifvoid\\nbv\\else\\unvcopy\\nbv\\vskip 0pt plus .5pt\\fi
    \\box\\nbh
  }%
}%
\\def\\nhrule{%
  \\setbox\\nbh=\\hbox to 7.5cm{\\hrulefill}%
  \\ht\\nbh=6pt
  \\dp\\nbh=6pt
  \\setbox\\nbv=\\vbox{%
    \\ifvoid\\nbv\\else\\unvcopy\\nbv\\vskip 0pt plus .5pt\\fi
    \\box\\nbh
  }%
}%
EOF

open(DAT,'people.adb');
while(<DAT>)
{
  chop;
  next if(/^#/);
  next unless(/./);
  ($prezime,$ime,$nadimak,$telefoni,$rodyendan,$email)=split(/:/,$_);
  if($telefoni ne '')
  {
    @telefon=split(/,/,$telefoni);
    for($i=0;$i<=$#telefon;$i++)
    {
      printf "\\tel{%s %s",
        $prezime ne ''?nasa_slova($prezime):'???',
        $ime ne ''?nasa_slova($ime):'???';
      if($nadimak ne '')
      {
        printf " ``%s''",nasa_slova($nadimak);
      }
      printf "}{%s}\n",$telefon[$i];
    }
  }
}
close(DAT);

print "\\nhrule\n";

open(DAT,'company.adb');
while(<DAT>)
{
  chop;
  next if(/^#/);
  next unless(/./);
  ($ime,$telefoni)=split(/:/,$_);
  if($telefoni ne '')
  {
    @telefon=split(/,/,$telefoni);
    for($i=0;$i<=$#telefon;$i++)
    {
      printf "\\tel{%s}{%s}\n",
        nasa_slova($ime),
        $telefon[$i];
    }
  }
}
close(DAT);

print "\\nhrule\n";

open(DAT,'people.adb');
while(<DAT>)
{
  chop;
  next if(/^#/);
  next unless(/./);
  ($prezime,$ime,$nadimak,$telefoni,$rodyendan,$email)=split(/:/,$_);
  if($rodyendan ne '')
  {
    ($dan,$mesec)=split(/\./,$rodyendan);
    $datum=sprintf("%02d%02d",$mesec,$dan);
    $punoime=sprintf "%s %s",
      $prezime ne ''?nasa_slova($prezime):'???',
      $ime ne ''?nasa_slova($ime):'???';
    if($nadimak ne '')
    {
      $punoime.=sprintf " ``%s''",nasa_slova($nadimak);
    }
    if(defined $Datumi{$datum})
    {
      $Datumi{$datum}.=':'.$punoime;
    }
    else
    {
      $Datumi{$datum}=$punoime;
    }
  }
}
close(DAT);

foreach $datum (sort keys %Datumi)
{
  @imena=split(/:/,$Datumi{$datum});
  $datum=~/(\d\d)(\d\d)/;
  for($i=0;$i<=$#imena;$i++)
  {
    printf "\\datum{%d}{%d}{%s}\n",$2,$1,$imena[$i];
  }
}

print <<EOF;
\\newbox\\nbpa
\\newbox\\nbpb
\\newif\\ifnotvoid
\\setbox\\nbv=\\vbox{\\unvbox\\nbv\\vfil}%
\\loop
  \\setbox\\nbpa=\\vsplit\\nbv to \\vsize
  \\setbox\\nbpa=\\vbox to \\vsize{\\unvbox\\nbpa\\vfil}%
  \\setbox\\nbpb=\\vsplit\\nbv to \\vsize
  \\setbox\\nbpb=\\vbox to \\vsize{\\unvbox\\nbpb\\vfil}%
  \\ifvoid\\nbv\\notvoidfalse\\else\\notvoidtrue\\fi
  \\hbox to \\hsize{\\box\\nbpa\\hfil\\box\\nbpb}
  \\ifnotvoid
\\repeat
\\bye
EOF
