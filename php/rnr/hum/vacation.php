<?php

  #
  # Klasa koja sadrzi vacation request
  #
  class vacation extends table
  {
    # ime db tabele
    protected static function table_name()
    {
      return 'vacations';
    }

    # kolone koje se koriste
    protected static function data_names()
    {
      return array('id', 'employer_id', 'time_insert', 'date_from', 'date_to', 'status');
    }

    # Sta ne ispisujemo u toString
    protected static function forbiden_names()
    {
      return [];
    }

    # provera ispravnosti, proverava kontreinove pre upisa u bazu
    public function validate()
    {
      # date_to mora biti posle date_from
      if(strtotime($this->date_from) >= strtotime($this->date_to))
      {
        error_log::set_error('Vacation date in wrong order');
        return false;
      }

      # status mora biti neki sa spiska
      if(in_array($this->status, array('wait', 'approved', 'rejected')) === false)
      {
        error_log::set_error('Vacation status is wrong');
        return false;
      }

      # employer mora postojati
      if(employer::find_by_id($this->employer_id) === false)
      {
        error_log::set_error('Bad employer_id');
        return false;
      }

      # samo za nove proverava jos nesto
      if($this->have_id() !== true)
      {
        # da li je date_from i date_to u buducnosti
        if
        (
          strtotime($this->date_from) <= time() or
          strtotime($this->date_to) <= time()
        )
        {
          error_log::set_error('Vacation date from past');
          return false;
        }

        # nov moze da se stavi samo ako nema neki wait zahtev
        if(count(static::find_by_value(array('employer_id' => $this->employer_id, 'status' => 'wait'))) > 0)
        {
          error_log::set_error('Already have request');
          return false;
        }

        # da li datumi ulaze u neki approved interval
        if($this->is_overlaped() === true)
        {
          error_log::set_error('Overlap intervals');
          return false;
        }
      }
      return true;
    }

    # pomocna funkcija koja sredjuje datume
    public function normalize()
    {
      $this->date_from = date('Y-m-d', strtotime($this->date_from));
      $this->date_to = date('Y-m-d', strtotime($this->date_to));
      if(is_null($this->time_insert) === true)
      {
        $this->time_insert = date('Y-m-d H:i:s');
      }
    }

    # da li su datumi "od" "do" unutar nekog intervala
    public function is_overlaped()
    {
      $rows = database::pdo()->prepare
      (
        'SELECT id FROM '.static::table_name().' WHERE'.
        '  employer_id = :employer_id AND'.
        '  status = "approved" AND ('.
        '    :date_from BETWEEN date_from AND date_to OR'.
        '    :date_to BETWEEN date_from AND date_to)'
      );
      $rows->execute(array(
        'employer_id' => $this->employer_id,
        'date_from' => $this->date_from,
        'date_to' => $this->date_to
      ));
      if(count($rows->fetchAll()) > 0)
      {
        return true;
      }
      return false;
    }

    # racuna trajanje intervala "od" "do"
    public function duration()
    {
      return intval(date_diff(date_create($this->date_from), date_create($this->date_to))->format('%a'))+1;
    }

    # menja status u approve, provera je ostvarena u boss_vacation
    public function approve()
    {
      $this->status = 'approved';
      $this->save();
    }

    # menja status u reject, provera je ostvarena u boss_vacation
    public function reject()
    {
      $this->status = 'rejected';
      $this->save();
    }
  }

?>
