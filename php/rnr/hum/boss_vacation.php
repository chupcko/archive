<?php

  #
  # clasa koja nasledjuje boss-a i ima dodatne funkcije vezane za kontrole od strane
  # boss-a a vezane za vacation
  # u nekom idealnom svetu ovo bi trebalo da bude u klasi boss, ali kako je ovo modul,
  # izdvojeno je u nasledjenu klasu
  #
  class boss_vacation extends boss
  {
    # vraca niz svih vacation requesta za ovog boss-a
    public function get_all()
    {
      $result = [];
      foreach($this->all_employers() as $employer)
      {
        $employer_vacation = employer_vacation::find_by_id($employer->id);
        $result = array_merge($result, $employer_vacation->get_all());
      }
      return $result;
    }

    # vraca niz svih wait vacation requesta za ovog boss-a
    public function get_requests()
    {
      $result = [];
      foreach($this->all_employers() as $employer)
      {
        $employer_vacation = employer_vacation::find_by_id($employer->id);
        $vacation = $employer_vacation->get_request();
        if($vacation !== false)
        {
          $result[] = $vacation;
        }
      }
      return $result;
    }

    # proverava da li je vacation_id bossov i spreman za akciju
    # vraca false ako nije, ili objekat vacation ako jeste
    private function get_my_vacation_request($vacation_id)
    {
      $vacation_id = intval($vacation_id);
      $vacation = vacation::find_by_id($vacation_id);
      if($vacation === false)
      {
        return false;
      }
      $employer = employer::find_by_id($vacation->employer_id);
      if($employer === false)
      {
        return false;
      }
      if($employer->boss_id !== $this->id)
      {
        error_log::set_error('You are not my boss');
        return false;
      }
      if($vacation->status !== 'wait')
      {
        error_log::set_error('Do not touch non wait request');
        return false;
      }
      return $vacation;
    }

    # dopusta godisnji odmor za ovaj request
    public function approve($vacation_id)
    {
      $vacation = $this->get_my_vacation_request($vacation_id);
      if($vacation === false)
      {
        return false;
      }
      $vacation->approve();
      return true;
    }

    # odbija godisnji odmor za ovaj request
    public function reject($vacation_id)
    {
      $vacation = $this->get_my_vacation_request($vacation_id);
      if($vacation === false)
      {
        return false;
      }
      $vacation->reject();
      return true;
    }
  }

?>
