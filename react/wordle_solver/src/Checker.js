import { useContext, useState } from 'react';

import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';
import TextField from '@mui/material/TextField';
import Typography from '@mui/material/Typography';

import { StoreContext } from './Store';

const Checker = (props) => {

  const { LEN, check } = useContext(StoreContext);

  const [ input, setInput ] = useState('');
  const [ error, setError ] = useState(false);
  const [ helper, setHelper ] = useState('');

  const enter = (input) => {
    setInput(input.toUpperCase());
    if(input == '') {
      setError(false);
      setHelper('');
      return;
    }
    if(input.length != LEN) {
      setError(false);
      setHelper(`Must have ${LEN} letters`);
      return;
    }
    if(check(input.toLowerCase())) {
      setError(false);
      setHelper('Found in the database');
      return;
    }
    setError(true);
    setHelper('Not in the database');
  };

  return (
    <TextField
      variant="standard"
      error={ error }
      value={ input }
      helperText={ helper }
      label="Check the word in the database"
      onChange={ (event) => { enter(event.target.value); } }
      sx={ { width: '15em' } }
    />
  );

};

export default Checker;
