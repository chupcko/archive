#!/usr/bin/perl

@vreme=localtime();
$danas=($vreme[4]+1)*100+$vreme[3];

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

    $datum=$mesec*100+$dan;
    if($datum<$danas)
    {
      $datum+=10000;
    }
    $punoime=$ime." ".$prezime.($nadimak ne ""?" \"".$nadimak."\"":"");
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

foreach $datum (sort {$a <=> $b} keys %Datumi)
{
  @imena=split(/:/,$Datumi{$datum});
  if($datum>10000)
  {
    $datum-=10000;
  }
  for($i=0;$i<=$#imena;$i++)
  {
    printf "%2d.%2d. %s%s\n",$datum%100,$datum/100,$imena[$i],$datum==$danas?" <<<===":"";
  }
}
