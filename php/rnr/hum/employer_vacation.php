<?php

  #
  # klasa koja sadrzi sve metode vezane za vacation moduo a prosiruje funkcionalnost
  # klase employer, u nekom idelanom svetu ovo bi bile metode u klasi emplyer, ali
  # ovako je odvojeno kao nova fukniconalost
  #
  class employer_vacation extends employer
  {
    # racuna koliko je dana bilo approved u zadatoj godini
    # obraca paznju i na one intervale gde je pocetak u prethodnoj ili kraj u sledecoj.
    # NE obraca paznju na zahteve koji premasuju celu godinu, ali se lako moze dodati jos
    # jedan subquery
    public function approved_days_in_year($year)
    {
      if($this->have_id() !== true)
      {
        return 0;
      }
      $year = intval($year);
      $row = database::pdo()->prepare
      (
        'SELECT'.
        '  COALESCE('.
        '   (SELECT SUM(DATEDIFF(date_to, date_from)+1) FROM '.vacation::table_name().' WHERE'.
        '     employer_id = :employer_id AND'.
        '     status = "approved" AND'.
        '     YEAR(date_from) = :year AND'.
        '     YEAR(date_to) = :year'.
        '   ), 0'.
        '  )+'.
        '  COALESCE('.
        '    (SELECT SUM(DATEDIFF(:last_day_in_year, date_from)+1) FROM '.vacation::table_name().' WHERE'.
        '      employer_id = :employer_id AND'.
        '      status = "approved" AND'.
        '      YEAR(date_from) = :year AND'.
        '      YEAR(date_to) > :year'.
        '    ), 0'.
        '  )+'.
        '  COALESCE('.
        '    (SELECT SUM(DATEDIFF(date_to, :first_day_in_year)+1) FROM '.vacation::table_name().' WHERE'.
        '      employer_id = :employer_id AND'.
        '      status = "approved" AND'.
        '      YEAR(date_from) < :year AND'.
        '      YEAR(date_to) = :year'.
        '    ), 0'.
        '  ) AS number'
      );
      $row->execute(array(
        'employer_id' => $this->id,
        'year' => $year,
        'first_day_in_year' => $year.'-01-01',
        'last_day_in_year' => $year.'-12-31'
      ));
      return intval($row->fetch()['number']);
    }

    # vraca koliko ima jos data odmora
    public function remaining_days_in_year($year)
    {
      return $this->vacation_days-$this->approved_days_in_year($year);
    }

    # vraca niz svih dosadasnjih requestova
    public function get_all()
    {
      if($this->have_id() !== true)
      {
        return [];
      }
      return vacation::find_by_value(array('employer_id' => $this->id));
    }

    # vraca poslednji request, false ako ga nema
    public function get_last()
    {
      if($this->have_id() !== true)
      {
        return false;
      }
      $result = vacation::all('WHERE employer_id = '.$this->id.' ORDER BY time_insert DESC LIMIT 1');
      if(count($result) == 0)
      {
        return false;
      }
      return $result[0];
    }

    # slicno kao i get_last, ali na drugi nacin dobija, podsetnik: u svakom trenutku moze biti samo
    # jedan wait request po zaposlenom
    public function get_request()
    {
      if($this->have_id() !== true)
      {
        return false;
      }
      $vacations = vacation::find_by_value(array('employer_id' => $this->id, 'status' => 'wait'));
      if(count($vacations) === 0)
      {
        return false;
      }
      return $vacations[0];
    }

    # pravljenje novog requesta, vraca vacation objekat ili false ako je greska
    public function new_request($date_from, $date_to)
    {
      if($this->have_id() !== true)
      {
        return false;
      }
      $vacation = new vacation(array(
        'date_from' => $date_from,
        'date_to' => $date_to,
        'employer_id' => $this->id,
        'status' => 'wait'
      ));
      $vacation->normalize();

      # provera da li ima jos dana je ovde, a ne u vacation, jer je to deo vezan i za employera
      if($vacation->duration() > $this->remaining_days_in_year(date('Y')))
      {
        error_log::set_error('No more free days');
        return false;
      }

      # ovde proverava validnost novog zahteva po ostalim kriterijumima
      if($vacation->validate(true) === false)
      {
        return false;
      }
      $vacation->save();
      return $vacation;
    }

    # menjanje requesta($date_from, $date_to) vraca vacation objkekat ili false za gresku
    public function change_request($date_from, $date_to)
    {
      if($this->have_id() !== true)
      {
        return false;
      }
      $vacation = $this->get_request();
      if($vacation === false)
      {
        error_log::set_error('Cannot change, not found');
        return false;
      }
      $vacation->date_from = $date_from;
      $vacation->date_to = $date_to;
      $vacation->normalize();

      # provera da li ima jos dana je ovde, a ne u vacation, jer je to deo vezan i za employera
      if($vacation->duration() > $this->remaining_days_in_year(date('Y')))
      {
        error_log::set_error('No more free days');
        return false;
      }

      # ovde proverava validnost novog zahteva po ostalim kriterijumima
      if($vacation->validate(false) === false)
      {
        return false;
      }
      $vacation->save();
      return $vacation;
    }

    # otkazivanje poslednje requesta ako postoji
    public function delete_request()
    {
      $vacation = $this->get_request();
      if($vacation === false)
      {
        error_log::set_error('Cannot delete, not found');
        return false;
      }
      $vacation->delete();
      return true;
    }
  }

?>
